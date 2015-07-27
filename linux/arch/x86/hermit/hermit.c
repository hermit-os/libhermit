/*
 * Copyright (C) 2015, Stefan Lankes <slankes@eonerc.rwth-aachen.de>
 *                     RWTH Aachen University, Germany.
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY OR FITNESS FOR A PARTICULAR PURPOSE, GOOD TITLE or
 * NON INFRINGEMENT.  See the GNU General Public License for more
 * details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.
 */

#include <linux/kobject.h>
#include <linux/types.h>
#include <linux/kernel.h>
#include <linux/kobject.h>
#include <linux/string.h>
#include <linux/sysfs.h>
#include <linux/ctype.h>
#include <linux/init.h>
#include <linux/err.h>
#include <linux/mm.h>
#include <linux/sched.h>
#include <linux/memblock.h>
#include <linux/file.h>
#include <linux/fs.h>
#include <linux/spinlock.h>
#include <linux/slab.h>
#include <asm/page.h>
#include <asm/pgtable.h>
#include <asm/delay.h>
#include <asm/cpu.h>
#include <asm/apic.h>
#include <asm/tsc.h>
#include <asm/msr.h>

#define NAME_SIZE	256
#define CMOS_PORT	0x70
#define CMOS_PORT_DATA	0x71

/* include code to switch from real mode to 64bit mode */
#include "boot.h"

static struct kobject *hermit_kobj = NULL;
static struct kobject *isle_kobj[NR_CPUS] = {[0 ... NR_CPUS-1] = NULL};
static int cpu_online[NR_CPUS] = {[0 ... NR_CPUS-1] = -1};
static char path2hermit[NAME_SIZE] = "/hermit.bin";
static char* hermit_base[1 << NODES_SHIFT] = {[0 ... (1 << NODES_SHIFT)-1] = NULL};
static arch_spinlock_t boot_lock = __ARCH_SPIN_LOCK_UNLOCKED;
static size_t pool_size = 0x1000000;

/* tramploline to boot a CPU */
extern uint8_t* hermit_trampoline;

static inline void set_ipi_dest(uint32_t cpu_id)
{
	uint32_t tmp;

	tmp = apic_read(APIC_ICR2);
	tmp &= 0x00FFFFFF;
	tmp |= (cpu_id << 24);
	apic_write(APIC_ICR2, tmp);
}

/*
 * Wake up a core and boot HermitCore on it
 */
