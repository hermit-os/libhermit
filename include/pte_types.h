/* pte_types.h  */

#ifndef PTE_TYPES_H
#define PTE_TYPES_H

#ifdef __KERNEL__
#include <hermit/errno.h>
#else
#include <errno.h>
#endif

#include <sys/types.h>
#include <sys/timeb.h>

typedef unsigned int tid_t;

#endif /* PTE_TYPES_H */
