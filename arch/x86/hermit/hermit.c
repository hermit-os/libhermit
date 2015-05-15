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

static struct kobject *hermit_kobj = NULL;
static struct kobject *cpu_kobj[NR_CPUS] = {[0 ... NR_CPUS-1] = NULL};
static int cpu_online[NR_CPUS] = {[0 ... NR_CPUS-1] = 0};

static ssize_t hermit_is_online(struct kobject *kobj, struct kobj_attribute *attr,
				char *buf)
{
	int i;

	for_each_possible_cpu(i) {
		if (cpu_kobj[i] == kobj)
			break;
	}

	if (i>= NR_CPUS)
		return -EINVAL;

	return sprintf(buf, "%d\n", cpu_online[i]);
}

static ssize_t hermit_set_online(struct kobject *kobj, struct kobj_attribute *attr,
 				const char *buf, size_t count)
{
	int i, new_state;

	for_each_possible_cpu(i) {
		if (cpu_kobj[i] == kobj)
			break;
	}

	if (i>= NR_CPUS)
		return -EINVAL;

	sscanf(buf, "%du", &new_state);

	if (!new_state) {
		pr_notice("Currently, HermitCore isn't able to set its CPUs offline\n");
	} else {
		if (cpu_online(i)) {
			pr_notice("HermitCore isn't able to use CPU %d, because it is already used by the Linux kernel.\n", i);
		} else {
			cpu_online[i] = 1;
		}
	}

	return count;
}

static ssize_t hermit_get_log(struct kobject *kobj, struct kobj_attribute *attr,
                                char *buf)
{
	return sprintf(buf, "Hello from HermitCore\n");
}

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

	hermit_kobj = kobject_create_and_add("hermit", NULL);
	if (!hermit_kobj) {
		error = -ENOMEM;
		goto _exit;
	}

	error = sysfs_create_group(hermit_kobj, &hermit_attr_group);
	if (error)
		goto _exit;

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