static int boot_hermit_core(int cpu, int isle, int cpu_counter)
{
	int i;
	unsigned int start_eip;

	pr_notice("Isle %d tries to boot HermitCore on CPU %d (boot code size 0x%zx)\n", isle, cpu, sizeof(boot_code));

	if (!hermit_trampoline)
		return -EINVAL;
	start_eip = (unsigned int) virt_to_phys(hermit_trampoline);

	if (!hermit_base[isle])
		return -ENOMEM;

	if (apic_read(APIC_ICR) & APIC_ICR_BUSY) {
		pr_notice("ERROR: previous send not complete");
		return -EIO;
	}

	arch_spin_lock(&boot_lock);

	/* intialize trampoline code */
	memcpy(hermit_trampoline, boot_code, sizeof(boot_code));

	/* relocate code */
	*((unsigned short*) (hermit_trampoline+0x04)) += (unsigned short) start_eip;
	*((unsigned int*) (hermit_trampoline+0x10)) += start_eip;
	*((unsigned int*) (hermit_trampoline+0x29)) += start_eip;
	*((unsigned int*) (hermit_trampoline+0x2E)) += start_eip;
	*((unsigned int*) (hermit_trampoline+0x3A)) += start_eip;
	*((unsigned int*) (hermit_trampoline+0x72)) += start_eip;
	*((unsigned int*) (hermit_trampoline+0xCE)) += virt_to_phys(hermit_base[isle]);
	*((unsigned int*) (hermit_trampoline+0x180)) += start_eip;
	*((unsigned int*) (hermit_trampoline+0x185)) += start_eip;

	if (!cpu_counter) {
		struct file * file;
		ssize_t sz, pos;
		ssize_t bytes;

		file = filp_open(path2hermit, O_RDONLY, 0);
		if (IS_ERR(file)) {
			int rc = PTR_ERR(file);
			pr_err("Unable to open file: %s (%d)\n", path2hermit, rc);
			return rc;
		}

		sz = i_size_read(file_inode(file));
		if (sz <= 0)
			return -EIO;
		pr_notice("Loading HermitCore's kernel image with a size of %d KiB\n", (int) sz >> 10);

		pos = 0;
		while (pos < sz) {
			bytes = kernel_read(file, pos, hermit_base[isle] + pos, sz - pos);
			if (bytes < 0) {
				pr_notice("Unable to load HermitCore's kernel\n");
				filp_close(file, NULL);
				return -EIO;
                	}
			if (bytes == 0)
				break;
			pos += bytes;
		}

		filp_close(file, NULL);

		/*
		 * set base, limit and cpu frequency in HermitCore's kernel
		 */
		*((uint64_t*) (hermit_base[isle] + 0x08)) = (uint64_t) virt_to_phys(hermit_base[isle]);
		*((uint64_t*) (hermit_base[isle] + 0x10)) = (uint64_t) virt_to_phys(hermit_base[isle] + pool_size / num_possible_nodes()); 
		*((uint32_t*) (hermit_base[isle] + 0x18)) = cpu_khz / 1000;
		*((uint32_t*) (hermit_base[isle] + 0x1C)) = cpu;
	}

	local_irq_disable();

	/* set shutdown code to 0x0A */
	outb(CMOS_PORT, 0xF);  // offset 0xF is shutdown code
	outb(CMOS_PORT_DATA, 0x0A);

	/*
	 * use the universal startup algorithm of Intel's MultiProcessor Specification
	 */
	if (x2apic_enabled()) {
		uint64_t dest = ((uint64_t)cpu << 32);

		pr_notice("X2APIC is enabled\n");

		wrmsrl(0x800 + (APIC_ICR >> 4), dest|APIC_INT_LEVELTRIG|APIC_INT_ASSERT|APIC_DM_INIT);
		udelay(200);
		/* reset INIT */
		wrmsrl(0x800 + (APIC_ICR >> 4), APIC_INT_LEVELTRIG|APIC_DM_INIT);
		udelay(10000);
		/* send out the startup */
		wrmsrl(0x800 + (APIC_ICR >> 4), dest|APIC_DM_STARTUP|(start_eip >> 12));
		udelay(200);
		/* do it again */
		wrmsrl(0x800 + (APIC_ICR >> 4), dest|APIC_DM_STARTUP|(start_eip >> 12));
		udelay(200);
	} else {
		pr_notice("X2APIC is disabled\n");

		set_ipi_dest(cpu);
		apic_write(APIC_ICR, APIC_INT_LEVELTRIG|APIC_INT_ASSERT|APIC_DM_INIT);
		udelay(200);
		/* reset INIT */
		apic_write(APIC_ICR, APIC_INT_LEVELTRIG|APIC_DM_INIT);
		udelay(10000);
		/* send out the startup */
		set_ipi_dest(cpu);
		apic_write(APIC_ICR, APIC_DM_STARTUP|(start_eip >> 12));
		udelay(200);
		/* do it again */
		set_ipi_dest(cpu);
		apic_write(APIC_ICR, APIC_DM_STARTUP|(start_eip >> 12));
		udelay(200);
	}

	i = 0;
	while((apic_read(APIC_ICR) & APIC_ICR_BUSY) && (i < 1000))
		i++; /* wait for it to finish, give up eventualy tho */

	local_irq_enable();

	cpu_counter++;
	while(*((volatile uint32_t*) (hermit_base[isle] + 0x20)) < cpu_counter) { cpu_relax(); }

	arch_spin_unlock(&boot_lock);

	return ((apic_read(APIC_ICR) & APIC_ICR_BUSY) ? -EIO : 0); // did it fail (still delivering) or succeed ?
}

/*
 * shows if HermitCore is running on a specific CPU
 */
static ssize_t hermit_is_cpus(struct kobject *kobj, struct kobj_attribute *attr,
				char *buf)
{
	char* path = kobject_get_path(kobj, GFP_KERNEL);
	int i, isle = NR_CPUS;
	int start;

	if (!path)
		return -EINVAL;

	sscanf(path, "/hermit/isle%d", &isle);

	kfree(path);

	for(i=0; (i<NR_CPUS) && (cpu_online[i] != isle); i++)
		;

	if (i >= NR_CPUS) 
		return sprintf(buf, "%d", -1);

	start = i;
	for(; (i < NR_CPUS) && (cpu_online[i] == isle); i++)
		;

	if (i >= NR_CPUS)
		i = NR_CPUS-1;
	else
		i--;

	if ((i != start) && (cpu_online[i] == isle))
		return sprintf(buf, "%d-%d\n", start, i);
	else
		return sprintf(buf, "%d\n", start);
}

