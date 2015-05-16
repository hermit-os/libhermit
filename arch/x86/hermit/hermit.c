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
#include <linux/smp.h>
#include <asm/cpu.h>

#define NAME_SIZE	128

/* code to switch from real mode in protected mode */
static uint8_t boot_code[] = {0xFA, 0x0F, 0x01, 0x16, 0x55, 0x00, 0xC6, 0x06, 0x73, 0x00, 0x31, 0x0F, 0x20, 0xC0, 0x0C, 0x01, 0x0F, 0x22, 0xC0, 0xC6, 0x06, 0x73, 0x00, 0x32, 0x66, 0xEA, 0x20, 0x00, 0x00, 0x00, 0x08, 0x00, 0xC6, 0x05, 0x73, 0x00, 0x00, 0x00, 0x33, 0x31, 0xC0, 0x66, 0xB8, 0x10, 0x00, 0x8E, 0xD8, 0x8E, 0xC0, 0x8E, 0xE0, 0x8E, 0xE8, 0x8E, 0xD0, 0xC6, 0x05, 0x73, 0x00, 0x00, 0x00, 0x34, 0xEB, 0xFE, 0xBC, 0xEF, 0xBE, 0xAD, 0xDE, 0x68, 0xAD, 0xDE, 0xAD, 0xDE, 0x6A, 0x00, 0xEA, 0xDE, 0xC0, 0xAD, 0xDE, 0x08, 0x00, 0xEB, 0xFE, 0x17, 0x00, 0x5B, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xFF, 0xFF, 0x00, 0x00, 0x00, 0x9A, 0xCF, 0x00, 0xFF, 0xFF, 0x00, 0x00, 0x00, 0x92, 0xCF, 0x00, 0x30, 0x45, 0x4F, 0x43, 0x00};

static struct kobject *hermit_kobj = NULL;
static struct kobject *cpu_kobj[NR_CPUS] = {[0 ... NR_CPUS-1] = NULL};
static int cpu_online[NR_CPUS] = {[0 ... NR_CPUS-1] = 0};

/* tramploline to boot a CPU */
extern uint8_t* hermit_trampoline;

/*
 * Wake up a core and boot HermitCore on it
 */
static int boot_hermit_core(int cpu)
{
	pr_notice("Try boot HermitCore on CPU %d\n", cpu);

	if (!hermit_trampoline)
		return -EINVAL;

	memcpy(hermit_trampoline, boot_code, sizeof(boot_code));

	return 0;
}

/*
 * shows if HermitCore is running on a specific CPU
 */
static ssize_t hermit_is_online(struct kobject *kobj, struct kobj_attribute *attr,
				char *buf)
{
	int i;

	/* search for the CPU, which is addressed by kobj */
	for_each_possible_cpu(i) {
		if (cpu_kobj[i] == kobj)
			break;
	}

	if (i>= NR_CPUS)
		return -EINVAL;

	return sprintf(buf, "%d\n", cpu_online[i]);
}

/*
 * boot or shut down a CPU with HermitCore
 */
static ssize_t hermit_set_online(struct kobject *kobj, struct kobj_attribute *attr,
 				const char *buf, size_t count)
{
	int i, new_state;

	/* search for the CPU, which is addressed by kobj */
	for_each_possible_cpu(i) {
		if (cpu_kobj[i] == kobj)
			break;
	}

	if (i>= NR_CPUS)
		return -EINVAL;

	sscanf(buf, "%du", &new_state);

	if (!new_state) {
		/* TODO: add feature to shut down a core */
		pr_notice("Currently, HermitCore isn't able to set its CPUs offline\n");
	} else {
		/* 
		 * only CPU, which are not maintained by Linux, could be used
		 * for HermitCore
		 */ 
		if (cpu_online(i)) {
			pr_notice("HermitCore isn't able to use CPU %d, because it is already used by the Linux kernel.\n", i);
		} else {
			if (!boot_hermit_core(i)) {
				// to avoid problems with Linux, we disable the hotplug feature
				cpu_hotplug_disable();

				cpu_online[i] = 1;
			}
		}
	}

	return count;
}

/*
 * Interface to display log messages from HermitCore
 */
static ssize_t hermit_get_log(struct kobject *kobj, struct kobj_attribute *attr,
                                char *buf)
{
	ssize_t ret;

	if (hermit_trampoline)
		ret = sprintf(buf, "%s\n", hermit_trampoline+sizeof(boot_code)-5);
	else
		ret = sprintf(buf, "Hello from HermitCore\n");

	return ret;
}

/*
 * Create sysfs entries as communication interface between Linux user
 * and the HermitCore kernel
 *
 * Usage:
 * Boot CPUX         : echo 1 > /sys/hermit/cpuX/online 
 * Shut down CPUX    : echo 0 > /sys/hermit/cpuX/online
 * Show log messages : cat /sys/hermit/log 
 */

static struct kobj_attribute cpu_attribute =
	__ATTR(online, 0600, hermit_is_online, hermit_set_online);

static struct kobj_attribute log_attribute =
	__ATTR(log, 0600, hermit_get_log, NULL);
  
static struct attribute * hermit_attrs[] = {
	&log_attribute.attr,
	NULL
};

static struct attribute_group hermit_attr_group = {
	.attrs = hermit_attrs,
};

static struct attribute * cpu_attrs[] = {
	&cpu_attribute.attr,
	NULL
};

static struct attribute_group cpu_attr_group = {
	.attrs = cpu_attrs,
};

int hermit_init(void)
{
	int i, error;
	char name[NAME_SIZE];

	pr_notice("Initialize HermitCore\n");
	pr_notice("HermitCore trampoline at 0x%p (0x%p)\n", hermit_trampoline, (char*) virt_to_phys(hermit_trampoline));

	/*
	 * Create a kobject for HermitCore and located
	 * under the sysfs directory (/sys)
 	 */
	hermit_kobj = kobject_create_and_add("hermit", NULL);
	if (!hermit_kobj) {
		error = -ENOMEM;
		goto _exit;
	}

	error = sysfs_create_group(hermit_kobj, &hermit_attr_group);
	if (error)
		goto _exit;

	/*
	 * Create for each possible CPU an entry and located under /sys/hermit
	 */
	for_each_possible_cpu(i) {
		/* CPU0 is always maintained by the Linux kernel */
		if (i) {
			if (snprintf(name, NAME_SIZE, "cpu%d", i) >= NAME_SIZE) {
				printk(KERN_WARNING "HermitCore: buffer is too small\n");
				continue;
			}

			cpu_kobj[i] = kobject_create_and_add(name, hermit_kobj);
			if (!cpu_kobj[i]) {
				error = -ENOMEM;
				goto _exit;
			}

			error = sysfs_create_group(cpu_kobj[i], &cpu_attr_group);
			if (error)
				goto _exit;
		}
	}

	return 0;

_exit:
	if (hermit_kobj)
		kobject_put(hermit_kobj);
	for_each_possible_cpu(i) {
		if (cpu_kobj[i]) 
			kobject_put(cpu_kobj[i]);
	}

	return error;
}