/*
 * boot or shut down HermitCore
 */
static ssize_t hermit_set_cpus(struct kobject *kobj, struct kobj_attribute *attr,
 				const char *buf, size_t count)
{
	char* path = kobject_get_path(kobj, GFP_KERNEL);
	int start = NR_CPUS, end = NR_CPUS;
	int i, j, isle = NR_CPUS;
	int ret;

	if (!path)
		return -EINVAL;

	sscanf(path, "/hermit/isle%d", &isle);

	kfree(path);

	/* Do we already boot the isle? */
	for(i=0; i<NR_CPUS; i++)
		if (cpu_online[i] == isle)
			return -EBUSY;

	sscanf(buf, "%d-%d", &start, &end);

	if (end >= NR_CPUS)
		end = start;

	//pr_notice("Try to boot HermitCore on isle %d (cpu %d - %d)\n", isle, start, end);

	if (start == -1) {
		/* TODO: add feature to shut down a core */
		pr_notice("Currently, HermitCore isn't able to set a isle offline\n");
		return -EINVAL;
	}

	for(i=start; i<=end; i++) {
		/* Do Linux or HermitCore already use this CPU ? */
		if (!(!cpu_online(i) && (cpu_online[i] == -1))) {
			pr_notice("CPU %d is already online\n", i);
			return -EINVAL;
		}
	}

	//TODO: to avoid problems with Linux, we disable the hotplug feature
	cpu_hotplug_disable();

	/* reserve CPU for our isle */
	for(j=0, i=start; i<=end; i++, j++) {
		ret = boot_hermit_core(i, isle, j);
		if (!ret)
			cpu_online[i] = isle;
		else
			return ret;
	}

	return count;
}

/*
 * Interface to display log messages from HermitCore
 */
static ssize_t hermit_get_log(struct kobject *kobj, struct kobj_attribute *attr,
                                char *buf)
{
	int isle = NR_CPUS;
	char* path = kobject_get_path(kobj, GFP_KERNEL);

	if (!path)
		return -EINVAL;

	sscanf(path, "/hermit/isle%d", &isle);

	kfree(path);

	if ((isle >= 0) && (isle < NR_CPUS) && hermit_base[isle])
		return snprintf(buf, 2*PAGE_SIZE, "%s\n", hermit_base[isle]+PAGE_SIZE);

	return -ENOMEM;
}

/*
 * Get path to the kernel
 */
static ssize_t hermit_get_path(struct kobject *kobj, struct kobj_attribute *attr,
                                char *buf)
{
	return sprintf(buf, "%s\n", path2hermit);
}

/*
 * Set path to the kernel
 */
static ssize_t hermit_set_path(struct kobject *kobj, struct kobj_attribute *attr,
                                const char *buf, size_t count)
{
	return snprintf(path2hermit, NAME_SIZE, "%s", buf);
}

/*
 * Get default size of HermitCore's memory
 */
static ssize_t hermit_get_memsize(struct kobject *kobj, struct kobj_attribute *attr,
                                char *buf)
{
	return sprintf(buf, "%zd K per isle\n", pool_size / (1024 * num_possible_nodes()));
}

/*
 * Determine base address of HermitCore's kernel
 */
static ssize_t hermit_get_base(struct kobject *kobj, struct kobj_attribute *attr,
                                char *buf)
{
	int isle = NR_CPUS;
	char* path = kobject_get_path(kobj, GFP_KERNEL);

	if (!path)
		return -EINVAL;

	sscanf(path, "/hermit/isle%d", &isle);

	kfree(path);

	if (isle >= NR_CPUS)
		return -EINVAL;

	return sprintf(buf, "0x%lx\n", (size_t) hermit_base[isle]);
}

/*
 * Create sysfs entries as communication interface between Linux user
 * and the HermitCore kernel
 *
 * Usage:
 * Boot CPUX             : echo 1 > /sys/hermit/isleX/cpus 
 * Boot CPU X-Y		 : echo 1-2 > /sys/hermit/isleX/cpus
 * Shut down all CPUs    : echo 0 > /sys/hermit/isleX/online
 * Show log messages     : cat /sys/hermit/log 
 * Start address         : cat /sys/hermit/base
 * Memory size           : cat /sys/hermit/memsize
 * Set path to HermitCore: echo "/hermit.bin" > /sys/hermit/path
 * Get path to HermitCore: cat /sys/hermit/path 
 */

static struct kobj_attribute cpu_attribute =
	__ATTR(cpus, 0600, hermit_is_cpus, hermit_set_cpus);

static struct kobj_attribute log_attribute =
	__ATTR(log, 0600, hermit_get_log, NULL);

static struct kobj_attribute path_attribute =
	__ATTR(path, 0600, hermit_get_path, hermit_set_path);

static struct kobj_attribute memsize_attribute =
	__ATTR(memsize, 0600, hermit_get_memsize, NULL);

static struct kobj_attribute base_attribute =
	__ATTR(base, 0600, hermit_get_base, NULL);

static struct attribute * isle_attrs[] = {
	&cpu_attribute.attr,
	&log_attribute.attr,
	&base_attribute.attr,
	NULL
};

static struct attribute * hermit_attrs[] = {
	&path_attribute.attr,
	&memsize_attribute.attr,
	NULL
};

static struct attribute_group hermit_attr_group = {
	.attrs = hermit_attrs,
};

static struct attribute_group isle_attr_group = {
	.attrs = isle_attrs,
};

static int set_hermit_pool_size(char *arg)
{
	pool_size = memparse(arg, NULL);
        return 0;
}
early_param("hermit_pool_size", set_hermit_pool_size);

static int enable_hermit = 1;
static int disable_hermit(char *arg)
{
	enable_hermit = 0;
	return 0;
}
early_param("disable_hermit", disable_hermit);

int __init hermit_init(void)
{
	int i, ret;
	char name[NAME_SIZE];
	phys_addr_t mem;

	if (!enable_hermit)
		return 0;

	pr_notice("Initialize HermitCore\n");
	pr_notice("HermitCore trampoline at 0x%p (0x%zx)\n", hermit_trampoline, (size_t) virt_to_phys(hermit_trampoline));
	pr_notice("Number of available nodes: %d\n", num_possible_nodes());
	pr_notice("Pool size: 0x%zx\n", pool_size);

	/* allocate for each HermitCore instance */
	for(i=0; i<num_possible_nodes(); i++) {
		mem = memblock_find_in_range_node(pool_size / num_possible_nodes(), 2 << 20, 4 << 20, MEMBLOCK_ALLOC_ACCESSIBLE, i);
		//mem = memblock_find_in_range(4 << 20, 100<<20, CONFIG_HERMIT_SIZE, 2 << 20);
		if (!mem) {
			ret = -ENOMEM;
			goto _exit;
		}

		ret = memblock_reserve(mem, pool_size / num_possible_nodes());
		if (ret) {
			ret = -ENOMEM;
			goto _exit;
		}

		hermit_base[i] = (char*) phys_to_virt(mem);
		pr_notice("HermitCore %d at 0x%p (0x%zx)\n", i, hermit_base[i], (size_t) mem);
	}

	/*
	 * Create a kobject for HermitCore and located
	 * under the sysfs directory (/sys)
 	 */
	hermit_kobj = kobject_create_and_add("hermit", NULL);
	if (!hermit_kobj) {
		ret = -ENOMEM;
		goto _exit;
	}

	ret = sysfs_create_group(hermit_kobj, &hermit_attr_group);
	if (ret)
		goto _exit;

	/*
	 * Create for each possible CPU an entry and located under /sys/hermit
	 */
	for(i=0; i<num_possible_nodes(); i++) {
		if (snprintf(name, NAME_SIZE, "isle%d", i) >= NAME_SIZE) {
			printk(KERN_WARNING "HermitCore: buffer is too small\n");
			continue;
		}

		isle_kobj[i] = kobject_create_and_add(name, hermit_kobj);
		if (!isle_kobj[i]) {
			ret = -ENOMEM;
			goto _exit;
		}

		ret = sysfs_create_group(isle_kobj[i], &isle_attr_group);
		if (ret)
			goto _exit;
	}

	return 0;

_exit:
	if (hermit_kobj)
		kobject_put(hermit_kobj);
	for_each_possible_cpu(i) {
		if (isle_kobj[i]) 
			kobject_put(isle_kobj[i]);
	}

	return ret;
}
