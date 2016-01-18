/* -*- Mode: C; c-basic-offset:4 ; indent-tabs-mode:nil ; -*- */
/*
 *  (C) 2010 by Argonne National Laboratory.
 *      See COPYRIGHT in top-level directory.
 */
/* automatically generated
 *   by:   ./maint/extractcvars
 *   at:   Wed Nov 11 22:07:04 2015
 *
 * DO NOT EDIT!!!
 */

#include "mpiimpl.h"

/* Actual storage for cvars */
#if defined MPID_DEBUG_HOLD
int MPIR_CVAR_DEBUG_HOLD = MPID_DEBUG_HOLD;
#else
int MPIR_CVAR_DEBUG_HOLD = 0;
#endif /* MPID_DEBUG_HOLD */

#if defined MPID_ERROR_CHECKING
int MPIR_CVAR_ERROR_CHECKING = MPID_ERROR_CHECKING;
#else
int MPIR_CVAR_ERROR_CHECKING = 1;
#endif /* MPID_ERROR_CHECKING */

#if defined MPID_ASYNC_PROGRESS
int MPIR_CVAR_ASYNC_PROGRESS = MPID_ASYNC_PROGRESS;
#else
int MPIR_CVAR_ASYNC_PROGRESS = 0;
#endif /* MPID_ASYNC_PROGRESS */

#if defined MPID_DEFAULT_THREAD_LEVEL
char * MPIR_CVAR_DEFAULT_THREAD_LEVEL = MPID_DEFAULT_THREAD_LEVEL;
#else
char * MPIR_CVAR_DEFAULT_THREAD_LEVEL = (char*)"MPI_THREAD_SINGLE";
#endif /* MPID_DEFAULT_THREAD_LEVEL */

#if defined MPID_MEMDUMP
int MPIR_CVAR_MEMDUMP = MPID_MEMDUMP;
#else
int MPIR_CVAR_MEMDUMP = 1;
#endif /* MPID_MEMDUMP */

#if defined MPID_SUPPRESS_ABORT_MESSAGE
int MPIR_CVAR_SUPPRESS_ABORT_MESSAGE = MPID_SUPPRESS_ABORT_MESSAGE;
#else
int MPIR_CVAR_SUPPRESS_ABORT_MESSAGE = 0;
#endif /* MPID_SUPPRESS_ABORT_MESSAGE */

#if defined MPID_REDUCE_SHORT_MSG_SIZE
int MPIR_CVAR_REDUCE_SHORT_MSG_SIZE = MPID_REDUCE_SHORT_MSG_SIZE;
#else
int MPIR_CVAR_REDUCE_SHORT_MSG_SIZE = 2048;
#endif /* MPID_REDUCE_SHORT_MSG_SIZE */

#if defined MPID_ENABLE_SMP_REDUCE
int MPIR_CVAR_ENABLE_SMP_REDUCE = MPID_ENABLE_SMP_REDUCE;
#else
int MPIR_CVAR_ENABLE_SMP_REDUCE = 1;
#endif /* MPID_ENABLE_SMP_REDUCE */

#if defined MPID_MAX_SMP_REDUCE_MSG_SIZE
int MPIR_CVAR_MAX_SMP_REDUCE_MSG_SIZE = MPID_MAX_SMP_REDUCE_MSG_SIZE;
#else
int MPIR_CVAR_MAX_SMP_REDUCE_MSG_SIZE = 0;
#endif /* MPID_MAX_SMP_REDUCE_MSG_SIZE */

#if defined MPID_REDSCAT_COMMUTATIVE_LONG_MSG_SIZE
int MPIR_CVAR_REDSCAT_COMMUTATIVE_LONG_MSG_SIZE = MPID_REDSCAT_COMMUTATIVE_LONG_MSG_SIZE;
#else
int MPIR_CVAR_REDSCAT_COMMUTATIVE_LONG_MSG_SIZE = 524288;
#endif /* MPID_REDSCAT_COMMUTATIVE_LONG_MSG_SIZE */

#if defined MPID_BCAST_MIN_PROCS
int MPIR_CVAR_BCAST_MIN_PROCS = MPID_BCAST_MIN_PROCS;
#else
int MPIR_CVAR_BCAST_MIN_PROCS = 8;
#endif /* MPID_BCAST_MIN_PROCS */

#if defined MPID_BCAST_SHORT_MSG_SIZE
int MPIR_CVAR_BCAST_SHORT_MSG_SIZE = MPID_BCAST_SHORT_MSG_SIZE;
#else
int MPIR_CVAR_BCAST_SHORT_MSG_SIZE = 12288;
#endif /* MPID_BCAST_SHORT_MSG_SIZE */

#if defined MPID_BCAST_LONG_MSG_SIZE
int MPIR_CVAR_BCAST_LONG_MSG_SIZE = MPID_BCAST_LONG_MSG_SIZE;
#else
int MPIR_CVAR_BCAST_LONG_MSG_SIZE = 524288;
#endif /* MPID_BCAST_LONG_MSG_SIZE */

#if defined MPID_ENABLE_SMP_BCAST
int MPIR_CVAR_ENABLE_SMP_BCAST = MPID_ENABLE_SMP_BCAST;
#else
int MPIR_CVAR_ENABLE_SMP_BCAST = 1;
#endif /* MPID_ENABLE_SMP_BCAST */

#if defined MPID_MAX_SMP_BCAST_MSG_SIZE
int MPIR_CVAR_MAX_SMP_BCAST_MSG_SIZE = MPID_MAX_SMP_BCAST_MSG_SIZE;
#else
int MPIR_CVAR_MAX_SMP_BCAST_MSG_SIZE = 0;
#endif /* MPID_MAX_SMP_BCAST_MSG_SIZE */

#if defined MPID_GATHERV_INTER_SSEND_MIN_PROCS
int MPIR_CVAR_GATHERV_INTER_SSEND_MIN_PROCS = MPID_GATHERV_INTER_SSEND_MIN_PROCS;
#else
int MPIR_CVAR_GATHERV_INTER_SSEND_MIN_PROCS = 32;
#endif /* MPID_GATHERV_INTER_SSEND_MIN_PROCS */

#if defined MPID_ALLREDUCE_SHORT_MSG_SIZE
int MPIR_CVAR_ALLREDUCE_SHORT_MSG_SIZE = MPID_ALLREDUCE_SHORT_MSG_SIZE;
#else
int MPIR_CVAR_ALLREDUCE_SHORT_MSG_SIZE = 2048;
#endif /* MPID_ALLREDUCE_SHORT_MSG_SIZE */

#if defined MPID_ENABLE_SMP_COLLECTIVES
int MPIR_CVAR_ENABLE_SMP_COLLECTIVES = MPID_ENABLE_SMP_COLLECTIVES;
#else
int MPIR_CVAR_ENABLE_SMP_COLLECTIVES = 1;
#endif /* MPID_ENABLE_SMP_COLLECTIVES */

#if defined MPID_ENABLE_SMP_ALLREDUCE
int MPIR_CVAR_ENABLE_SMP_ALLREDUCE = MPID_ENABLE_SMP_ALLREDUCE;
#else
int MPIR_CVAR_ENABLE_SMP_ALLREDUCE = 1;
#endif /* MPID_ENABLE_SMP_ALLREDUCE */

#if defined MPID_MAX_SMP_ALLREDUCE_MSG_SIZE
int MPIR_CVAR_MAX_SMP_ALLREDUCE_MSG_SIZE = MPID_MAX_SMP_ALLREDUCE_MSG_SIZE;
#else
int MPIR_CVAR_MAX_SMP_ALLREDUCE_MSG_SIZE = 0;
#endif /* MPID_MAX_SMP_ALLREDUCE_MSG_SIZE */

#if defined MPID_GATHER_VSMALL_MSG_SIZE
int MPIR_CVAR_GATHER_VSMALL_MSG_SIZE = MPID_GATHER_VSMALL_MSG_SIZE;
#else
int MPIR_CVAR_GATHER_VSMALL_MSG_SIZE = 1024;
#endif /* MPID_GATHER_VSMALL_MSG_SIZE */

#if defined MPID_GATHER_INTER_SHORT_MSG_SIZE
int MPIR_CVAR_GATHER_INTER_SHORT_MSG_SIZE = MPID_GATHER_INTER_SHORT_MSG_SIZE;
#else
int MPIR_CVAR_GATHER_INTER_SHORT_MSG_SIZE = 2048;
#endif /* MPID_GATHER_INTER_SHORT_MSG_SIZE */

#if defined MPID_ENABLE_SMP_BARRIER
int MPIR_CVAR_ENABLE_SMP_BARRIER = MPID_ENABLE_SMP_BARRIER;
#else
int MPIR_CVAR_ENABLE_SMP_BARRIER = 1;
#endif /* MPID_ENABLE_SMP_BARRIER */

#if defined MPID_ALLGATHER_SHORT_MSG_SIZE
int MPIR_CVAR_ALLGATHER_SHORT_MSG_SIZE = MPID_ALLGATHER_SHORT_MSG_SIZE;
#else
int MPIR_CVAR_ALLGATHER_SHORT_MSG_SIZE = 81920;
#endif /* MPID_ALLGATHER_SHORT_MSG_SIZE */

#if defined MPID_ALLGATHER_LONG_MSG_SIZE
int MPIR_CVAR_ALLGATHER_LONG_MSG_SIZE = MPID_ALLGATHER_LONG_MSG_SIZE;
#else
int MPIR_CVAR_ALLGATHER_LONG_MSG_SIZE = 524288;
#endif /* MPID_ALLGATHER_LONG_MSG_SIZE */

#if defined MPID_ALLTOALL_SHORT_MSG_SIZE
int MPIR_CVAR_ALLTOALL_SHORT_MSG_SIZE = MPID_ALLTOALL_SHORT_MSG_SIZE;
#else
int MPIR_CVAR_ALLTOALL_SHORT_MSG_SIZE = 256;
#endif /* MPID_ALLTOALL_SHORT_MSG_SIZE */

#if defined MPID_ALLTOALL_MEDIUM_MSG_SIZE
int MPIR_CVAR_ALLTOALL_MEDIUM_MSG_SIZE = MPID_ALLTOALL_MEDIUM_MSG_SIZE;
#else
int MPIR_CVAR_ALLTOALL_MEDIUM_MSG_SIZE = 32768;
#endif /* MPID_ALLTOALL_MEDIUM_MSG_SIZE */

#if defined MPID_ALLTOALL_THROTTLE
int MPIR_CVAR_ALLTOALL_THROTTLE = MPID_ALLTOALL_THROTTLE;
#else
int MPIR_CVAR_ALLTOALL_THROTTLE = 32;
#endif /* MPID_ALLTOALL_THROTTLE */

#if defined MPID_SCATTER_INTER_SHORT_MSG_SIZE
int MPIR_CVAR_SCATTER_INTER_SHORT_MSG_SIZE = MPID_SCATTER_INTER_SHORT_MSG_SIZE;
#else
int MPIR_CVAR_SCATTER_INTER_SHORT_MSG_SIZE = 2048;
#endif /* MPID_SCATTER_INTER_SHORT_MSG_SIZE */

#if defined MPID_ALLGATHERV_PIPELINE_MSG_SIZE
int MPIR_CVAR_ALLGATHERV_PIPELINE_MSG_SIZE = MPID_ALLGATHERV_PIPELINE_MSG_SIZE;
#else
int MPIR_CVAR_ALLGATHERV_PIPELINE_MSG_SIZE = 32768;
#endif /* MPID_ALLGATHERV_PIPELINE_MSG_SIZE */

#if defined MPID_CTXID_EAGER_SIZE
int MPIR_CVAR_CTXID_EAGER_SIZE = MPID_CTXID_EAGER_SIZE;
#else
int MPIR_CVAR_CTXID_EAGER_SIZE = 2;
#endif /* MPID_CTXID_EAGER_SIZE */

#if defined MPID_COMM_SPLIT_USE_QSORT
int MPIR_CVAR_COMM_SPLIT_USE_QSORT = MPID_COMM_SPLIT_USE_QSORT;
#else
int MPIR_CVAR_COMM_SPLIT_USE_QSORT = 1;
#endif /* MPID_COMM_SPLIT_USE_QSORT */

#if defined MPID_PROCTABLE_SIZE
int MPIR_CVAR_PROCTABLE_SIZE = MPID_PROCTABLE_SIZE;
#else
int MPIR_CVAR_PROCTABLE_SIZE = 64;
#endif /* MPID_PROCTABLE_SIZE */

#if defined MPID_PROCTABLE_PRINT
int MPIR_CVAR_PROCTABLE_PRINT = MPID_PROCTABLE_PRINT;
#else
int MPIR_CVAR_PROCTABLE_PRINT = 0;
#endif /* MPID_PROCTABLE_PRINT */

#if defined MPID_PRINT_ERROR_STACK
int MPIR_CVAR_PRINT_ERROR_STACK = MPID_PRINT_ERROR_STACK;
#else
int MPIR_CVAR_PRINT_ERROR_STACK = 1;
#endif /* MPID_PRINT_ERROR_STACK */

#if defined MPID_CHOP_ERROR_STACK
int MPIR_CVAR_CHOP_ERROR_STACK = MPID_CHOP_ERROR_STACK;
#else
int MPIR_CVAR_CHOP_ERROR_STACK = 0;
#endif /* MPID_CHOP_ERROR_STACK */

char * MPIR_CVAR_NAMESERV_FILE_PUBDIR = (char*)NULL;
#if defined MPID_ABORT_ON_LEAKED_HANDLES
int MPIR_CVAR_ABORT_ON_LEAKED_HANDLES = MPID_ABORT_ON_LEAKED_HANDLES;
#else
int MPIR_CVAR_ABORT_ON_LEAKED_HANDLES = 0;
#endif /* MPID_ABORT_ON_LEAKED_HANDLES */

#if defined MPID_COLL_ALIAS_CHECK
int MPIR_CVAR_COLL_ALIAS_CHECK = MPID_COLL_ALIAS_CHECK;
#else
int MPIR_CVAR_COLL_ALIAS_CHECK = 1;
#endif /* MPID_COLL_ALIAS_CHECK */

int MPIR_CVAR_CH3_ENABLE_HCOLL = 0;
int MPIR_CVAR_CH3_NOLOCAL = 0;
int MPIR_CVAR_CH3_ODD_EVEN_CLIQUES = 0;
int MPIR_CVAR_CH3_EAGER_MAX_MSG_SIZE = 131072;
int MPIR_CVAR_CH3_RMA_SLOTS_SIZE = 262144;
int MPIR_CVAR_CH3_RMA_TARGET_LOCK_DATA_BYTES = 655360;
int MPIR_CVAR_CH3_RMA_OP_PIGGYBACK_LOCK_DATA_SIZE = 65536;
int MPIR_CVAR_CH3_RMA_SCALABLE_FENCE_PROCESS_NUM = 1024;
int MPIR_CVAR_CH3_RMA_DELAY_ISSUING_FOR_PIGGYBACKING = 0;
int MPIR_CVAR_CH3_RMA_ACTIVE_REQ_THRESHOLD = 65536;
int MPIR_CVAR_CH3_RMA_POKE_PROGRESS_REQ_THRESHOLD = 128;
int MPIR_CVAR_CH3_RMA_OP_WIN_POOL_SIZE = 256;
int MPIR_CVAR_CH3_RMA_OP_GLOBAL_POOL_SIZE = 16384;
int MPIR_CVAR_CH3_RMA_TARGET_WIN_POOL_SIZE = 256;
int MPIR_CVAR_CH3_RMA_TARGET_GLOBAL_POOL_SIZE = 16384;
int MPIR_CVAR_CH3_RMA_TARGET_LOCK_ENTRY_WIN_POOL_SIZE = 256;
#if defined MPID_ENABLE_FT
int MPIR_CVAR_ENABLE_FT = MPID_ENABLE_FT;
#else
int MPIR_CVAR_ENABLE_FT = 0;
#endif /* MPID_ENABLE_FT */

int MPIR_CVAR_NEMESIS_SHM_EAGER_MAX_SZ = -1;
int MPIR_CVAR_NEMESIS_SHM_READY_EAGER_MAX_SZ = -2;
int MPIR_CVAR_NEMESIS_ENABLE_CKPOINT = 0;
char * MPIR_CVAR_NEMESIS_NETMOD = (char*)"";
int MPIR_CVAR_NEMESIS_LMT_DMA_THRESHOLD = 2097152;
int MPIR_CVAR_POLLS_BEFORE_YIELD = 1000;
#if defined MPID_OFI_USE_PROVIDER
char * MPIR_CVAR_OFI_USE_PROVIDER = MPID_OFI_USE_PROVIDER;
#else
char * MPIR_CVAR_OFI_USE_PROVIDER = (char*)NULL;
#endif /* MPID_OFI_USE_PROVIDER */

#if defined MPID_OFI_DUMP_PROVIDERS
int MPIR_CVAR_OFI_DUMP_PROVIDERS = MPID_OFI_DUMP_PROVIDERS;
#else
int MPIR_CVAR_OFI_DUMP_PROVIDERS = 0;
#endif /* MPID_OFI_DUMP_PROVIDERS */

char * MPIR_CVAR_CH3_INTERFACE_HOSTNAME = (char*)NULL;
MPIR_T_cvar_range_value_t MPIR_CVAR_CH3_PORT_RANGE = {0,0};
char * MPIR_CVAR_NEMESIS_TCP_NETWORK_IFACE = (char*)NULL;
int MPIR_CVAR_NEMESIS_TCP_HOST_LOOKUP_RETRIES = 10;
int MPIR_CVAR_NEMESIS_MXM_BULK_CONNECT = 0;
int MPIR_CVAR_NEMESIS_MXM_BULK_DISCONNECT = 0;
int MPIR_CVAR_NEMESIS_MXM_HUGEPAGE = 0;

#undef FUNCNAME
#define FUNCNAME MPIR_T_cvar_init
#undef FCNAME
#define FCNAME MPL_QUOTE(FUNCNAME)
int MPIR_T_cvar_init(void)
{
    int mpi_errno = MPI_SUCCESS;
    int rc;
    const char *tmp_str;
    static int initialized = FALSE;
    MPIR_T_cvar_value_t defaultval;

    /* FIXME any MT issues here? */
    if (initialized)
        return MPI_SUCCESS;
    initialized = TRUE;

    /* declared in /tmp/wB2927n3sW/mpich-3.2/maint/../src/mpi/init/initthread.c */
    MPIR_T_cat_add_desc("DEBUGGER",
        "cvars relevant to the \"MPIR\" debugger interface");

    /* declared in /tmp/wB2927n3sW/mpich-3.2/maint/../src/mpi/init/init.c */
    MPIR_T_cat_add_desc("THREADS",
        "multi-threading cvars");

    /* declared in /tmp/wB2927n3sW/mpich-3.2/maint/../src/mpi/init/finalize.c */
    MPIR_T_cat_add_desc("DEVELOPER",
        "useful for developers working on MPICH itself");

    /* declared in /tmp/wB2927n3sW/mpich-3.2/maint/../src/mpi/coll/alltoall.c */
    MPIR_T_cat_add_desc("COLLECTIVE",
        "A category for collective communication variables.");

    /* declared in /tmp/wB2927n3sW/mpich-3.2/maint/../src/mpi/comm/comm_split.c */
    MPIR_T_cat_add_desc("COMMUNICATOR",
        "cvars that control communicator construction and operation");

    /* declared in /tmp/wB2927n3sW/mpich-3.2/maint/../src/mpi/errhan/errutil.c */
    MPIR_T_cat_add_desc("ERROR_HANDLING",
        "cvars that control error handling behavior (stack traces, aborts, etc)");

    /* declared in /tmp/wB2927n3sW/mpich-3.2/maint/../src/nameserv/file/file_nameserv.c */
    MPIR_T_cat_add_desc("PROCESS_MANAGER",
        "cvars that control the client-side process manager code");

    /* declared in /tmp/wB2927n3sW/mpich-3.2/maint/../src/util/mem/handlemem.c */
    MPIR_T_cat_add_desc("MEMORY",
        "affects memory allocation and usage, including MPI object handles");

    /* declared in /tmp/wB2927n3sW/mpich-3.2/maint/../src/mpid/ch3/src/mpidi_rma.c */
    MPIR_T_cat_add_desc("CH3",
        "cvars that control behavior of ch3");

    /* declared in /tmp/wB2927n3sW/mpich-3.2/maint/../src/mpid/ch3/channels/nemesis/src/mpid_nem_lmt.c */
    MPIR_T_cat_add_desc("FT",
        "cvars that control behavior of fault tolerance");

    /* declared in /tmp/wB2927n3sW/mpich-3.2/maint/../src/mpid/ch3/channels/nemesis/src/mpid_nem_init.c */
    MPIR_T_cat_add_desc("NEMESIS",
        "cvars that control behavior of the ch3:nemesis channel");

    defaultval.d = 0;
    MPIR_T_CVAR_REGISTER_STATIC(
        MPI_INT,
        MPIR_CVAR_DEBUG_HOLD, /* name */
        &MPIR_CVAR_DEBUG_HOLD, /* address */
        1, /* count */
        MPI_T_VERBOSITY_USER_BASIC,
        MPI_T_SCOPE_ALL_EQ,
        defaultval,
        "DEBUGGER", /* category */
        "If true, causes processes to wait in MPI_Init and MPI_Initthread for a debugger to be attached.  Once the debugger has attached, the variable 'hold' should be set to 0 in order to allow the process to continue (e.g., in gdb, \"set hold=0\").");
    rc = MPL_env2bool("MPICH_DEBUG_HOLD", &(MPIR_CVAR_DEBUG_HOLD));
    MPIR_ERR_CHKANDJUMP1((-1 == rc),mpi_errno,MPI_ERR_OTHER,"**envvarparse","**envvarparse %s","MPICH_DEBUG_HOLD");
    rc = MPL_env2bool("MPIR_PARAM_DEBUG_HOLD", &(MPIR_CVAR_DEBUG_HOLD));
    MPIR_ERR_CHKANDJUMP1((-1 == rc),mpi_errno,MPI_ERR_OTHER,"**envvarparse","**envvarparse %s","MPIR_PARAM_DEBUG_HOLD");
    rc = MPL_env2bool("MPIR_CVAR_DEBUG_HOLD", &(MPIR_CVAR_DEBUG_HOLD));
    MPIR_ERR_CHKANDJUMP1((-1 == rc),mpi_errno,MPI_ERR_OTHER,"**envvarparse","**envvarparse %s","MPIR_CVAR_DEBUG_HOLD");

    defaultval.d = 1;
    MPIR_T_CVAR_REGISTER_STATIC(
        MPI_INT,
        MPIR_CVAR_ERROR_CHECKING, /* name */
        &MPIR_CVAR_ERROR_CHECKING, /* address */
        1, /* count */
        MPI_T_VERBOSITY_USER_BASIC,
        MPI_T_SCOPE_LOCAL,
        defaultval,
        "ERROR_HANDLING", /* category */
        "If true, perform checks for errors, typically to verify valid inputs to MPI routines.  Only effective when MPICH is configured with --enable-error-checking=runtime .");
    rc = MPL_env2bool("MPICH_ERROR_CHECKING", &(MPIR_CVAR_ERROR_CHECKING));
    MPIR_ERR_CHKANDJUMP1((-1 == rc),mpi_errno,MPI_ERR_OTHER,"**envvarparse","**envvarparse %s","MPICH_ERROR_CHECKING");
    rc = MPL_env2bool("MPIR_PARAM_ERROR_CHECKING", &(MPIR_CVAR_ERROR_CHECKING));
    MPIR_ERR_CHKANDJUMP1((-1 == rc),mpi_errno,MPI_ERR_OTHER,"**envvarparse","**envvarparse %s","MPIR_PARAM_ERROR_CHECKING");
    rc = MPL_env2bool("MPIR_CVAR_ERROR_CHECKING", &(MPIR_CVAR_ERROR_CHECKING));
    MPIR_ERR_CHKANDJUMP1((-1 == rc),mpi_errno,MPI_ERR_OTHER,"**envvarparse","**envvarparse %s","MPIR_CVAR_ERROR_CHECKING");

    defaultval.d = 0;
    MPIR_T_CVAR_REGISTER_STATIC(
        MPI_INT,
        MPIR_CVAR_ASYNC_PROGRESS, /* name */
        &MPIR_CVAR_ASYNC_PROGRESS, /* address */
        1, /* count */
        MPI_T_VERBOSITY_USER_BASIC,
        MPI_T_SCOPE_ALL_EQ,
        defaultval,
        "THREADS", /* category */
        "If set to true, MPICH will initiate an additional thread to make asynchronous progress on all communication operations including point-to-point, collective, one-sided operations and I/O.  Setting this variable will automatically increase the thread-safety level to MPI_THREAD_MULTIPLE.  While this improves the progress semantics, it might cause a small amount of performance overhead for regular MPI operations.  The user is encouraged to leave one or more hardware threads vacant in order to prevent contention between the application threads and the progress thread(s).  The impact of oversubscription is highly system dependent but may be substantial in some cases, hence this recommendation.");
    rc = MPL_env2bool("MPICH_ASYNC_PROGRESS", &(MPIR_CVAR_ASYNC_PROGRESS));
    MPIR_ERR_CHKANDJUMP1((-1 == rc),mpi_errno,MPI_ERR_OTHER,"**envvarparse","**envvarparse %s","MPICH_ASYNC_PROGRESS");
    rc = MPL_env2bool("MPIR_PARAM_ASYNC_PROGRESS", &(MPIR_CVAR_ASYNC_PROGRESS));
    MPIR_ERR_CHKANDJUMP1((-1 == rc),mpi_errno,MPI_ERR_OTHER,"**envvarparse","**envvarparse %s","MPIR_PARAM_ASYNC_PROGRESS");
    rc = MPL_env2bool("MPIR_CVAR_ASYNC_PROGRESS", &(MPIR_CVAR_ASYNC_PROGRESS));
    MPIR_ERR_CHKANDJUMP1((-1 == rc),mpi_errno,MPI_ERR_OTHER,"**envvarparse","**envvarparse %s","MPIR_CVAR_ASYNC_PROGRESS");

    defaultval.str = (char *)"MPI_THREAD_SINGLE";
    MPIR_T_CVAR_REGISTER_STATIC(
        MPI_CHAR,
        MPIR_CVAR_DEFAULT_THREAD_LEVEL, /* name */
        &MPIR_CVAR_DEFAULT_THREAD_LEVEL, /* address */
        MPIR_CVAR_MAX_STRLEN, /* count */
        MPI_T_VERBOSITY_USER_BASIC,
        MPI_T_SCOPE_ALL_EQ,
        defaultval,
        "THREADS", /* category */
        "Sets the default thread level to use when using MPI_INIT.");
    MPIR_CVAR_GET_DEFAULT_STRING(MPIR_CVAR_DEFAULT_THREAD_LEVEL, &tmp_str);
    rc = MPL_env2str("MPICH_DEFAULT_THREAD_LEVEL", &tmp_str);
    MPIR_ERR_CHKANDJUMP1((-1 == rc),mpi_errno,MPI_ERR_OTHER,"**envvarparse","**envvarparse %s","MPICH_DEFAULT_THREAD_LEVEL");
    rc = MPL_env2str("MPIR_PARAM_DEFAULT_THREAD_LEVEL", &tmp_str);
    MPIR_ERR_CHKANDJUMP1((-1 == rc),mpi_errno,MPI_ERR_OTHER,"**envvarparse","**envvarparse %s","MPIR_PARAM_DEFAULT_THREAD_LEVEL");
    rc = MPL_env2str("MPIR_CVAR_DEFAULT_THREAD_LEVEL", &tmp_str);
    MPIR_ERR_CHKANDJUMP1((-1 == rc),mpi_errno,MPI_ERR_OTHER,"**envvarparse","**envvarparse %s","MPIR_CVAR_DEFAULT_THREAD_LEVEL");
    if (tmp_str != NULL) {
        MPIR_CVAR_DEFAULT_THREAD_LEVEL = MPIU_Strdup(tmp_str);
        MPIR_CVAR_assert(MPIR_CVAR_DEFAULT_THREAD_LEVEL);
        if (MPIR_CVAR_DEFAULT_THREAD_LEVEL == NULL) {
            MPIU_CHKMEM_SETERR(mpi_errno, strlen(tmp_str), "dup of string for MPIR_CVAR_DEFAULT_THREAD_LEVEL");
            goto fn_fail;
        }
    }
    else {
        MPIR_CVAR_DEFAULT_THREAD_LEVEL = NULL;
    }

    defaultval.d = 1;
    MPIR_T_CVAR_REGISTER_STATIC(
        MPI_INT,
        MPIR_CVAR_MEMDUMP, /* name */
        &MPIR_CVAR_MEMDUMP, /* address */
        1, /* count */
        MPI_T_VERBOSITY_MPIDEV_DETAIL,
        MPI_T_SCOPE_LOCAL,
        defaultval,
        "DEVELOPER", /* category */
        "If true, list any memory that was allocated by MPICH and that remains allocated when MPI_Finalize completes.");
    rc = MPL_env2bool("MPICH_MEMDUMP", &(MPIR_CVAR_MEMDUMP));
    MPIR_ERR_CHKANDJUMP1((-1 == rc),mpi_errno,MPI_ERR_OTHER,"**envvarparse","**envvarparse %s","MPICH_MEMDUMP");
    rc = MPL_env2bool("MPIR_PARAM_MEMDUMP", &(MPIR_CVAR_MEMDUMP));
    MPIR_ERR_CHKANDJUMP1((-1 == rc),mpi_errno,MPI_ERR_OTHER,"**envvarparse","**envvarparse %s","MPIR_PARAM_MEMDUMP");
    rc = MPL_env2bool("MPIR_CVAR_MEMDUMP", &(MPIR_CVAR_MEMDUMP));
    MPIR_ERR_CHKANDJUMP1((-1 == rc),mpi_errno,MPI_ERR_OTHER,"**envvarparse","**envvarparse %s","MPIR_CVAR_MEMDUMP");

    defaultval.d = 0;
    MPIR_T_CVAR_REGISTER_STATIC(
        MPI_INT,
        MPIR_CVAR_SUPPRESS_ABORT_MESSAGE, /* name */
        &MPIR_CVAR_SUPPRESS_ABORT_MESSAGE, /* address */
        1, /* count */
        MPI_T_VERBOSITY_USER_BASIC,
        MPI_T_SCOPE_ALL_EQ,
        defaultval,
        "ERROR_HANDLING", /* category */
        "Disable printing of abort error message.");
    rc = MPL_env2bool("MPICH_SUPPRESS_ABORT_MESSAGE", &(MPIR_CVAR_SUPPRESS_ABORT_MESSAGE));
    MPIR_ERR_CHKANDJUMP1((-1 == rc),mpi_errno,MPI_ERR_OTHER,"**envvarparse","**envvarparse %s","MPICH_SUPPRESS_ABORT_MESSAGE");
    rc = MPL_env2bool("MPIR_PARAM_SUPPRESS_ABORT_MESSAGE", &(MPIR_CVAR_SUPPRESS_ABORT_MESSAGE));
    MPIR_ERR_CHKANDJUMP1((-1 == rc),mpi_errno,MPI_ERR_OTHER,"**envvarparse","**envvarparse %s","MPIR_PARAM_SUPPRESS_ABORT_MESSAGE");
    rc = MPL_env2bool("MPIR_CVAR_SUPPRESS_ABORT_MESSAGE", &(MPIR_CVAR_SUPPRESS_ABORT_MESSAGE));
    MPIR_ERR_CHKANDJUMP1((-1 == rc),mpi_errno,MPI_ERR_OTHER,"**envvarparse","**envvarparse %s","MPIR_CVAR_SUPPRESS_ABORT_MESSAGE");

    defaultval.d = 2048;
    MPIR_T_CVAR_REGISTER_STATIC(
        MPI_INT,
        MPIR_CVAR_REDUCE_SHORT_MSG_SIZE, /* name */
        &MPIR_CVAR_REDUCE_SHORT_MSG_SIZE, /* address */
        1, /* count */
        MPI_T_VERBOSITY_USER_BASIC,
        MPI_T_SCOPE_ALL_EQ,
        defaultval,
        "COLLECTIVE", /* category */
        "the short message algorithm will be used if the send buffer size is <= this value (in bytes)");
    rc = MPL_env2int("MPICH_REDUCE_SHORT_MSG_SIZE", &(MPIR_CVAR_REDUCE_SHORT_MSG_SIZE));
    MPIR_ERR_CHKANDJUMP1((-1 == rc),mpi_errno,MPI_ERR_OTHER,"**envvarparse","**envvarparse %s","MPICH_REDUCE_SHORT_MSG_SIZE");
    rc = MPL_env2int("MPIR_PARAM_REDUCE_SHORT_MSG_SIZE", &(MPIR_CVAR_REDUCE_SHORT_MSG_SIZE));
    MPIR_ERR_CHKANDJUMP1((-1 == rc),mpi_errno,MPI_ERR_OTHER,"**envvarparse","**envvarparse %s","MPIR_PARAM_REDUCE_SHORT_MSG_SIZE");
    rc = MPL_env2int("MPIR_CVAR_REDUCE_SHORT_MSG_SIZE", &(MPIR_CVAR_REDUCE_SHORT_MSG_SIZE));
    MPIR_ERR_CHKANDJUMP1((-1 == rc),mpi_errno,MPI_ERR_OTHER,"**envvarparse","**envvarparse %s","MPIR_CVAR_REDUCE_SHORT_MSG_SIZE");

    defaultval.d = 1;
    MPIR_T_CVAR_REGISTER_STATIC(
        MPI_INT,
        MPIR_CVAR_ENABLE_SMP_REDUCE, /* name */
        &MPIR_CVAR_ENABLE_SMP_REDUCE, /* address */
        1, /* count */
        MPI_T_VERBOSITY_USER_BASIC,
        MPI_T_SCOPE_ALL_EQ,
        defaultval,
        "COLLECTIVE", /* category */
        "Enable SMP aware reduce.");
    rc = MPL_env2bool("MPICH_ENABLE_SMP_REDUCE", &(MPIR_CVAR_ENABLE_SMP_REDUCE));
    MPIR_ERR_CHKANDJUMP1((-1 == rc),mpi_errno,MPI_ERR_OTHER,"**envvarparse","**envvarparse %s","MPICH_ENABLE_SMP_REDUCE");
    rc = MPL_env2bool("MPIR_PARAM_ENABLE_SMP_REDUCE", &(MPIR_CVAR_ENABLE_SMP_REDUCE));
    MPIR_ERR_CHKANDJUMP1((-1 == rc),mpi_errno,MPI_ERR_OTHER,"**envvarparse","**envvarparse %s","MPIR_PARAM_ENABLE_SMP_REDUCE");
    rc = MPL_env2bool("MPIR_CVAR_ENABLE_SMP_REDUCE", &(MPIR_CVAR_ENABLE_SMP_REDUCE));
    MPIR_ERR_CHKANDJUMP1((-1 == rc),mpi_errno,MPI_ERR_OTHER,"**envvarparse","**envvarparse %s","MPIR_CVAR_ENABLE_SMP_REDUCE");

    defaultval.d = 0;
    MPIR_T_CVAR_REGISTER_STATIC(
        MPI_INT,
        MPIR_CVAR_MAX_SMP_REDUCE_MSG_SIZE, /* name */
        &MPIR_CVAR_MAX_SMP_REDUCE_MSG_SIZE, /* address */
        1, /* count */
        MPI_T_VERBOSITY_USER_BASIC,
        MPI_T_SCOPE_ALL_EQ,
        defaultval,
        "COLLECTIVE", /* category */
        "Maximum message size for which SMP-aware reduce is used.  A value of '0' uses SMP-aware reduce for all message sizes.");
    rc = MPL_env2int("MPICH_MAX_SMP_REDUCE_MSG_SIZE", &(MPIR_CVAR_MAX_SMP_REDUCE_MSG_SIZE));
    MPIR_ERR_CHKANDJUMP1((-1 == rc),mpi_errno,MPI_ERR_OTHER,"**envvarparse","**envvarparse %s","MPICH_MAX_SMP_REDUCE_MSG_SIZE");
    rc = MPL_env2int("MPIR_PARAM_MAX_SMP_REDUCE_MSG_SIZE", &(MPIR_CVAR_MAX_SMP_REDUCE_MSG_SIZE));
    MPIR_ERR_CHKANDJUMP1((-1 == rc),mpi_errno,MPI_ERR_OTHER,"**envvarparse","**envvarparse %s","MPIR_PARAM_MAX_SMP_REDUCE_MSG_SIZE");
    rc = MPL_env2int("MPIR_CVAR_MAX_SMP_REDUCE_MSG_SIZE", &(MPIR_CVAR_MAX_SMP_REDUCE_MSG_SIZE));
    MPIR_ERR_CHKANDJUMP1((-1 == rc),mpi_errno,MPI_ERR_OTHER,"**envvarparse","**envvarparse %s","MPIR_CVAR_MAX_SMP_REDUCE_MSG_SIZE");

    defaultval.d = 524288;
    MPIR_T_CVAR_REGISTER_STATIC(
        MPI_INT,
        MPIR_CVAR_REDSCAT_COMMUTATIVE_LONG_MSG_SIZE, /* name */
        &MPIR_CVAR_REDSCAT_COMMUTATIVE_LONG_MSG_SIZE, /* address */
        1, /* count */
        MPI_T_VERBOSITY_USER_BASIC,
        MPI_T_SCOPE_ALL_EQ,
        defaultval,
        "COLLECTIVE", /* category */
        "the long message algorithm will be used if the operation is commutative and the send buffer size is >= this value (in bytes)");
    rc = MPL_env2int("MPICH_REDSCAT_COMMUTATIVE_LONG_MSG_SIZE", &(MPIR_CVAR_REDSCAT_COMMUTATIVE_LONG_MSG_SIZE));
    MPIR_ERR_CHKANDJUMP1((-1 == rc),mpi_errno,MPI_ERR_OTHER,"**envvarparse","**envvarparse %s","MPICH_REDSCAT_COMMUTATIVE_LONG_MSG_SIZE");
    rc = MPL_env2int("MPIR_PARAM_REDSCAT_COMMUTATIVE_LONG_MSG_SIZE", &(MPIR_CVAR_REDSCAT_COMMUTATIVE_LONG_MSG_SIZE));
    MPIR_ERR_CHKANDJUMP1((-1 == rc),mpi_errno,MPI_ERR_OTHER,"**envvarparse","**envvarparse %s","MPIR_PARAM_REDSCAT_COMMUTATIVE_LONG_MSG_SIZE");
    rc = MPL_env2int("MPIR_CVAR_REDSCAT_COMMUTATIVE_LONG_MSG_SIZE", &(MPIR_CVAR_REDSCAT_COMMUTATIVE_LONG_MSG_SIZE));
    MPIR_ERR_CHKANDJUMP1((-1 == rc),mpi_errno,MPI_ERR_OTHER,"**envvarparse","**envvarparse %s","MPIR_CVAR_REDSCAT_COMMUTATIVE_LONG_MSG_SIZE");

    defaultval.d = 8;
    MPIR_T_CVAR_REGISTER_STATIC(
        MPI_INT,
        MPIR_CVAR_BCAST_MIN_PROCS, /* name */
        &MPIR_CVAR_BCAST_MIN_PROCS, /* address */
        1, /* count */
        MPI_T_VERBOSITY_USER_BASIC,
        MPI_T_SCOPE_ALL_EQ,
        defaultval,
        "COLLECTIVE", /* category */
        "Let's define short messages as messages with size < MPIR_CVAR_BCAST_SHORT_MSG_SIZE, and medium messages as messages with size >= MPIR_CVAR_BCAST_SHORT_MSG_SIZE but < MPIR_CVAR_BCAST_LONG_MSG_SIZE, and long messages as messages with size >= MPIR_CVAR_BCAST_LONG_MSG_SIZE. The broadcast algorithms selection procedure is as follows. For short messages or when the number of processes is < MPIR_CVAR_BCAST_MIN_PROCS, we do broadcast using the binomial tree algorithm. Otherwise, for medium messages and with a power-of-two number of processes, we do broadcast based on a scatter followed by a recursive doubling allgather algorithm. Otherwise, for long messages or with non power-of-two number of processes, we do broadcast based on a scatter followed by a ring allgather algorithm. (See also: MPIR_CVAR_BCAST_SHORT_MSG_SIZE, MPIR_CVAR_BCAST_LONG_MSG_SIZE)");
    rc = MPL_env2int("MPICH_BCAST_MIN_PROCS", &(MPIR_CVAR_BCAST_MIN_PROCS));
    MPIR_ERR_CHKANDJUMP1((-1 == rc),mpi_errno,MPI_ERR_OTHER,"**envvarparse","**envvarparse %s","MPICH_BCAST_MIN_PROCS");
    rc = MPL_env2int("MPIR_PARAM_BCAST_MIN_PROCS", &(MPIR_CVAR_BCAST_MIN_PROCS));
    MPIR_ERR_CHKANDJUMP1((-1 == rc),mpi_errno,MPI_ERR_OTHER,"**envvarparse","**envvarparse %s","MPIR_PARAM_BCAST_MIN_PROCS");
    rc = MPL_env2int("MPIR_CVAR_BCAST_MIN_PROCS", &(MPIR_CVAR_BCAST_MIN_PROCS));
    MPIR_ERR_CHKANDJUMP1((-1 == rc),mpi_errno,MPI_ERR_OTHER,"**envvarparse","**envvarparse %s","MPIR_CVAR_BCAST_MIN_PROCS");

    defaultval.d = 12288;
    MPIR_T_CVAR_REGISTER_STATIC(
        MPI_INT,
        MPIR_CVAR_BCAST_SHORT_MSG_SIZE, /* name */
        &MPIR_CVAR_BCAST_SHORT_MSG_SIZE, /* address */
        1, /* count */
        MPI_T_VERBOSITY_USER_BASIC,
        MPI_T_SCOPE_ALL_EQ,
        defaultval,
        "COLLECTIVE", /* category */
        "Let's define short messages as messages with size < MPIR_CVAR_BCAST_SHORT_MSG_SIZE, and medium messages as messages with size >= MPIR_CVAR_BCAST_SHORT_MSG_SIZE but < MPIR_CVAR_BCAST_LONG_MSG_SIZE, and long messages as messages with size >= MPIR_CVAR_BCAST_LONG_MSG_SIZE. The broadcast algorithms selection procedure is as follows. For short messages or when the number of processes is < MPIR_CVAR_BCAST_MIN_PROCS, we do broadcast using the binomial tree algorithm. Otherwise, for medium messages and with a power-of-two number of processes, we do broadcast based on a scatter followed by a recursive doubling allgather algorithm. Otherwise, for long messages or with non power-of-two number of processes, we do broadcast based on a scatter followed by a ring allgather algorithm. (See also: MPIR_CVAR_BCAST_MIN_PROCS, MPIR_CVAR_BCAST_LONG_MSG_SIZE)");
    rc = MPL_env2int("MPICH_BCAST_SHORT_MSG_SIZE", &(MPIR_CVAR_BCAST_SHORT_MSG_SIZE));
    MPIR_ERR_CHKANDJUMP1((-1 == rc),mpi_errno,MPI_ERR_OTHER,"**envvarparse","**envvarparse %s","MPICH_BCAST_SHORT_MSG_SIZE");
    rc = MPL_env2int("MPIR_PARAM_BCAST_SHORT_MSG_SIZE", &(MPIR_CVAR_BCAST_SHORT_MSG_SIZE));
    MPIR_ERR_CHKANDJUMP1((-1 == rc),mpi_errno,MPI_ERR_OTHER,"**envvarparse","**envvarparse %s","MPIR_PARAM_BCAST_SHORT_MSG_SIZE");
    rc = MPL_env2int("MPIR_CVAR_BCAST_SHORT_MSG_SIZE", &(MPIR_CVAR_BCAST_SHORT_MSG_SIZE));
    MPIR_ERR_CHKANDJUMP1((-1 == rc),mpi_errno,MPI_ERR_OTHER,"**envvarparse","**envvarparse %s","MPIR_CVAR_BCAST_SHORT_MSG_SIZE");

    defaultval.d = 524288;
    MPIR_T_CVAR_REGISTER_STATIC(
        MPI_INT,
        MPIR_CVAR_BCAST_LONG_MSG_SIZE, /* name */
        &MPIR_CVAR_BCAST_LONG_MSG_SIZE, /* address */
        1, /* count */
        MPI_T_VERBOSITY_USER_BASIC,
        MPI_T_SCOPE_ALL_EQ,
        defaultval,
        "COLLECTIVE", /* category */
        "Let's define short messages as messages with size < MPIR_CVAR_BCAST_SHORT_MSG_SIZE, and medium messages as messages with size >= MPIR_CVAR_BCAST_SHORT_MSG_SIZE but < MPIR_CVAR_BCAST_LONG_MSG_SIZE, and long messages as messages with size >= MPIR_CVAR_BCAST_LONG_MSG_SIZE. The broadcast algorithms selection procedure is as follows. For short messages or when the number of processes is < MPIR_CVAR_BCAST_MIN_PROCS, we do broadcast using the binomial tree algorithm. Otherwise, for medium messages and with a power-of-two number of processes, we do broadcast based on a scatter followed by a recursive doubling allgather algorithm. Otherwise, for long messages or with non power-of-two number of processes, we do broadcast based on a scatter followed by a ring allgather algorithm. (See also: MPIR_CVAR_BCAST_MIN_PROCS, MPIR_CVAR_BCAST_SHORT_MSG_SIZE)");
    rc = MPL_env2int("MPICH_BCAST_LONG_MSG_SIZE", &(MPIR_CVAR_BCAST_LONG_MSG_SIZE));
    MPIR_ERR_CHKANDJUMP1((-1 == rc),mpi_errno,MPI_ERR_OTHER,"**envvarparse","**envvarparse %s","MPICH_BCAST_LONG_MSG_SIZE");
    rc = MPL_env2int("MPIR_PARAM_BCAST_LONG_MSG_SIZE", &(MPIR_CVAR_BCAST_LONG_MSG_SIZE));
    MPIR_ERR_CHKANDJUMP1((-1 == rc),mpi_errno,MPI_ERR_OTHER,"**envvarparse","**envvarparse %s","MPIR_PARAM_BCAST_LONG_MSG_SIZE");
    rc = MPL_env2int("MPIR_CVAR_BCAST_LONG_MSG_SIZE", &(MPIR_CVAR_BCAST_LONG_MSG_SIZE));
    MPIR_ERR_CHKANDJUMP1((-1 == rc),mpi_errno,MPI_ERR_OTHER,"**envvarparse","**envvarparse %s","MPIR_CVAR_BCAST_LONG_MSG_SIZE");

    defaultval.d = 1;
    MPIR_T_CVAR_REGISTER_STATIC(
        MPI_INT,
        MPIR_CVAR_ENABLE_SMP_BCAST, /* name */
        &MPIR_CVAR_ENABLE_SMP_BCAST, /* address */
        1, /* count */
        MPI_T_VERBOSITY_USER_BASIC,
        MPI_T_SCOPE_ALL_EQ,
        defaultval,
        "COLLECTIVE", /* category */
        "Enable SMP aware broadcast (See also: MPIR_CVAR_MAX_SMP_BCAST_MSG_SIZE)");
    rc = MPL_env2bool("MPICH_ENABLE_SMP_BCAST", &(MPIR_CVAR_ENABLE_SMP_BCAST));
    MPIR_ERR_CHKANDJUMP1((-1 == rc),mpi_errno,MPI_ERR_OTHER,"**envvarparse","**envvarparse %s","MPICH_ENABLE_SMP_BCAST");
    rc = MPL_env2bool("MPIR_PARAM_ENABLE_SMP_BCAST", &(MPIR_CVAR_ENABLE_SMP_BCAST));
    MPIR_ERR_CHKANDJUMP1((-1 == rc),mpi_errno,MPI_ERR_OTHER,"**envvarparse","**envvarparse %s","MPIR_PARAM_ENABLE_SMP_BCAST");
    rc = MPL_env2bool("MPIR_CVAR_ENABLE_SMP_BCAST", &(MPIR_CVAR_ENABLE_SMP_BCAST));
    MPIR_ERR_CHKANDJUMP1((-1 == rc),mpi_errno,MPI_ERR_OTHER,"**envvarparse","**envvarparse %s","MPIR_CVAR_ENABLE_SMP_BCAST");

    defaultval.d = 0;
    MPIR_T_CVAR_REGISTER_STATIC(
        MPI_INT,
        MPIR_CVAR_MAX_SMP_BCAST_MSG_SIZE, /* name */
        &MPIR_CVAR_MAX_SMP_BCAST_MSG_SIZE, /* address */
        1, /* count */
        MPI_T_VERBOSITY_USER_BASIC,
        MPI_T_SCOPE_ALL_EQ,
        defaultval,
        "COLLECTIVE", /* category */
        "Maximum message size for which SMP-aware broadcast is used.  A value of '0' uses SMP-aware broadcast for all message sizes. (See also: MPIR_CVAR_ENABLE_SMP_BCAST)");
    rc = MPL_env2int("MPICH_MAX_SMP_BCAST_MSG_SIZE", &(MPIR_CVAR_MAX_SMP_BCAST_MSG_SIZE));
    MPIR_ERR_CHKANDJUMP1((-1 == rc),mpi_errno,MPI_ERR_OTHER,"**envvarparse","**envvarparse %s","MPICH_MAX_SMP_BCAST_MSG_SIZE");
    rc = MPL_env2int("MPIR_PARAM_MAX_SMP_BCAST_MSG_SIZE", &(MPIR_CVAR_MAX_SMP_BCAST_MSG_SIZE));
    MPIR_ERR_CHKANDJUMP1((-1 == rc),mpi_errno,MPI_ERR_OTHER,"**envvarparse","**envvarparse %s","MPIR_PARAM_MAX_SMP_BCAST_MSG_SIZE");
    rc = MPL_env2int("MPIR_CVAR_MAX_SMP_BCAST_MSG_SIZE", &(MPIR_CVAR_MAX_SMP_BCAST_MSG_SIZE));
    MPIR_ERR_CHKANDJUMP1((-1 == rc),mpi_errno,MPI_ERR_OTHER,"**envvarparse","**envvarparse %s","MPIR_CVAR_MAX_SMP_BCAST_MSG_SIZE");

    defaultval.d = 32;
    MPIR_T_CVAR_REGISTER_STATIC(
        MPI_INT,
        MPIR_CVAR_GATHERV_INTER_SSEND_MIN_PROCS, /* name */
        &MPIR_CVAR_GATHERV_INTER_SSEND_MIN_PROCS, /* address */
        1, /* count */
        MPI_T_VERBOSITY_USER_BASIC,
        MPI_T_SCOPE_ALL_EQ,
        defaultval,
        "COLLECTIVE", /* category */
        "Use Ssend (synchronous send) for intercommunicator MPI_Gatherv if the \"group B\" size is >= this value.  Specifying \"-1\" always avoids using Ssend.  For backwards compatibility, specifying \"0\" uses the default value.");
    rc = MPL_env2int("MPICH_GATHERV_INTER_SSEND_MIN_PROCS", &(MPIR_CVAR_GATHERV_INTER_SSEND_MIN_PROCS));
    MPIR_ERR_CHKANDJUMP1((-1 == rc),mpi_errno,MPI_ERR_OTHER,"**envvarparse","**envvarparse %s","MPICH_GATHERV_INTER_SSEND_MIN_PROCS");
    rc = MPL_env2int("MPIR_PARAM_GATHERV_INTER_SSEND_MIN_PROCS", &(MPIR_CVAR_GATHERV_INTER_SSEND_MIN_PROCS));
    MPIR_ERR_CHKANDJUMP1((-1 == rc),mpi_errno,MPI_ERR_OTHER,"**envvarparse","**envvarparse %s","MPIR_PARAM_GATHERV_INTER_SSEND_MIN_PROCS");
    rc = MPL_env2int("MPIR_CVAR_GATHERV_INTER_SSEND_MIN_PROCS", &(MPIR_CVAR_GATHERV_INTER_SSEND_MIN_PROCS));
    MPIR_ERR_CHKANDJUMP1((-1 == rc),mpi_errno,MPI_ERR_OTHER,"**envvarparse","**envvarparse %s","MPIR_CVAR_GATHERV_INTER_SSEND_MIN_PROCS");

    defaultval.d = 2048;
    MPIR_T_CVAR_REGISTER_STATIC(
        MPI_INT,
        MPIR_CVAR_ALLREDUCE_SHORT_MSG_SIZE, /* name */
        &MPIR_CVAR_ALLREDUCE_SHORT_MSG_SIZE, /* address */
        1, /* count */
        MPI_T_VERBOSITY_USER_BASIC,
        MPI_T_SCOPE_ALL_EQ,
        defaultval,
        "COLLECTIVE", /* category */
        "the short message algorithm will be used if the send buffer size is <= this value (in bytes)");
    rc = MPL_env2int("MPICH_ALLREDUCE_SHORT_MSG_SIZE", &(MPIR_CVAR_ALLREDUCE_SHORT_MSG_SIZE));
    MPIR_ERR_CHKANDJUMP1((-1 == rc),mpi_errno,MPI_ERR_OTHER,"**envvarparse","**envvarparse %s","MPICH_ALLREDUCE_SHORT_MSG_SIZE");
    rc = MPL_env2int("MPIR_PARAM_ALLREDUCE_SHORT_MSG_SIZE", &(MPIR_CVAR_ALLREDUCE_SHORT_MSG_SIZE));
    MPIR_ERR_CHKANDJUMP1((-1 == rc),mpi_errno,MPI_ERR_OTHER,"**envvarparse","**envvarparse %s","MPIR_PARAM_ALLREDUCE_SHORT_MSG_SIZE");
    rc = MPL_env2int("MPIR_CVAR_ALLREDUCE_SHORT_MSG_SIZE", &(MPIR_CVAR_ALLREDUCE_SHORT_MSG_SIZE));
    MPIR_ERR_CHKANDJUMP1((-1 == rc),mpi_errno,MPI_ERR_OTHER,"**envvarparse","**envvarparse %s","MPIR_CVAR_ALLREDUCE_SHORT_MSG_SIZE");

    defaultval.d = 1;
    MPIR_T_CVAR_REGISTER_STATIC(
        MPI_INT,
        MPIR_CVAR_ENABLE_SMP_COLLECTIVES, /* name */
        &MPIR_CVAR_ENABLE_SMP_COLLECTIVES, /* address */
        1, /* count */
        MPI_T_VERBOSITY_USER_BASIC,
        MPI_T_SCOPE_ALL_EQ,
        defaultval,
        "COLLECTIVE", /* category */
        "Enable SMP aware collective communication.");
    rc = MPL_env2bool("MPICH_ENABLE_SMP_COLLECTIVES", &(MPIR_CVAR_ENABLE_SMP_COLLECTIVES));
    MPIR_ERR_CHKANDJUMP1((-1 == rc),mpi_errno,MPI_ERR_OTHER,"**envvarparse","**envvarparse %s","MPICH_ENABLE_SMP_COLLECTIVES");
    rc = MPL_env2bool("MPIR_PARAM_ENABLE_SMP_COLLECTIVES", &(MPIR_CVAR_ENABLE_SMP_COLLECTIVES));
    MPIR_ERR_CHKANDJUMP1((-1 == rc),mpi_errno,MPI_ERR_OTHER,"**envvarparse","**envvarparse %s","MPIR_PARAM_ENABLE_SMP_COLLECTIVES");
    rc = MPL_env2bool("MPIR_CVAR_ENABLE_SMP_COLLECTIVES", &(MPIR_CVAR_ENABLE_SMP_COLLECTIVES));
    MPIR_ERR_CHKANDJUMP1((-1 == rc),mpi_errno,MPI_ERR_OTHER,"**envvarparse","**envvarparse %s","MPIR_CVAR_ENABLE_SMP_COLLECTIVES");

    defaultval.d = 1;
    MPIR_T_CVAR_REGISTER_STATIC(
        MPI_INT,
        MPIR_CVAR_ENABLE_SMP_ALLREDUCE, /* name */
        &MPIR_CVAR_ENABLE_SMP_ALLREDUCE, /* address */
        1, /* count */
        MPI_T_VERBOSITY_USER_BASIC,
        MPI_T_SCOPE_ALL_EQ,
        defaultval,
        "COLLECTIVE", /* category */
        "Enable SMP aware allreduce.");
    rc = MPL_env2bool("MPICH_ENABLE_SMP_ALLREDUCE", &(MPIR_CVAR_ENABLE_SMP_ALLREDUCE));
    MPIR_ERR_CHKANDJUMP1((-1 == rc),mpi_errno,MPI_ERR_OTHER,"**envvarparse","**envvarparse %s","MPICH_ENABLE_SMP_ALLREDUCE");
    rc = MPL_env2bool("MPIR_PARAM_ENABLE_SMP_ALLREDUCE", &(MPIR_CVAR_ENABLE_SMP_ALLREDUCE));
    MPIR_ERR_CHKANDJUMP1((-1 == rc),mpi_errno,MPI_ERR_OTHER,"**envvarparse","**envvarparse %s","MPIR_PARAM_ENABLE_SMP_ALLREDUCE");
    rc = MPL_env2bool("MPIR_CVAR_ENABLE_SMP_ALLREDUCE", &(MPIR_CVAR_ENABLE_SMP_ALLREDUCE));
    MPIR_ERR_CHKANDJUMP1((-1 == rc),mpi_errno,MPI_ERR_OTHER,"**envvarparse","**envvarparse %s","MPIR_CVAR_ENABLE_SMP_ALLREDUCE");

    defaultval.d = 0;
    MPIR_T_CVAR_REGISTER_STATIC(
        MPI_INT,
        MPIR_CVAR_MAX_SMP_ALLREDUCE_MSG_SIZE, /* name */
        &MPIR_CVAR_MAX_SMP_ALLREDUCE_MSG_SIZE, /* address */
        1, /* count */
        MPI_T_VERBOSITY_USER_BASIC,
        MPI_T_SCOPE_ALL_EQ,
        defaultval,
        "COLLECTIVE", /* category */
        "Maximum message size for which SMP-aware allreduce is used.  A value of '0' uses SMP-aware allreduce for all message sizes.");
    rc = MPL_env2int("MPICH_MAX_SMP_ALLREDUCE_MSG_SIZE", &(MPIR_CVAR_MAX_SMP_ALLREDUCE_MSG_SIZE));
    MPIR_ERR_CHKANDJUMP1((-1 == rc),mpi_errno,MPI_ERR_OTHER,"**envvarparse","**envvarparse %s","MPICH_MAX_SMP_ALLREDUCE_MSG_SIZE");
    rc = MPL_env2int("MPIR_PARAM_MAX_SMP_ALLREDUCE_MSG_SIZE", &(MPIR_CVAR_MAX_SMP_ALLREDUCE_MSG_SIZE));
    MPIR_ERR_CHKANDJUMP1((-1 == rc),mpi_errno,MPI_ERR_OTHER,"**envvarparse","**envvarparse %s","MPIR_PARAM_MAX_SMP_ALLREDUCE_MSG_SIZE");
    rc = MPL_env2int("MPIR_CVAR_MAX_SMP_ALLREDUCE_MSG_SIZE", &(MPIR_CVAR_MAX_SMP_ALLREDUCE_MSG_SIZE));
    MPIR_ERR_CHKANDJUMP1((-1 == rc),mpi_errno,MPI_ERR_OTHER,"**envvarparse","**envvarparse %s","MPIR_CVAR_MAX_SMP_ALLREDUCE_MSG_SIZE");

    defaultval.d = 1024;
    MPIR_T_CVAR_REGISTER_STATIC(
        MPI_INT,
        MPIR_CVAR_GATHER_VSMALL_MSG_SIZE, /* name */
        &MPIR_CVAR_GATHER_VSMALL_MSG_SIZE, /* address */
        1, /* count */
        MPI_T_VERBOSITY_USER_BASIC,
        MPI_T_SCOPE_ALL_EQ,
        defaultval,
        "COLLECTIVE", /* category */
        "use a temporary buffer for intracommunicator MPI_Gather if the send buffer size is < this value (in bytes) (See also: MPIR_CVAR_GATHER_INTER_SHORT_MSG_SIZE)");
    rc = MPL_env2int("MPICH_GATHER_VSMALL_MSG_SIZE", &(MPIR_CVAR_GATHER_VSMALL_MSG_SIZE));
    MPIR_ERR_CHKANDJUMP1((-1 == rc),mpi_errno,MPI_ERR_OTHER,"**envvarparse","**envvarparse %s","MPICH_GATHER_VSMALL_MSG_SIZE");
    rc = MPL_env2int("MPIR_PARAM_GATHER_VSMALL_MSG_SIZE", &(MPIR_CVAR_GATHER_VSMALL_MSG_SIZE));
    MPIR_ERR_CHKANDJUMP1((-1 == rc),mpi_errno,MPI_ERR_OTHER,"**envvarparse","**envvarparse %s","MPIR_PARAM_GATHER_VSMALL_MSG_SIZE");
    rc = MPL_env2int("MPIR_CVAR_GATHER_VSMALL_MSG_SIZE", &(MPIR_CVAR_GATHER_VSMALL_MSG_SIZE));
    MPIR_ERR_CHKANDJUMP1((-1 == rc),mpi_errno,MPI_ERR_OTHER,"**envvarparse","**envvarparse %s","MPIR_CVAR_GATHER_VSMALL_MSG_SIZE");

    defaultval.d = 2048;
    MPIR_T_CVAR_REGISTER_STATIC(
        MPI_INT,
        MPIR_CVAR_GATHER_INTER_SHORT_MSG_SIZE, /* name */
        &MPIR_CVAR_GATHER_INTER_SHORT_MSG_SIZE, /* address */
        1, /* count */
        MPI_T_VERBOSITY_USER_BASIC,
        MPI_T_SCOPE_ALL_EQ,
        defaultval,
        "COLLECTIVE", /* category */
        "use the short message algorithm for intercommunicator MPI_Gather if the send buffer size is < this value (in bytes) (See also: MPIR_CVAR_GATHER_VSMALL_MSG_SIZE)");
    rc = MPL_env2int("MPICH_GATHER_INTER_SHORT_MSG_SIZE", &(MPIR_CVAR_GATHER_INTER_SHORT_MSG_SIZE));
    MPIR_ERR_CHKANDJUMP1((-1 == rc),mpi_errno,MPI_ERR_OTHER,"**envvarparse","**envvarparse %s","MPICH_GATHER_INTER_SHORT_MSG_SIZE");
    rc = MPL_env2int("MPIR_PARAM_GATHER_INTER_SHORT_MSG_SIZE", &(MPIR_CVAR_GATHER_INTER_SHORT_MSG_SIZE));
    MPIR_ERR_CHKANDJUMP1((-1 == rc),mpi_errno,MPI_ERR_OTHER,"**envvarparse","**envvarparse %s","MPIR_PARAM_GATHER_INTER_SHORT_MSG_SIZE");
    rc = MPL_env2int("MPIR_CVAR_GATHER_INTER_SHORT_MSG_SIZE", &(MPIR_CVAR_GATHER_INTER_SHORT_MSG_SIZE));
    MPIR_ERR_CHKANDJUMP1((-1 == rc),mpi_errno,MPI_ERR_OTHER,"**envvarparse","**envvarparse %s","MPIR_CVAR_GATHER_INTER_SHORT_MSG_SIZE");

    defaultval.d = 1;
    MPIR_T_CVAR_REGISTER_STATIC(
        MPI_INT,
        MPIR_CVAR_ENABLE_SMP_BARRIER, /* name */
        &MPIR_CVAR_ENABLE_SMP_BARRIER, /* address */
        1, /* count */
        MPI_T_VERBOSITY_USER_BASIC,
        MPI_T_SCOPE_ALL_EQ,
        defaultval,
        "COLLECTIVE", /* category */
        "Enable SMP aware barrier.");
    rc = MPL_env2bool("MPICH_ENABLE_SMP_BARRIER", &(MPIR_CVAR_ENABLE_SMP_BARRIER));
    MPIR_ERR_CHKANDJUMP1((-1 == rc),mpi_errno,MPI_ERR_OTHER,"**envvarparse","**envvarparse %s","MPICH_ENABLE_SMP_BARRIER");
    rc = MPL_env2bool("MPIR_PARAM_ENABLE_SMP_BARRIER", &(MPIR_CVAR_ENABLE_SMP_BARRIER));
    MPIR_ERR_CHKANDJUMP1((-1 == rc),mpi_errno,MPI_ERR_OTHER,"**envvarparse","**envvarparse %s","MPIR_PARAM_ENABLE_SMP_BARRIER");
    rc = MPL_env2bool("MPIR_CVAR_ENABLE_SMP_BARRIER", &(MPIR_CVAR_ENABLE_SMP_BARRIER));
    MPIR_ERR_CHKANDJUMP1((-1 == rc),mpi_errno,MPI_ERR_OTHER,"**envvarparse","**envvarparse %s","MPIR_CVAR_ENABLE_SMP_BARRIER");

    defaultval.d = 81920;
    MPIR_T_CVAR_REGISTER_STATIC(
        MPI_INT,
        MPIR_CVAR_ALLGATHER_SHORT_MSG_SIZE, /* name */
        &MPIR_CVAR_ALLGATHER_SHORT_MSG_SIZE, /* address */
        1, /* count */
        MPI_T_VERBOSITY_USER_BASIC,
        MPI_T_SCOPE_ALL_EQ,
        defaultval,
        "COLLECTIVE", /* category */
        "For MPI_Allgather and MPI_Allgatherv, the short message algorithm will be used if the send buffer size is < this value (in bytes). (See also: MPIR_CVAR_ALLGATHER_LONG_MSG_SIZE)");
    rc = MPL_env2int("MPICH_ALLGATHER_SHORT_MSG_SIZE", &(MPIR_CVAR_ALLGATHER_SHORT_MSG_SIZE));
    MPIR_ERR_CHKANDJUMP1((-1 == rc),mpi_errno,MPI_ERR_OTHER,"**envvarparse","**envvarparse %s","MPICH_ALLGATHER_SHORT_MSG_SIZE");
    rc = MPL_env2int("MPIR_PARAM_ALLGATHER_SHORT_MSG_SIZE", &(MPIR_CVAR_ALLGATHER_SHORT_MSG_SIZE));
    MPIR_ERR_CHKANDJUMP1((-1 == rc),mpi_errno,MPI_ERR_OTHER,"**envvarparse","**envvarparse %s","MPIR_PARAM_ALLGATHER_SHORT_MSG_SIZE");
    rc = MPL_env2int("MPIR_CVAR_ALLGATHER_SHORT_MSG_SIZE", &(MPIR_CVAR_ALLGATHER_SHORT_MSG_SIZE));
    MPIR_ERR_CHKANDJUMP1((-1 == rc),mpi_errno,MPI_ERR_OTHER,"**envvarparse","**envvarparse %s","MPIR_CVAR_ALLGATHER_SHORT_MSG_SIZE");

    defaultval.d = 524288;
    MPIR_T_CVAR_REGISTER_STATIC(
        MPI_INT,
        MPIR_CVAR_ALLGATHER_LONG_MSG_SIZE, /* name */
        &MPIR_CVAR_ALLGATHER_LONG_MSG_SIZE, /* address */
        1, /* count */
        MPI_T_VERBOSITY_USER_BASIC,
        MPI_T_SCOPE_ALL_EQ,
        defaultval,
        "COLLECTIVE", /* category */
        "For MPI_Allgather and MPI_Allgatherv, the long message algorithm will be used if the send buffer size is >= this value (in bytes) (See also: MPIR_CVAR_ALLGATHER_SHORT_MSG_SIZE)");
    rc = MPL_env2int("MPICH_ALLGATHER_LONG_MSG_SIZE", &(MPIR_CVAR_ALLGATHER_LONG_MSG_SIZE));
    MPIR_ERR_CHKANDJUMP1((-1 == rc),mpi_errno,MPI_ERR_OTHER,"**envvarparse","**envvarparse %s","MPICH_ALLGATHER_LONG_MSG_SIZE");
    rc = MPL_env2int("MPIR_PARAM_ALLGATHER_LONG_MSG_SIZE", &(MPIR_CVAR_ALLGATHER_LONG_MSG_SIZE));
    MPIR_ERR_CHKANDJUMP1((-1 == rc),mpi_errno,MPI_ERR_OTHER,"**envvarparse","**envvarparse %s","MPIR_PARAM_ALLGATHER_LONG_MSG_SIZE");
    rc = MPL_env2int("MPIR_CVAR_ALLGATHER_LONG_MSG_SIZE", &(MPIR_CVAR_ALLGATHER_LONG_MSG_SIZE));
    MPIR_ERR_CHKANDJUMP1((-1 == rc),mpi_errno,MPI_ERR_OTHER,"**envvarparse","**envvarparse %s","MPIR_CVAR_ALLGATHER_LONG_MSG_SIZE");

    defaultval.d = 256;
    MPIR_T_CVAR_REGISTER_STATIC(
        MPI_INT,
        MPIR_CVAR_ALLTOALL_SHORT_MSG_SIZE, /* name */
        &MPIR_CVAR_ALLTOALL_SHORT_MSG_SIZE, /* address */
        1, /* count */
        MPI_T_VERBOSITY_USER_BASIC,
        MPI_T_SCOPE_ALL_EQ,
        defaultval,
        "COLLECTIVE", /* category */
        "the short message algorithm will be used if the per-destination message size (sendcount*size(sendtype)) is <= this value (See also: MPIR_CVAR_ALLTOALL_MEDIUM_MSG_SIZE)");
    rc = MPL_env2int("MPICH_ALLTOALL_SHORT_MSG_SIZE", &(MPIR_CVAR_ALLTOALL_SHORT_MSG_SIZE));
    MPIR_ERR_CHKANDJUMP1((-1 == rc),mpi_errno,MPI_ERR_OTHER,"**envvarparse","**envvarparse %s","MPICH_ALLTOALL_SHORT_MSG_SIZE");
    rc = MPL_env2int("MPIR_PARAM_ALLTOALL_SHORT_MSG_SIZE", &(MPIR_CVAR_ALLTOALL_SHORT_MSG_SIZE));
    MPIR_ERR_CHKANDJUMP1((-1 == rc),mpi_errno,MPI_ERR_OTHER,"**envvarparse","**envvarparse %s","MPIR_PARAM_ALLTOALL_SHORT_MSG_SIZE");
    rc = MPL_env2int("MPIR_CVAR_ALLTOALL_SHORT_MSG_SIZE", &(MPIR_CVAR_ALLTOALL_SHORT_MSG_SIZE));
    MPIR_ERR_CHKANDJUMP1((-1 == rc),mpi_errno,MPI_ERR_OTHER,"**envvarparse","**envvarparse %s","MPIR_CVAR_ALLTOALL_SHORT_MSG_SIZE");

    defaultval.d = 32768;
    MPIR_T_CVAR_REGISTER_STATIC(
        MPI_INT,
        MPIR_CVAR_ALLTOALL_MEDIUM_MSG_SIZE, /* name */
        &MPIR_CVAR_ALLTOALL_MEDIUM_MSG_SIZE, /* address */
        1, /* count */
        MPI_T_VERBOSITY_USER_BASIC,
        MPI_T_SCOPE_ALL_EQ,
        defaultval,
        "COLLECTIVE", /* category */
        "the medium message algorithm will be used if the per-destination message size (sendcount*size(sendtype)) is <= this value and larger than MPIR_CVAR_ALLTOALL_SHORT_MSG_SIZE (See also: MPIR_CVAR_ALLTOALL_SHORT_MSG_SIZE)");
    rc = MPL_env2int("MPICH_ALLTOALL_MEDIUM_MSG_SIZE", &(MPIR_CVAR_ALLTOALL_MEDIUM_MSG_SIZE));
    MPIR_ERR_CHKANDJUMP1((-1 == rc),mpi_errno,MPI_ERR_OTHER,"**envvarparse","**envvarparse %s","MPICH_ALLTOALL_MEDIUM_MSG_SIZE");
    rc = MPL_env2int("MPIR_PARAM_ALLTOALL_MEDIUM_MSG_SIZE", &(MPIR_CVAR_ALLTOALL_MEDIUM_MSG_SIZE));
    MPIR_ERR_CHKANDJUMP1((-1 == rc),mpi_errno,MPI_ERR_OTHER,"**envvarparse","**envvarparse %s","MPIR_PARAM_ALLTOALL_MEDIUM_MSG_SIZE");
    rc = MPL_env2int("MPIR_CVAR_ALLTOALL_MEDIUM_MSG_SIZE", &(MPIR_CVAR_ALLTOALL_MEDIUM_MSG_SIZE));
    MPIR_ERR_CHKANDJUMP1((-1 == rc),mpi_errno,MPI_ERR_OTHER,"**envvarparse","**envvarparse %s","MPIR_CVAR_ALLTOALL_MEDIUM_MSG_SIZE");

    defaultval.d = 32;
    MPIR_T_CVAR_REGISTER_STATIC(
        MPI_INT,
        MPIR_CVAR_ALLTOALL_THROTTLE, /* name */
        &MPIR_CVAR_ALLTOALL_THROTTLE, /* address */
        1, /* count */
        MPI_T_VERBOSITY_USER_BASIC,
        MPI_T_SCOPE_ALL_EQ,
        defaultval,
        "COLLECTIVE", /* category */
        "max no. of irecvs/isends posted at a time in some alltoall algorithms. Setting it to 0 causes all irecvs/isends to be posted at once");
    rc = MPL_env2int("MPICH_ALLTOALL_THROTTLE", &(MPIR_CVAR_ALLTOALL_THROTTLE));
    MPIR_ERR_CHKANDJUMP1((-1 == rc),mpi_errno,MPI_ERR_OTHER,"**envvarparse","**envvarparse %s","MPICH_ALLTOALL_THROTTLE");
    rc = MPL_env2int("MPIR_PARAM_ALLTOALL_THROTTLE", &(MPIR_CVAR_ALLTOALL_THROTTLE));
    MPIR_ERR_CHKANDJUMP1((-1 == rc),mpi_errno,MPI_ERR_OTHER,"**envvarparse","**envvarparse %s","MPIR_PARAM_ALLTOALL_THROTTLE");
    rc = MPL_env2int("MPIR_CVAR_ALLTOALL_THROTTLE", &(MPIR_CVAR_ALLTOALL_THROTTLE));
    MPIR_ERR_CHKANDJUMP1((-1 == rc),mpi_errno,MPI_ERR_OTHER,"**envvarparse","**envvarparse %s","MPIR_CVAR_ALLTOALL_THROTTLE");

    defaultval.d = 2048;
    MPIR_T_CVAR_REGISTER_STATIC(
        MPI_INT,
        MPIR_CVAR_SCATTER_INTER_SHORT_MSG_SIZE, /* name */
        &MPIR_CVAR_SCATTER_INTER_SHORT_MSG_SIZE, /* address */
        1, /* count */
        MPI_T_VERBOSITY_USER_BASIC,
        MPI_T_SCOPE_ALL_EQ,
        defaultval,
        "COLLECTIVE", /* category */
        "use the short message algorithm for intercommunicator MPI_Scatter if the send buffer size is < this value (in bytes)");
    rc = MPL_env2int("MPICH_SCATTER_INTER_SHORT_MSG_SIZE", &(MPIR_CVAR_SCATTER_INTER_SHORT_MSG_SIZE));
    MPIR_ERR_CHKANDJUMP1((-1 == rc),mpi_errno,MPI_ERR_OTHER,"**envvarparse","**envvarparse %s","MPICH_SCATTER_INTER_SHORT_MSG_SIZE");
    rc = MPL_env2int("MPIR_PARAM_SCATTER_INTER_SHORT_MSG_SIZE", &(MPIR_CVAR_SCATTER_INTER_SHORT_MSG_SIZE));
    MPIR_ERR_CHKANDJUMP1((-1 == rc),mpi_errno,MPI_ERR_OTHER,"**envvarparse","**envvarparse %s","MPIR_PARAM_SCATTER_INTER_SHORT_MSG_SIZE");
    rc = MPL_env2int("MPIR_CVAR_SCATTER_INTER_SHORT_MSG_SIZE", &(MPIR_CVAR_SCATTER_INTER_SHORT_MSG_SIZE));
    MPIR_ERR_CHKANDJUMP1((-1 == rc),mpi_errno,MPI_ERR_OTHER,"**envvarparse","**envvarparse %s","MPIR_CVAR_SCATTER_INTER_SHORT_MSG_SIZE");

    defaultval.d = 32768;
    MPIR_T_CVAR_REGISTER_STATIC(
        MPI_INT,
        MPIR_CVAR_ALLGATHERV_PIPELINE_MSG_SIZE, /* name */
        &MPIR_CVAR_ALLGATHERV_PIPELINE_MSG_SIZE, /* address */
        1, /* count */
        MPI_T_VERBOSITY_USER_BASIC,
        MPI_T_SCOPE_ALL_EQ,
        defaultval,
        "COLLECTIVE", /* category */
        "The smallest message size that will be used for the pipelined, large-message, ring algorithm in the MPI_Allgatherv implementation.");
    rc = MPL_env2int("MPICH_ALLGATHERV_PIPELINE_MSG_SIZE", &(MPIR_CVAR_ALLGATHERV_PIPELINE_MSG_SIZE));
    MPIR_ERR_CHKANDJUMP1((-1 == rc),mpi_errno,MPI_ERR_OTHER,"**envvarparse","**envvarparse %s","MPICH_ALLGATHERV_PIPELINE_MSG_SIZE");
    rc = MPL_env2int("MPIR_PARAM_ALLGATHERV_PIPELINE_MSG_SIZE", &(MPIR_CVAR_ALLGATHERV_PIPELINE_MSG_SIZE));
    MPIR_ERR_CHKANDJUMP1((-1 == rc),mpi_errno,MPI_ERR_OTHER,"**envvarparse","**envvarparse %s","MPIR_PARAM_ALLGATHERV_PIPELINE_MSG_SIZE");
    rc = MPL_env2int("MPIR_CVAR_ALLGATHERV_PIPELINE_MSG_SIZE", &(MPIR_CVAR_ALLGATHERV_PIPELINE_MSG_SIZE));
    MPIR_ERR_CHKANDJUMP1((-1 == rc),mpi_errno,MPI_ERR_OTHER,"**envvarparse","**envvarparse %s","MPIR_CVAR_ALLGATHERV_PIPELINE_MSG_SIZE");

    defaultval.d = 2;
    MPIR_T_CVAR_REGISTER_STATIC(
        MPI_INT,
        MPIR_CVAR_CTXID_EAGER_SIZE, /* name */
        &MPIR_CVAR_CTXID_EAGER_SIZE, /* address */
        1, /* count */
        MPI_T_VERBOSITY_USER_BASIC,
        MPI_T_SCOPE_ALL_EQ,
        defaultval,
        "THREADS", /* category */
        "The MPIR_CVAR_CTXID_EAGER_SIZE environment variable allows you to specify how many words in the context ID mask will be set aside for the eager allocation protocol.  If the application is running out of context IDs, reducing this value may help.");
    rc = MPL_env2int("MPICH_CTXID_EAGER_SIZE", &(MPIR_CVAR_CTXID_EAGER_SIZE));
    MPIR_ERR_CHKANDJUMP1((-1 == rc),mpi_errno,MPI_ERR_OTHER,"**envvarparse","**envvarparse %s","MPICH_CTXID_EAGER_SIZE");
    rc = MPL_env2int("MPIR_PARAM_CTXID_EAGER_SIZE", &(MPIR_CVAR_CTXID_EAGER_SIZE));
    MPIR_ERR_CHKANDJUMP1((-1 == rc),mpi_errno,MPI_ERR_OTHER,"**envvarparse","**envvarparse %s","MPIR_PARAM_CTXID_EAGER_SIZE");
    rc = MPL_env2int("MPIR_CVAR_CTXID_EAGER_SIZE", &(MPIR_CVAR_CTXID_EAGER_SIZE));
    MPIR_ERR_CHKANDJUMP1((-1 == rc),mpi_errno,MPI_ERR_OTHER,"**envvarparse","**envvarparse %s","MPIR_CVAR_CTXID_EAGER_SIZE");

    defaultval.d = 1;
    MPIR_T_CVAR_REGISTER_STATIC(
        MPI_INT,
        MPIR_CVAR_COMM_SPLIT_USE_QSORT, /* name */
        &MPIR_CVAR_COMM_SPLIT_USE_QSORT, /* address */
        1, /* count */
        MPI_T_VERBOSITY_USER_BASIC,
        MPI_T_SCOPE_ALL_EQ,
        defaultval,
        "COMMUNICATOR", /* category */
        "Use qsort(3) in the implementation of MPI_Comm_split instead of bubble sort.");
    rc = MPL_env2bool("MPICH_COMM_SPLIT_USE_QSORT", &(MPIR_CVAR_COMM_SPLIT_USE_QSORT));
    MPIR_ERR_CHKANDJUMP1((-1 == rc),mpi_errno,MPI_ERR_OTHER,"**envvarparse","**envvarparse %s","MPICH_COMM_SPLIT_USE_QSORT");
    rc = MPL_env2bool("MPIR_PARAM_COMM_SPLIT_USE_QSORT", &(MPIR_CVAR_COMM_SPLIT_USE_QSORT));
    MPIR_ERR_CHKANDJUMP1((-1 == rc),mpi_errno,MPI_ERR_OTHER,"**envvarparse","**envvarparse %s","MPIR_PARAM_COMM_SPLIT_USE_QSORT");
    rc = MPL_env2bool("MPIR_CVAR_COMM_SPLIT_USE_QSORT", &(MPIR_CVAR_COMM_SPLIT_USE_QSORT));
    MPIR_ERR_CHKANDJUMP1((-1 == rc),mpi_errno,MPI_ERR_OTHER,"**envvarparse","**envvarparse %s","MPIR_CVAR_COMM_SPLIT_USE_QSORT");

    defaultval.d = 64;
    MPIR_T_CVAR_REGISTER_STATIC(
        MPI_INT,
        MPIR_CVAR_PROCTABLE_SIZE, /* name */
        &MPIR_CVAR_PROCTABLE_SIZE, /* address */
        1, /* count */
        MPI_T_VERBOSITY_USER_BASIC,
        MPI_T_SCOPE_ALL_EQ,
        defaultval,
        "DEBUGGER", /* category */
        "Size of the \"MPIR\" debugger interface proctable (process table).");
    rc = MPL_env2int("MPICH_PROCTABLE_SIZE", &(MPIR_CVAR_PROCTABLE_SIZE));
    MPIR_ERR_CHKANDJUMP1((-1 == rc),mpi_errno,MPI_ERR_OTHER,"**envvarparse","**envvarparse %s","MPICH_PROCTABLE_SIZE");
    rc = MPL_env2int("MPIR_PARAM_PROCTABLE_SIZE", &(MPIR_CVAR_PROCTABLE_SIZE));
    MPIR_ERR_CHKANDJUMP1((-1 == rc),mpi_errno,MPI_ERR_OTHER,"**envvarparse","**envvarparse %s","MPIR_PARAM_PROCTABLE_SIZE");
    rc = MPL_env2int("MPIR_CVAR_PROCTABLE_SIZE", &(MPIR_CVAR_PROCTABLE_SIZE));
    MPIR_ERR_CHKANDJUMP1((-1 == rc),mpi_errno,MPI_ERR_OTHER,"**envvarparse","**envvarparse %s","MPIR_CVAR_PROCTABLE_SIZE");

    defaultval.d = 0;
    MPIR_T_CVAR_REGISTER_STATIC(
        MPI_INT,
        MPIR_CVAR_PROCTABLE_PRINT, /* name */
        &MPIR_CVAR_PROCTABLE_PRINT, /* address */
        1, /* count */
        MPI_T_VERBOSITY_USER_BASIC,
        MPI_T_SCOPE_ALL_EQ,
        defaultval,
        "DEBUGGER", /* category */
        "If true, dump the proctable entries at MPIR_WaitForDebugger-time.");
    rc = MPL_env2bool("MPICH_PROCTABLE_PRINT", &(MPIR_CVAR_PROCTABLE_PRINT));
    MPIR_ERR_CHKANDJUMP1((-1 == rc),mpi_errno,MPI_ERR_OTHER,"**envvarparse","**envvarparse %s","MPICH_PROCTABLE_PRINT");
    rc = MPL_env2bool("MPIR_PARAM_PROCTABLE_PRINT", &(MPIR_CVAR_PROCTABLE_PRINT));
    MPIR_ERR_CHKANDJUMP1((-1 == rc),mpi_errno,MPI_ERR_OTHER,"**envvarparse","**envvarparse %s","MPIR_PARAM_PROCTABLE_PRINT");
    rc = MPL_env2bool("MPIR_CVAR_PROCTABLE_PRINT", &(MPIR_CVAR_PROCTABLE_PRINT));
    MPIR_ERR_CHKANDJUMP1((-1 == rc),mpi_errno,MPI_ERR_OTHER,"**envvarparse","**envvarparse %s","MPIR_CVAR_PROCTABLE_PRINT");

    defaultval.d = 1;
    MPIR_T_CVAR_REGISTER_STATIC(
        MPI_INT,
        MPIR_CVAR_PRINT_ERROR_STACK, /* name */
        &MPIR_CVAR_PRINT_ERROR_STACK, /* address */
        1, /* count */
        MPI_T_VERBOSITY_USER_BASIC,
        MPI_T_SCOPE_LOCAL,
        defaultval,
        "ERROR_HANDLING", /* category */
        "If true, print an error stack trace at error handling time.");
    rc = MPL_env2bool("MPICH_PRINT_ERROR_STACK", &(MPIR_CVAR_PRINT_ERROR_STACK));
    MPIR_ERR_CHKANDJUMP1((-1 == rc),mpi_errno,MPI_ERR_OTHER,"**envvarparse","**envvarparse %s","MPICH_PRINT_ERROR_STACK");
    rc = MPL_env2bool("MPIR_PARAM_PRINT_ERROR_STACK", &(MPIR_CVAR_PRINT_ERROR_STACK));
    MPIR_ERR_CHKANDJUMP1((-1 == rc),mpi_errno,MPI_ERR_OTHER,"**envvarparse","**envvarparse %s","MPIR_PARAM_PRINT_ERROR_STACK");
    rc = MPL_env2bool("MPIR_CVAR_PRINT_ERROR_STACK", &(MPIR_CVAR_PRINT_ERROR_STACK));
    MPIR_ERR_CHKANDJUMP1((-1 == rc),mpi_errno,MPI_ERR_OTHER,"**envvarparse","**envvarparse %s","MPIR_CVAR_PRINT_ERROR_STACK");

    defaultval.d = 0;
    MPIR_T_CVAR_REGISTER_STATIC(
        MPI_INT,
        MPIR_CVAR_CHOP_ERROR_STACK, /* name */
        &MPIR_CVAR_CHOP_ERROR_STACK, /* address */
        1, /* count */
        MPI_T_VERBOSITY_USER_BASIC,
        MPI_T_SCOPE_LOCAL,
        defaultval,
        "ERROR_HANDLING", /* category */
        "If >0, truncate error stack output lines this many characters wide.  If 0, do not truncate, and if <0 use a sensible default.");
    rc = MPL_env2int("MPICH_CHOP_ERROR_STACK", &(MPIR_CVAR_CHOP_ERROR_STACK));
    MPIR_ERR_CHKANDJUMP1((-1 == rc),mpi_errno,MPI_ERR_OTHER,"**envvarparse","**envvarparse %s","MPICH_CHOP_ERROR_STACK");
    rc = MPL_env2int("MPIR_PARAM_CHOP_ERROR_STACK", &(MPIR_CVAR_CHOP_ERROR_STACK));
    MPIR_ERR_CHKANDJUMP1((-1 == rc),mpi_errno,MPI_ERR_OTHER,"**envvarparse","**envvarparse %s","MPIR_PARAM_CHOP_ERROR_STACK");
    rc = MPL_env2int("MPIR_CVAR_CHOP_ERROR_STACK", &(MPIR_CVAR_CHOP_ERROR_STACK));
    MPIR_ERR_CHKANDJUMP1((-1 == rc),mpi_errno,MPI_ERR_OTHER,"**envvarparse","**envvarparse %s","MPIR_CVAR_CHOP_ERROR_STACK");

    defaultval.str = (char *)NULL;
    MPIR_T_CVAR_REGISTER_STATIC(
        MPI_CHAR,
        MPIR_CVAR_NAMESERV_FILE_PUBDIR, /* name */
        &MPIR_CVAR_NAMESERV_FILE_PUBDIR, /* address */
        MPIR_CVAR_MAX_STRLEN, /* count */
        MPI_T_VERBOSITY_USER_BASIC,
        MPI_T_SCOPE_ALL_EQ,
        defaultval,
        "PROCESS_MANAGER", /* category */
        "Sets the directory to use for MPI service publishing in the file nameserv implementation.  Allows the user to override where the publish and lookup information is placed for connect/accept based applications.");
    MPIR_CVAR_GET_DEFAULT_STRING(MPIR_CVAR_NAMESERV_FILE_PUBDIR, &tmp_str);
    rc = MPL_env2str("MPICH_NAMEPUB_DIR", &tmp_str);
    MPIR_ERR_CHKANDJUMP1((-1 == rc),mpi_errno,MPI_ERR_OTHER,"**envvarparse","**envvarparse %s","MPICH_NAMEPUB_DIR");
    rc = MPL_env2str("MPIR_PARAM_NAMEPUB_DIR", &tmp_str);
    MPIR_ERR_CHKANDJUMP1((-1 == rc),mpi_errno,MPI_ERR_OTHER,"**envvarparse","**envvarparse %s","MPIR_PARAM_NAMEPUB_DIR");
    rc = MPL_env2str("MPIR_CVAR_NAMEPUB_DIR", &tmp_str);
    MPIR_ERR_CHKANDJUMP1((-1 == rc),mpi_errno,MPI_ERR_OTHER,"**envvarparse","**envvarparse %s","MPIR_CVAR_NAMEPUB_DIR");
    rc = MPL_env2str("MPICH_NAMESERV_FILE_PUBDIR", &tmp_str);
    MPIR_ERR_CHKANDJUMP1((-1 == rc),mpi_errno,MPI_ERR_OTHER,"**envvarparse","**envvarparse %s","MPICH_NAMESERV_FILE_PUBDIR");
    rc = MPL_env2str("MPIR_PARAM_NAMESERV_FILE_PUBDIR", &tmp_str);
    MPIR_ERR_CHKANDJUMP1((-1 == rc),mpi_errno,MPI_ERR_OTHER,"**envvarparse","**envvarparse %s","MPIR_PARAM_NAMESERV_FILE_PUBDIR");
    rc = MPL_env2str("MPIR_CVAR_NAMESERV_FILE_PUBDIR", &tmp_str);
    MPIR_ERR_CHKANDJUMP1((-1 == rc),mpi_errno,MPI_ERR_OTHER,"**envvarparse","**envvarparse %s","MPIR_CVAR_NAMESERV_FILE_PUBDIR");
    if (tmp_str != NULL) {
        MPIR_CVAR_NAMESERV_FILE_PUBDIR = MPIU_Strdup(tmp_str);
        MPIR_CVAR_assert(MPIR_CVAR_NAMESERV_FILE_PUBDIR);
        if (MPIR_CVAR_NAMESERV_FILE_PUBDIR == NULL) {
            MPIU_CHKMEM_SETERR(mpi_errno, strlen(tmp_str), "dup of string for MPIR_CVAR_NAMESERV_FILE_PUBDIR");
            goto fn_fail;
        }
    }
    else {
        MPIR_CVAR_NAMESERV_FILE_PUBDIR = NULL;
    }

    defaultval.d = 0;
    MPIR_T_CVAR_REGISTER_STATIC(
        MPI_INT,
        MPIR_CVAR_ABORT_ON_LEAKED_HANDLES, /* name */
        &MPIR_CVAR_ABORT_ON_LEAKED_HANDLES, /* address */
        1, /* count */
        MPI_T_VERBOSITY_USER_BASIC,
        MPI_T_SCOPE_ALL_EQ,
        defaultval,
        "MEMORY", /* category */
        "If true, MPI will call MPI_Abort at MPI_Finalize if any MPI object handles have been leaked.  For example, if MPI_Comm_dup is called without calling a corresponding MPI_Comm_free.  For uninteresting reasons, enabling this option may prevent all known object leaks from being reported.  MPICH must have been configure with \"--enable-g=handlealloc\" or better in order for this functionality to work.");
    rc = MPL_env2bool("MPICH_ABORT_ON_LEAKED_HANDLES", &(MPIR_CVAR_ABORT_ON_LEAKED_HANDLES));
    MPIR_ERR_CHKANDJUMP1((-1 == rc),mpi_errno,MPI_ERR_OTHER,"**envvarparse","**envvarparse %s","MPICH_ABORT_ON_LEAKED_HANDLES");
    rc = MPL_env2bool("MPIR_PARAM_ABORT_ON_LEAKED_HANDLES", &(MPIR_CVAR_ABORT_ON_LEAKED_HANDLES));
    MPIR_ERR_CHKANDJUMP1((-1 == rc),mpi_errno,MPI_ERR_OTHER,"**envvarparse","**envvarparse %s","MPIR_PARAM_ABORT_ON_LEAKED_HANDLES");
    rc = MPL_env2bool("MPIR_CVAR_ABORT_ON_LEAKED_HANDLES", &(MPIR_CVAR_ABORT_ON_LEAKED_HANDLES));
    MPIR_ERR_CHKANDJUMP1((-1 == rc),mpi_errno,MPI_ERR_OTHER,"**envvarparse","**envvarparse %s","MPIR_CVAR_ABORT_ON_LEAKED_HANDLES");

    defaultval.d = 1;
    MPIR_T_CVAR_REGISTER_STATIC(
        MPI_INT,
        MPIR_CVAR_COLL_ALIAS_CHECK, /* name */
        &MPIR_CVAR_COLL_ALIAS_CHECK, /* address */
        1, /* count */
        MPI_T_VERBOSITY_USER_BASIC,
        MPI_T_SCOPE_ALL_EQ,
        defaultval,
        "COLLECTIVE", /* category */
        "Enable checking of aliasing in collective operations");
    rc = MPL_env2int("MPICH_COLL_ALIAS_CHECK", &(MPIR_CVAR_COLL_ALIAS_CHECK));
    MPIR_ERR_CHKANDJUMP1((-1 == rc),mpi_errno,MPI_ERR_OTHER,"**envvarparse","**envvarparse %s","MPICH_COLL_ALIAS_CHECK");
    rc = MPL_env2int("MPIR_PARAM_COLL_ALIAS_CHECK", &(MPIR_CVAR_COLL_ALIAS_CHECK));
    MPIR_ERR_CHKANDJUMP1((-1 == rc),mpi_errno,MPI_ERR_OTHER,"**envvarparse","**envvarparse %s","MPIR_PARAM_COLL_ALIAS_CHECK");
    rc = MPL_env2int("MPIR_CVAR_COLL_ALIAS_CHECK", &(MPIR_CVAR_COLL_ALIAS_CHECK));
    MPIR_ERR_CHKANDJUMP1((-1 == rc),mpi_errno,MPI_ERR_OTHER,"**envvarparse","**envvarparse %s","MPIR_CVAR_COLL_ALIAS_CHECK");

    defaultval.d = 0;
    MPIR_T_CVAR_REGISTER_STATIC(
        MPI_INT,
        MPIR_CVAR_CH3_ENABLE_HCOLL, /* name */
        &MPIR_CVAR_CH3_ENABLE_HCOLL, /* address */
        1, /* count */
        MPI_T_VERBOSITY_USER_BASIC,
        MPI_T_SCOPE_ALL_EQ,
        defaultval,
        "CH3", /* category */
        "If true, enable HCOLL collectives.");
    rc = MPL_env2bool("MPICH_CH3_ENABLE_HCOLL", &(MPIR_CVAR_CH3_ENABLE_HCOLL));
    MPIR_ERR_CHKANDJUMP1((-1 == rc),mpi_errno,MPI_ERR_OTHER,"**envvarparse","**envvarparse %s","MPICH_CH3_ENABLE_HCOLL");
    rc = MPL_env2bool("MPIR_PARAM_CH3_ENABLE_HCOLL", &(MPIR_CVAR_CH3_ENABLE_HCOLL));
    MPIR_ERR_CHKANDJUMP1((-1 == rc),mpi_errno,MPI_ERR_OTHER,"**envvarparse","**envvarparse %s","MPIR_PARAM_CH3_ENABLE_HCOLL");
    rc = MPL_env2bool("MPIR_CVAR_CH3_ENABLE_HCOLL", &(MPIR_CVAR_CH3_ENABLE_HCOLL));
    MPIR_ERR_CHKANDJUMP1((-1 == rc),mpi_errno,MPI_ERR_OTHER,"**envvarparse","**envvarparse %s","MPIR_CVAR_CH3_ENABLE_HCOLL");

    defaultval.d = 0;
    MPIR_T_CVAR_REGISTER_STATIC(
        MPI_INT,
        MPIR_CVAR_CH3_NOLOCAL, /* name */
        &MPIR_CVAR_CH3_NOLOCAL, /* address */
        1, /* count */
        MPI_T_VERBOSITY_USER_BASIC,
        MPI_T_SCOPE_ALL_EQ,
        defaultval,
        "CH3", /* category */
        "If true, force all processes to operate as though all processes are located on another node.  For example, this disables shared memory communication hierarchical collectives.");
    rc = MPL_env2bool("MPICH_CH3_NO_LOCAL", &(MPIR_CVAR_CH3_NOLOCAL));
    MPIR_ERR_CHKANDJUMP1((-1 == rc),mpi_errno,MPI_ERR_OTHER,"**envvarparse","**envvarparse %s","MPICH_CH3_NO_LOCAL");
    rc = MPL_env2bool("MPIR_PARAM_CH3_NO_LOCAL", &(MPIR_CVAR_CH3_NOLOCAL));
    MPIR_ERR_CHKANDJUMP1((-1 == rc),mpi_errno,MPI_ERR_OTHER,"**envvarparse","**envvarparse %s","MPIR_PARAM_CH3_NO_LOCAL");
    rc = MPL_env2bool("MPIR_CVAR_CH3_NO_LOCAL", &(MPIR_CVAR_CH3_NOLOCAL));
    MPIR_ERR_CHKANDJUMP1((-1 == rc),mpi_errno,MPI_ERR_OTHER,"**envvarparse","**envvarparse %s","MPIR_CVAR_CH3_NO_LOCAL");
    rc = MPL_env2bool("MPICH_CH3_NOLOCAL", &(MPIR_CVAR_CH3_NOLOCAL));
    MPIR_ERR_CHKANDJUMP1((-1 == rc),mpi_errno,MPI_ERR_OTHER,"**envvarparse","**envvarparse %s","MPICH_CH3_NOLOCAL");
    rc = MPL_env2bool("MPIR_PARAM_CH3_NOLOCAL", &(MPIR_CVAR_CH3_NOLOCAL));
    MPIR_ERR_CHKANDJUMP1((-1 == rc),mpi_errno,MPI_ERR_OTHER,"**envvarparse","**envvarparse %s","MPIR_PARAM_CH3_NOLOCAL");
    rc = MPL_env2bool("MPIR_CVAR_CH3_NOLOCAL", &(MPIR_CVAR_CH3_NOLOCAL));
    MPIR_ERR_CHKANDJUMP1((-1 == rc),mpi_errno,MPI_ERR_OTHER,"**envvarparse","**envvarparse %s","MPIR_CVAR_CH3_NOLOCAL");

    defaultval.d = 0;
    MPIR_T_CVAR_REGISTER_STATIC(
        MPI_INT,
        MPIR_CVAR_CH3_ODD_EVEN_CLIQUES, /* name */
        &MPIR_CVAR_CH3_ODD_EVEN_CLIQUES, /* address */
        1, /* count */
        MPI_T_VERBOSITY_USER_BASIC,
        MPI_T_SCOPE_ALL_EQ,
        defaultval,
        "CH3", /* category */
        "If true, odd procs on a node are seen as local to each other, and even procs on a node are seen as local to each other.  Used for debugging on a single machine.");
    rc = MPL_env2bool("MPICH_CH3_EVEN_ODD_CLIQUES", &(MPIR_CVAR_CH3_ODD_EVEN_CLIQUES));
    MPIR_ERR_CHKANDJUMP1((-1 == rc),mpi_errno,MPI_ERR_OTHER,"**envvarparse","**envvarparse %s","MPICH_CH3_EVEN_ODD_CLIQUES");
    rc = MPL_env2bool("MPIR_PARAM_CH3_EVEN_ODD_CLIQUES", &(MPIR_CVAR_CH3_ODD_EVEN_CLIQUES));
    MPIR_ERR_CHKANDJUMP1((-1 == rc),mpi_errno,MPI_ERR_OTHER,"**envvarparse","**envvarparse %s","MPIR_PARAM_CH3_EVEN_ODD_CLIQUES");
    rc = MPL_env2bool("MPIR_CVAR_CH3_EVEN_ODD_CLIQUES", &(MPIR_CVAR_CH3_ODD_EVEN_CLIQUES));
    MPIR_ERR_CHKANDJUMP1((-1 == rc),mpi_errno,MPI_ERR_OTHER,"**envvarparse","**envvarparse %s","MPIR_CVAR_CH3_EVEN_ODD_CLIQUES");
    rc = MPL_env2bool("MPICH_CH3_ODD_EVEN_CLIQUES", &(MPIR_CVAR_CH3_ODD_EVEN_CLIQUES));
    MPIR_ERR_CHKANDJUMP1((-1 == rc),mpi_errno,MPI_ERR_OTHER,"**envvarparse","**envvarparse %s","MPICH_CH3_ODD_EVEN_CLIQUES");
    rc = MPL_env2bool("MPIR_PARAM_CH3_ODD_EVEN_CLIQUES", &(MPIR_CVAR_CH3_ODD_EVEN_CLIQUES));
    MPIR_ERR_CHKANDJUMP1((-1 == rc),mpi_errno,MPI_ERR_OTHER,"**envvarparse","**envvarparse %s","MPIR_PARAM_CH3_ODD_EVEN_CLIQUES");
    rc = MPL_env2bool("MPIR_CVAR_CH3_ODD_EVEN_CLIQUES", &(MPIR_CVAR_CH3_ODD_EVEN_CLIQUES));
    MPIR_ERR_CHKANDJUMP1((-1 == rc),mpi_errno,MPI_ERR_OTHER,"**envvarparse","**envvarparse %s","MPIR_CVAR_CH3_ODD_EVEN_CLIQUES");

    defaultval.d = 131072;
    MPIR_T_CVAR_REGISTER_STATIC(
        MPI_INT,
        MPIR_CVAR_CH3_EAGER_MAX_MSG_SIZE, /* name */
        &MPIR_CVAR_CH3_EAGER_MAX_MSG_SIZE, /* address */
        1, /* count */
        MPI_T_VERBOSITY_USER_BASIC,
        MPI_T_SCOPE_ALL_EQ,
        defaultval,
        "CH3", /* category */
        "This cvar controls the message size at which CH3 switches from eager to rendezvous mode.");
    rc = MPL_env2int("MPICH_CH3_EAGER_MAX_MSG_SIZE", &(MPIR_CVAR_CH3_EAGER_MAX_MSG_SIZE));
    MPIR_ERR_CHKANDJUMP1((-1 == rc),mpi_errno,MPI_ERR_OTHER,"**envvarparse","**envvarparse %s","MPICH_CH3_EAGER_MAX_MSG_SIZE");
    rc = MPL_env2int("MPIR_PARAM_CH3_EAGER_MAX_MSG_SIZE", &(MPIR_CVAR_CH3_EAGER_MAX_MSG_SIZE));
    MPIR_ERR_CHKANDJUMP1((-1 == rc),mpi_errno,MPI_ERR_OTHER,"**envvarparse","**envvarparse %s","MPIR_PARAM_CH3_EAGER_MAX_MSG_SIZE");
    rc = MPL_env2int("MPIR_CVAR_CH3_EAGER_MAX_MSG_SIZE", &(MPIR_CVAR_CH3_EAGER_MAX_MSG_SIZE));
    MPIR_ERR_CHKANDJUMP1((-1 == rc),mpi_errno,MPI_ERR_OTHER,"**envvarparse","**envvarparse %s","MPIR_CVAR_CH3_EAGER_MAX_MSG_SIZE");

    defaultval.d = 262144;
    MPIR_T_CVAR_REGISTER_STATIC(
        MPI_INT,
        MPIR_CVAR_CH3_RMA_SLOTS_SIZE, /* name */
        &MPIR_CVAR_CH3_RMA_SLOTS_SIZE, /* address */
        1, /* count */
        MPI_T_VERBOSITY_USER_BASIC,
        MPI_T_SCOPE_ALL_EQ,
        defaultval,
        "CH3", /* category */
        "Number of RMA slots during window creation. Each slot contains a linked list of target elements. The distribution of ranks among slots follows a round-robin pattern. Requires a positive value.");
    rc = MPL_env2int("MPICH_CH3_RMA_SLOTS_SIZE", &(MPIR_CVAR_CH3_RMA_SLOTS_SIZE));
    MPIR_ERR_CHKANDJUMP1((-1 == rc),mpi_errno,MPI_ERR_OTHER,"**envvarparse","**envvarparse %s","MPICH_CH3_RMA_SLOTS_SIZE");
    rc = MPL_env2int("MPIR_PARAM_CH3_RMA_SLOTS_SIZE", &(MPIR_CVAR_CH3_RMA_SLOTS_SIZE));
    MPIR_ERR_CHKANDJUMP1((-1 == rc),mpi_errno,MPI_ERR_OTHER,"**envvarparse","**envvarparse %s","MPIR_PARAM_CH3_RMA_SLOTS_SIZE");
    rc = MPL_env2int("MPIR_CVAR_CH3_RMA_SLOTS_SIZE", &(MPIR_CVAR_CH3_RMA_SLOTS_SIZE));
    MPIR_ERR_CHKANDJUMP1((-1 == rc),mpi_errno,MPI_ERR_OTHER,"**envvarparse","**envvarparse %s","MPIR_CVAR_CH3_RMA_SLOTS_SIZE");

    defaultval.d = 655360;
    MPIR_T_CVAR_REGISTER_STATIC(
        MPI_INT,
        MPIR_CVAR_CH3_RMA_TARGET_LOCK_DATA_BYTES, /* name */
        &MPIR_CVAR_CH3_RMA_TARGET_LOCK_DATA_BYTES, /* address */
        1, /* count */
        MPI_T_VERBOSITY_USER_BASIC,
        MPI_T_SCOPE_ALL_EQ,
        defaultval,
        "CH3", /* category */
        "Size (in bytes) of available lock data this window can provided. If current buffered lock data is more than this value, the process will drop the upcoming operation data. Requires a positive calue.");
    rc = MPL_env2int("MPICH_CH3_RMA_TARGET_LOCK_DATA_BYTES", &(MPIR_CVAR_CH3_RMA_TARGET_LOCK_DATA_BYTES));
    MPIR_ERR_CHKANDJUMP1((-1 == rc),mpi_errno,MPI_ERR_OTHER,"**envvarparse","**envvarparse %s","MPICH_CH3_RMA_TARGET_LOCK_DATA_BYTES");
    rc = MPL_env2int("MPIR_PARAM_CH3_RMA_TARGET_LOCK_DATA_BYTES", &(MPIR_CVAR_CH3_RMA_TARGET_LOCK_DATA_BYTES));
    MPIR_ERR_CHKANDJUMP1((-1 == rc),mpi_errno,MPI_ERR_OTHER,"**envvarparse","**envvarparse %s","MPIR_PARAM_CH3_RMA_TARGET_LOCK_DATA_BYTES");
    rc = MPL_env2int("MPIR_CVAR_CH3_RMA_TARGET_LOCK_DATA_BYTES", &(MPIR_CVAR_CH3_RMA_TARGET_LOCK_DATA_BYTES));
    MPIR_ERR_CHKANDJUMP1((-1 == rc),mpi_errno,MPI_ERR_OTHER,"**envvarparse","**envvarparse %s","MPIR_CVAR_CH3_RMA_TARGET_LOCK_DATA_BYTES");

    defaultval.d = 65536;
    MPIR_T_CVAR_REGISTER_STATIC(
        MPI_INT,
        MPIR_CVAR_CH3_RMA_OP_PIGGYBACK_LOCK_DATA_SIZE, /* name */
        &MPIR_CVAR_CH3_RMA_OP_PIGGYBACK_LOCK_DATA_SIZE, /* address */
        1, /* count */
        MPI_T_VERBOSITY_USER_BASIC,
        MPI_T_SCOPE_ALL_EQ,
        defaultval,
        "CH3", /* category */
        "Specify the threshold of data size of a RMA operation which can be piggybacked with a LOCK message. It is always a positive value and should not be smaller than MPIDI_RMA_IMMED_BYTES. If user sets it as a small value, for middle and large data size, we will lose performance because of always waiting for round-trip of LOCK synchronization; if user sets it as a large value, we need to consume more memory on target side to buffer this lock request when lock is not satisfied.");
    rc = MPL_env2int("MPICH_CH3_RMA_OP_PIGGYBACK_LOCK_DATA_SIZE", &(MPIR_CVAR_CH3_RMA_OP_PIGGYBACK_LOCK_DATA_SIZE));
    MPIR_ERR_CHKANDJUMP1((-1 == rc),mpi_errno,MPI_ERR_OTHER,"**envvarparse","**envvarparse %s","MPICH_CH3_RMA_OP_PIGGYBACK_LOCK_DATA_SIZE");
    rc = MPL_env2int("MPIR_PARAM_CH3_RMA_OP_PIGGYBACK_LOCK_DATA_SIZE", &(MPIR_CVAR_CH3_RMA_OP_PIGGYBACK_LOCK_DATA_SIZE));
    MPIR_ERR_CHKANDJUMP1((-1 == rc),mpi_errno,MPI_ERR_OTHER,"**envvarparse","**envvarparse %s","MPIR_PARAM_CH3_RMA_OP_PIGGYBACK_LOCK_DATA_SIZE");
    rc = MPL_env2int("MPIR_CVAR_CH3_RMA_OP_PIGGYBACK_LOCK_DATA_SIZE", &(MPIR_CVAR_CH3_RMA_OP_PIGGYBACK_LOCK_DATA_SIZE));
    MPIR_ERR_CHKANDJUMP1((-1 == rc),mpi_errno,MPI_ERR_OTHER,"**envvarparse","**envvarparse %s","MPIR_CVAR_CH3_RMA_OP_PIGGYBACK_LOCK_DATA_SIZE");

    defaultval.d = 1024;
    MPIR_T_CVAR_REGISTER_STATIC(
        MPI_INT,
        MPIR_CVAR_CH3_RMA_SCALABLE_FENCE_PROCESS_NUM, /* name */
        &MPIR_CVAR_CH3_RMA_SCALABLE_FENCE_PROCESS_NUM, /* address */
        1, /* count */
        MPI_T_VERBOSITY_USER_BASIC,
        MPI_T_SCOPE_ALL_EQ,
        defaultval,
        "CH3", /* category */
        "Specify the threshold of switching the algorithm used in FENCE from the basic algorithm to the scalable algorithm. The value can be nagative, zero or positive. When the number of processes is larger than or equal to this value, FENCE will use a scalable algorithm which do not use O(P) data structure; when the number of processes is smaller than the value, FENCE will use a basic but fast algorithm which requires an O(P) data structure.");
    rc = MPL_env2int("MPICH_CH3_RMA_SCALABLE_FENCE_PROCESS_NUM", &(MPIR_CVAR_CH3_RMA_SCALABLE_FENCE_PROCESS_NUM));
    MPIR_ERR_CHKANDJUMP1((-1 == rc),mpi_errno,MPI_ERR_OTHER,"**envvarparse","**envvarparse %s","MPICH_CH3_RMA_SCALABLE_FENCE_PROCESS_NUM");
    rc = MPL_env2int("MPIR_PARAM_CH3_RMA_SCALABLE_FENCE_PROCESS_NUM", &(MPIR_CVAR_CH3_RMA_SCALABLE_FENCE_PROCESS_NUM));
    MPIR_ERR_CHKANDJUMP1((-1 == rc),mpi_errno,MPI_ERR_OTHER,"**envvarparse","**envvarparse %s","MPIR_PARAM_CH3_RMA_SCALABLE_FENCE_PROCESS_NUM");
    rc = MPL_env2int("MPIR_CVAR_CH3_RMA_SCALABLE_FENCE_PROCESS_NUM", &(MPIR_CVAR_CH3_RMA_SCALABLE_FENCE_PROCESS_NUM));
    MPIR_ERR_CHKANDJUMP1((-1 == rc),mpi_errno,MPI_ERR_OTHER,"**envvarparse","**envvarparse %s","MPIR_CVAR_CH3_RMA_SCALABLE_FENCE_PROCESS_NUM");

    defaultval.d = 0;
    MPIR_T_CVAR_REGISTER_STATIC(
        MPI_INT,
        MPIR_CVAR_CH3_RMA_DELAY_ISSUING_FOR_PIGGYBACKING, /* name */
        &MPIR_CVAR_CH3_RMA_DELAY_ISSUING_FOR_PIGGYBACKING, /* address */
        1, /* count */
        MPI_T_VERBOSITY_USER_BASIC,
        MPI_T_SCOPE_ALL_EQ,
        defaultval,
        "CH3", /* category */
        "Specify if delay issuing of RMA operations for piggybacking LOCK/UNLOCK/FLUSH is enabled. It can be either 0 or 1. When it is set to 1, the issuing of LOCK message is delayed until origin process see the first RMA operation and piggyback LOCK with that operation, and the origin process always keeps the current last operation until the ending synchronization call in order to piggyback UNLOCK/FLUSH with that operation. When it is set to 0, in WIN_LOCK/UNLOCK case, the LOCK message is sent out as early as possible, in WIN_LOCK_ALL/UNLOCK_ALL case, the origin process still tries to piggyback LOCK message with the first operation; for UNLOCK/FLUSH message, the origin process no longer keeps the current last operation but only piggyback UNLOCK/FLUSH if there is an operation avaliable in the ending synchronization call.");
    rc = MPL_env2int("MPICH_CH3_RMA_DELAY_ISSUING_FOR_PIGGYBACKING", &(MPIR_CVAR_CH3_RMA_DELAY_ISSUING_FOR_PIGGYBACKING));
    MPIR_ERR_CHKANDJUMP1((-1 == rc),mpi_errno,MPI_ERR_OTHER,"**envvarparse","**envvarparse %s","MPICH_CH3_RMA_DELAY_ISSUING_FOR_PIGGYBACKING");
    rc = MPL_env2int("MPIR_PARAM_CH3_RMA_DELAY_ISSUING_FOR_PIGGYBACKING", &(MPIR_CVAR_CH3_RMA_DELAY_ISSUING_FOR_PIGGYBACKING));
    MPIR_ERR_CHKANDJUMP1((-1 == rc),mpi_errno,MPI_ERR_OTHER,"**envvarparse","**envvarparse %s","MPIR_PARAM_CH3_RMA_DELAY_ISSUING_FOR_PIGGYBACKING");
    rc = MPL_env2int("MPIR_CVAR_CH3_RMA_DELAY_ISSUING_FOR_PIGGYBACKING", &(MPIR_CVAR_CH3_RMA_DELAY_ISSUING_FOR_PIGGYBACKING));
    MPIR_ERR_CHKANDJUMP1((-1 == rc),mpi_errno,MPI_ERR_OTHER,"**envvarparse","**envvarparse %s","MPIR_CVAR_CH3_RMA_DELAY_ISSUING_FOR_PIGGYBACKING");

    defaultval.d = 65536;
    MPIR_T_CVAR_REGISTER_STATIC(
        MPI_INT,
        MPIR_CVAR_CH3_RMA_ACTIVE_REQ_THRESHOLD, /* name */
        &MPIR_CVAR_CH3_RMA_ACTIVE_REQ_THRESHOLD, /* address */
        1, /* count */
        MPI_T_VERBOSITY_USER_BASIC,
        MPI_T_SCOPE_ALL_EQ,
        defaultval,
        "CH3", /* category */
        "Threshold of number of active requests to trigger blocking waiting in operation routines. When the value is negative, we never blockingly wait in operation routines. When the value is zero, we always trigger blocking waiting in operation routines to wait until no. of active requests becomes zero. When the value is positive, we do blocking waiting in operation routines to wait until no. of active requests being reduced to this value.");
    rc = MPL_env2int("MPICH_CH3_RMA_ACTIVE_REQ_THRESHOLD", &(MPIR_CVAR_CH3_RMA_ACTIVE_REQ_THRESHOLD));
    MPIR_ERR_CHKANDJUMP1((-1 == rc),mpi_errno,MPI_ERR_OTHER,"**envvarparse","**envvarparse %s","MPICH_CH3_RMA_ACTIVE_REQ_THRESHOLD");
    rc = MPL_env2int("MPIR_PARAM_CH3_RMA_ACTIVE_REQ_THRESHOLD", &(MPIR_CVAR_CH3_RMA_ACTIVE_REQ_THRESHOLD));
    MPIR_ERR_CHKANDJUMP1((-1 == rc),mpi_errno,MPI_ERR_OTHER,"**envvarparse","**envvarparse %s","MPIR_PARAM_CH3_RMA_ACTIVE_REQ_THRESHOLD");
    rc = MPL_env2int("MPIR_CVAR_CH3_RMA_ACTIVE_REQ_THRESHOLD", &(MPIR_CVAR_CH3_RMA_ACTIVE_REQ_THRESHOLD));
    MPIR_ERR_CHKANDJUMP1((-1 == rc),mpi_errno,MPI_ERR_OTHER,"**envvarparse","**envvarparse %s","MPIR_CVAR_CH3_RMA_ACTIVE_REQ_THRESHOLD");

    defaultval.d = 128;
    MPIR_T_CVAR_REGISTER_STATIC(
        MPI_INT,
        MPIR_CVAR_CH3_RMA_POKE_PROGRESS_REQ_THRESHOLD, /* name */
        &MPIR_CVAR_CH3_RMA_POKE_PROGRESS_REQ_THRESHOLD, /* address */
        1, /* count */
        MPI_T_VERBOSITY_USER_BASIC,
        MPI_T_SCOPE_ALL_EQ,
        defaultval,
        "CH3", /* category */
        "Threshold at which the RMA implementation attempts to complete requests while completing RMA operations and while using the lazy synchonization approach.  Change this value if programs fail because they run out of requests or other internal resources");
    rc = MPL_env2int("MPICH_CH3_RMA_POKE_PROGRESS_REQ_THRESHOLD", &(MPIR_CVAR_CH3_RMA_POKE_PROGRESS_REQ_THRESHOLD));
    MPIR_ERR_CHKANDJUMP1((-1 == rc),mpi_errno,MPI_ERR_OTHER,"**envvarparse","**envvarparse %s","MPICH_CH3_RMA_POKE_PROGRESS_REQ_THRESHOLD");
    rc = MPL_env2int("MPIR_PARAM_CH3_RMA_POKE_PROGRESS_REQ_THRESHOLD", &(MPIR_CVAR_CH3_RMA_POKE_PROGRESS_REQ_THRESHOLD));
    MPIR_ERR_CHKANDJUMP1((-1 == rc),mpi_errno,MPI_ERR_OTHER,"**envvarparse","**envvarparse %s","MPIR_PARAM_CH3_RMA_POKE_PROGRESS_REQ_THRESHOLD");
    rc = MPL_env2int("MPIR_CVAR_CH3_RMA_POKE_PROGRESS_REQ_THRESHOLD", &(MPIR_CVAR_CH3_RMA_POKE_PROGRESS_REQ_THRESHOLD));
    MPIR_ERR_CHKANDJUMP1((-1 == rc),mpi_errno,MPI_ERR_OTHER,"**envvarparse","**envvarparse %s","MPIR_CVAR_CH3_RMA_POKE_PROGRESS_REQ_THRESHOLD");

    defaultval.d = 256;
    MPIR_T_CVAR_REGISTER_STATIC(
        MPI_INT,
        MPIR_CVAR_CH3_RMA_OP_WIN_POOL_SIZE, /* name */
        &MPIR_CVAR_CH3_RMA_OP_WIN_POOL_SIZE, /* address */
        1, /* count */
        MPI_T_VERBOSITY_USER_BASIC,
        MPI_T_SCOPE_ALL_EQ,
        defaultval,
        "CH3", /* category */
        "Size of the window-private RMA operations pool (in number of operations) that stores information about RMA operations that could not be issued immediately.  Requires a positive value.");
    rc = MPL_env2int("MPICH_CH3_RMA_OP_WIN_POOL_SIZE", &(MPIR_CVAR_CH3_RMA_OP_WIN_POOL_SIZE));
    MPIR_ERR_CHKANDJUMP1((-1 == rc),mpi_errno,MPI_ERR_OTHER,"**envvarparse","**envvarparse %s","MPICH_CH3_RMA_OP_WIN_POOL_SIZE");
    rc = MPL_env2int("MPIR_PARAM_CH3_RMA_OP_WIN_POOL_SIZE", &(MPIR_CVAR_CH3_RMA_OP_WIN_POOL_SIZE));
    MPIR_ERR_CHKANDJUMP1((-1 == rc),mpi_errno,MPI_ERR_OTHER,"**envvarparse","**envvarparse %s","MPIR_PARAM_CH3_RMA_OP_WIN_POOL_SIZE");
    rc = MPL_env2int("MPIR_CVAR_CH3_RMA_OP_WIN_POOL_SIZE", &(MPIR_CVAR_CH3_RMA_OP_WIN_POOL_SIZE));
    MPIR_ERR_CHKANDJUMP1((-1 == rc),mpi_errno,MPI_ERR_OTHER,"**envvarparse","**envvarparse %s","MPIR_CVAR_CH3_RMA_OP_WIN_POOL_SIZE");

    defaultval.d = 16384;
    MPIR_T_CVAR_REGISTER_STATIC(
        MPI_INT,
        MPIR_CVAR_CH3_RMA_OP_GLOBAL_POOL_SIZE, /* name */
        &MPIR_CVAR_CH3_RMA_OP_GLOBAL_POOL_SIZE, /* address */
        1, /* count */
        MPI_T_VERBOSITY_USER_BASIC,
        MPI_T_SCOPE_ALL_EQ,
        defaultval,
        "CH3", /* category */
        "Size of the Global RMA operations pool (in number of operations) that stores information about RMA operations that could not be issued immediatly.  Requires a positive value.");
    rc = MPL_env2int("MPICH_CH3_RMA_OP_GLOBAL_POOL_SIZE", &(MPIR_CVAR_CH3_RMA_OP_GLOBAL_POOL_SIZE));
    MPIR_ERR_CHKANDJUMP1((-1 == rc),mpi_errno,MPI_ERR_OTHER,"**envvarparse","**envvarparse %s","MPICH_CH3_RMA_OP_GLOBAL_POOL_SIZE");
    rc = MPL_env2int("MPIR_PARAM_CH3_RMA_OP_GLOBAL_POOL_SIZE", &(MPIR_CVAR_CH3_RMA_OP_GLOBAL_POOL_SIZE));
    MPIR_ERR_CHKANDJUMP1((-1 == rc),mpi_errno,MPI_ERR_OTHER,"**envvarparse","**envvarparse %s","MPIR_PARAM_CH3_RMA_OP_GLOBAL_POOL_SIZE");
    rc = MPL_env2int("MPIR_CVAR_CH3_RMA_OP_GLOBAL_POOL_SIZE", &(MPIR_CVAR_CH3_RMA_OP_GLOBAL_POOL_SIZE));
    MPIR_ERR_CHKANDJUMP1((-1 == rc),mpi_errno,MPI_ERR_OTHER,"**envvarparse","**envvarparse %s","MPIR_CVAR_CH3_RMA_OP_GLOBAL_POOL_SIZE");

    defaultval.d = 256;
    MPIR_T_CVAR_REGISTER_STATIC(
        MPI_INT,
        MPIR_CVAR_CH3_RMA_TARGET_WIN_POOL_SIZE, /* name */
        &MPIR_CVAR_CH3_RMA_TARGET_WIN_POOL_SIZE, /* address */
        1, /* count */
        MPI_T_VERBOSITY_USER_BASIC,
        MPI_T_SCOPE_ALL_EQ,
        defaultval,
        "CH3", /* category */
        "Size of the window-private RMA target pool (in number of targets) that stores information about RMA targets that could not be issued immediately.  Requires a positive value.");
    rc = MPL_env2int("MPICH_CH3_RMA_TARGET_WIN_POOL_SIZE", &(MPIR_CVAR_CH3_RMA_TARGET_WIN_POOL_SIZE));
    MPIR_ERR_CHKANDJUMP1((-1 == rc),mpi_errno,MPI_ERR_OTHER,"**envvarparse","**envvarparse %s","MPICH_CH3_RMA_TARGET_WIN_POOL_SIZE");
    rc = MPL_env2int("MPIR_PARAM_CH3_RMA_TARGET_WIN_POOL_SIZE", &(MPIR_CVAR_CH3_RMA_TARGET_WIN_POOL_SIZE));
    MPIR_ERR_CHKANDJUMP1((-1 == rc),mpi_errno,MPI_ERR_OTHER,"**envvarparse","**envvarparse %s","MPIR_PARAM_CH3_RMA_TARGET_WIN_POOL_SIZE");
    rc = MPL_env2int("MPIR_CVAR_CH3_RMA_TARGET_WIN_POOL_SIZE", &(MPIR_CVAR_CH3_RMA_TARGET_WIN_POOL_SIZE));
    MPIR_ERR_CHKANDJUMP1((-1 == rc),mpi_errno,MPI_ERR_OTHER,"**envvarparse","**envvarparse %s","MPIR_CVAR_CH3_RMA_TARGET_WIN_POOL_SIZE");

    defaultval.d = 16384;
    MPIR_T_CVAR_REGISTER_STATIC(
        MPI_INT,
        MPIR_CVAR_CH3_RMA_TARGET_GLOBAL_POOL_SIZE, /* name */
        &MPIR_CVAR_CH3_RMA_TARGET_GLOBAL_POOL_SIZE, /* address */
        1, /* count */
        MPI_T_VERBOSITY_USER_BASIC,
        MPI_T_SCOPE_ALL_EQ,
        defaultval,
        "CH3", /* category */
        "Size of the Global RMA targets pool (in number of targets) that stores information about RMA targets that could not be issued immediatly.  Requires a positive value.");
    rc = MPL_env2int("MPICH_CH3_RMA_TARGET_GLOBAL_POOL_SIZE", &(MPIR_CVAR_CH3_RMA_TARGET_GLOBAL_POOL_SIZE));
    MPIR_ERR_CHKANDJUMP1((-1 == rc),mpi_errno,MPI_ERR_OTHER,"**envvarparse","**envvarparse %s","MPICH_CH3_RMA_TARGET_GLOBAL_POOL_SIZE");
    rc = MPL_env2int("MPIR_PARAM_CH3_RMA_TARGET_GLOBAL_POOL_SIZE", &(MPIR_CVAR_CH3_RMA_TARGET_GLOBAL_POOL_SIZE));
    MPIR_ERR_CHKANDJUMP1((-1 == rc),mpi_errno,MPI_ERR_OTHER,"**envvarparse","**envvarparse %s","MPIR_PARAM_CH3_RMA_TARGET_GLOBAL_POOL_SIZE");
    rc = MPL_env2int("MPIR_CVAR_CH3_RMA_TARGET_GLOBAL_POOL_SIZE", &(MPIR_CVAR_CH3_RMA_TARGET_GLOBAL_POOL_SIZE));
    MPIR_ERR_CHKANDJUMP1((-1 == rc),mpi_errno,MPI_ERR_OTHER,"**envvarparse","**envvarparse %s","MPIR_CVAR_CH3_RMA_TARGET_GLOBAL_POOL_SIZE");

    defaultval.d = 256;
    MPIR_T_CVAR_REGISTER_STATIC(
        MPI_INT,
        MPIR_CVAR_CH3_RMA_TARGET_LOCK_ENTRY_WIN_POOL_SIZE, /* name */
        &MPIR_CVAR_CH3_RMA_TARGET_LOCK_ENTRY_WIN_POOL_SIZE, /* address */
        1, /* count */
        MPI_T_VERBOSITY_USER_BASIC,
        MPI_T_SCOPE_ALL_EQ,
        defaultval,
        "CH3", /* category */
        "Size of the window-private RMA lock entries pool (in number of lock entries) that stores information about RMA lock requests that could not be satisfied immediatly.  Requires a positive value.");
    rc = MPL_env2int("MPICH_CH3_RMA_TARGET_LOCK_ENTRY_WIN_POOL_SIZE", &(MPIR_CVAR_CH3_RMA_TARGET_LOCK_ENTRY_WIN_POOL_SIZE));
    MPIR_ERR_CHKANDJUMP1((-1 == rc),mpi_errno,MPI_ERR_OTHER,"**envvarparse","**envvarparse %s","MPICH_CH3_RMA_TARGET_LOCK_ENTRY_WIN_POOL_SIZE");
    rc = MPL_env2int("MPIR_PARAM_CH3_RMA_TARGET_LOCK_ENTRY_WIN_POOL_SIZE", &(MPIR_CVAR_CH3_RMA_TARGET_LOCK_ENTRY_WIN_POOL_SIZE));
    MPIR_ERR_CHKANDJUMP1((-1 == rc),mpi_errno,MPI_ERR_OTHER,"**envvarparse","**envvarparse %s","MPIR_PARAM_CH3_RMA_TARGET_LOCK_ENTRY_WIN_POOL_SIZE");
    rc = MPL_env2int("MPIR_CVAR_CH3_RMA_TARGET_LOCK_ENTRY_WIN_POOL_SIZE", &(MPIR_CVAR_CH3_RMA_TARGET_LOCK_ENTRY_WIN_POOL_SIZE));
    MPIR_ERR_CHKANDJUMP1((-1 == rc),mpi_errno,MPI_ERR_OTHER,"**envvarparse","**envvarparse %s","MPIR_CVAR_CH3_RMA_TARGET_LOCK_ENTRY_WIN_POOL_SIZE");

    defaultval.d = 0;
    MPIR_T_CVAR_REGISTER_STATIC(
        MPI_INT,
        MPIR_CVAR_ENABLE_FT, /* name */
        &MPIR_CVAR_ENABLE_FT, /* address */
        1, /* count */
        MPI_T_VERBOSITY_USER_BASIC,
        MPI_T_SCOPE_ALL_EQ,
        defaultval,
        "FT", /* category */
        "Enable fault tolerance functions");
    rc = MPL_env2bool("MPICH_ENABLE_FT", &(MPIR_CVAR_ENABLE_FT));
    MPIR_ERR_CHKANDJUMP1((-1 == rc),mpi_errno,MPI_ERR_OTHER,"**envvarparse","**envvarparse %s","MPICH_ENABLE_FT");
    rc = MPL_env2bool("MPIR_PARAM_ENABLE_FT", &(MPIR_CVAR_ENABLE_FT));
    MPIR_ERR_CHKANDJUMP1((-1 == rc),mpi_errno,MPI_ERR_OTHER,"**envvarparse","**envvarparse %s","MPIR_PARAM_ENABLE_FT");
    rc = MPL_env2bool("MPIR_CVAR_ENABLE_FT", &(MPIR_CVAR_ENABLE_FT));
    MPIR_ERR_CHKANDJUMP1((-1 == rc),mpi_errno,MPI_ERR_OTHER,"**envvarparse","**envvarparse %s","MPIR_CVAR_ENABLE_FT");

    defaultval.d = -1;
    MPIR_T_CVAR_REGISTER_STATIC(
        MPI_INT,
        MPIR_CVAR_NEMESIS_SHM_EAGER_MAX_SZ, /* name */
        &MPIR_CVAR_NEMESIS_SHM_EAGER_MAX_SZ, /* address */
        1, /* count */
        MPI_T_VERBOSITY_USER_BASIC,
        MPI_T_SCOPE_ALL_EQ,
        defaultval,
        "NEMESIS", /* category */
        "This cvar controls the message size at which Nemesis switches from eager to rendezvous mode for shared memory. If this cvar is set to -1, then Nemesis will choose an appropriate value.");
    rc = MPL_env2int("MPICH_NEMESIS_SHM_EAGER_MAX_SZ", &(MPIR_CVAR_NEMESIS_SHM_EAGER_MAX_SZ));
    MPIR_ERR_CHKANDJUMP1((-1 == rc),mpi_errno,MPI_ERR_OTHER,"**envvarparse","**envvarparse %s","MPICH_NEMESIS_SHM_EAGER_MAX_SZ");
    rc = MPL_env2int("MPIR_PARAM_NEMESIS_SHM_EAGER_MAX_SZ", &(MPIR_CVAR_NEMESIS_SHM_EAGER_MAX_SZ));
    MPIR_ERR_CHKANDJUMP1((-1 == rc),mpi_errno,MPI_ERR_OTHER,"**envvarparse","**envvarparse %s","MPIR_PARAM_NEMESIS_SHM_EAGER_MAX_SZ");
    rc = MPL_env2int("MPIR_CVAR_NEMESIS_SHM_EAGER_MAX_SZ", &(MPIR_CVAR_NEMESIS_SHM_EAGER_MAX_SZ));
    MPIR_ERR_CHKANDJUMP1((-1 == rc),mpi_errno,MPI_ERR_OTHER,"**envvarparse","**envvarparse %s","MPIR_CVAR_NEMESIS_SHM_EAGER_MAX_SZ");

    defaultval.d = -2;
    MPIR_T_CVAR_REGISTER_STATIC(
        MPI_INT,
        MPIR_CVAR_NEMESIS_SHM_READY_EAGER_MAX_SZ, /* name */
        &MPIR_CVAR_NEMESIS_SHM_READY_EAGER_MAX_SZ, /* address */
        1, /* count */
        MPI_T_VERBOSITY_USER_BASIC,
        MPI_T_SCOPE_ALL_EQ,
        defaultval,
        "NEMESIS", /* category */
        "This cvar controls the message size at which Nemesis switches from eager to rendezvous mode for ready-send messages.  If this cvar is set to -1, then ready messages will always be sent eagerly.  If this cvar is set to -2, then Nemesis will choose an appropriate value.");
    rc = MPL_env2int("MPICH_NEMESIS_SHM_READY_EAGER_MAX_SZ", &(MPIR_CVAR_NEMESIS_SHM_READY_EAGER_MAX_SZ));
    MPIR_ERR_CHKANDJUMP1((-1 == rc),mpi_errno,MPI_ERR_OTHER,"**envvarparse","**envvarparse %s","MPICH_NEMESIS_SHM_READY_EAGER_MAX_SZ");
    rc = MPL_env2int("MPIR_PARAM_NEMESIS_SHM_READY_EAGER_MAX_SZ", &(MPIR_CVAR_NEMESIS_SHM_READY_EAGER_MAX_SZ));
    MPIR_ERR_CHKANDJUMP1((-1 == rc),mpi_errno,MPI_ERR_OTHER,"**envvarparse","**envvarparse %s","MPIR_PARAM_NEMESIS_SHM_READY_EAGER_MAX_SZ");
    rc = MPL_env2int("MPIR_CVAR_NEMESIS_SHM_READY_EAGER_MAX_SZ", &(MPIR_CVAR_NEMESIS_SHM_READY_EAGER_MAX_SZ));
    MPIR_ERR_CHKANDJUMP1((-1 == rc),mpi_errno,MPI_ERR_OTHER,"**envvarparse","**envvarparse %s","MPIR_CVAR_NEMESIS_SHM_READY_EAGER_MAX_SZ");

    defaultval.d = 0;
    MPIR_T_CVAR_REGISTER_STATIC(
        MPI_INT,
        MPIR_CVAR_NEMESIS_ENABLE_CKPOINT, /* name */
        &MPIR_CVAR_NEMESIS_ENABLE_CKPOINT, /* address */
        1, /* count */
        MPI_T_VERBOSITY_USER_BASIC,
        MPI_T_SCOPE_ALL_EQ,
        defaultval,
        "NEMESIS", /* category */
        "If true, enables checkpointing support and returns an error if checkpointing library cannot be initialized.");
    rc = MPL_env2bool("MPICH_NEMESIS_ENABLE_CKPOINT", &(MPIR_CVAR_NEMESIS_ENABLE_CKPOINT));
    MPIR_ERR_CHKANDJUMP1((-1 == rc),mpi_errno,MPI_ERR_OTHER,"**envvarparse","**envvarparse %s","MPICH_NEMESIS_ENABLE_CKPOINT");
    rc = MPL_env2bool("MPIR_PARAM_NEMESIS_ENABLE_CKPOINT", &(MPIR_CVAR_NEMESIS_ENABLE_CKPOINT));
    MPIR_ERR_CHKANDJUMP1((-1 == rc),mpi_errno,MPI_ERR_OTHER,"**envvarparse","**envvarparse %s","MPIR_PARAM_NEMESIS_ENABLE_CKPOINT");
    rc = MPL_env2bool("MPIR_CVAR_NEMESIS_ENABLE_CKPOINT", &(MPIR_CVAR_NEMESIS_ENABLE_CKPOINT));
    MPIR_ERR_CHKANDJUMP1((-1 == rc),mpi_errno,MPI_ERR_OTHER,"**envvarparse","**envvarparse %s","MPIR_CVAR_NEMESIS_ENABLE_CKPOINT");

    defaultval.str = (char *)"";
    MPIR_T_CVAR_REGISTER_STATIC(
        MPI_CHAR,
        MPIR_CVAR_NEMESIS_NETMOD, /* name */
        &MPIR_CVAR_NEMESIS_NETMOD, /* address */
        MPIR_CVAR_MAX_STRLEN, /* count */
        MPI_T_VERBOSITY_USER_BASIC,
        MPI_T_SCOPE_ALL_EQ,
        defaultval,
        "NEMESIS", /* category */
        "If non-empty, this cvar specifies which network module should be used for communication.");
    MPIR_CVAR_GET_DEFAULT_STRING(MPIR_CVAR_NEMESIS_NETMOD, &tmp_str);
    rc = MPL_env2str("MPICH_NEMESIS_NETMOD", &tmp_str);
    MPIR_ERR_CHKANDJUMP1((-1 == rc),mpi_errno,MPI_ERR_OTHER,"**envvarparse","**envvarparse %s","MPICH_NEMESIS_NETMOD");
    rc = MPL_env2str("MPIR_PARAM_NEMESIS_NETMOD", &tmp_str);
    MPIR_ERR_CHKANDJUMP1((-1 == rc),mpi_errno,MPI_ERR_OTHER,"**envvarparse","**envvarparse %s","MPIR_PARAM_NEMESIS_NETMOD");
    rc = MPL_env2str("MPIR_CVAR_NEMESIS_NETMOD", &tmp_str);
    MPIR_ERR_CHKANDJUMP1((-1 == rc),mpi_errno,MPI_ERR_OTHER,"**envvarparse","**envvarparse %s","MPIR_CVAR_NEMESIS_NETMOD");
    if (tmp_str != NULL) {
        MPIR_CVAR_NEMESIS_NETMOD = MPIU_Strdup(tmp_str);
        MPIR_CVAR_assert(MPIR_CVAR_NEMESIS_NETMOD);
        if (MPIR_CVAR_NEMESIS_NETMOD == NULL) {
            MPIU_CHKMEM_SETERR(mpi_errno, strlen(tmp_str), "dup of string for MPIR_CVAR_NEMESIS_NETMOD");
            goto fn_fail;
        }
    }
    else {
        MPIR_CVAR_NEMESIS_NETMOD = NULL;
    }

    defaultval.d = 2097152;
    MPIR_T_CVAR_REGISTER_STATIC(
        MPI_INT,
        MPIR_CVAR_NEMESIS_LMT_DMA_THRESHOLD, /* name */
        &MPIR_CVAR_NEMESIS_LMT_DMA_THRESHOLD, /* address */
        1, /* count */
        MPI_T_VERBOSITY_USER_BASIC,
        MPI_T_SCOPE_ALL_EQ,
        defaultval,
        "NEMESIS", /* category */
        "Messages larger than this size will use the \"dma\" (knem) intranode LMT implementation, if it is enabled and available.");
    rc = MPL_env2int("MPICH_NEMESIS_LMT_DMA_THRESHOLD", &(MPIR_CVAR_NEMESIS_LMT_DMA_THRESHOLD));
    MPIR_ERR_CHKANDJUMP1((-1 == rc),mpi_errno,MPI_ERR_OTHER,"**envvarparse","**envvarparse %s","MPICH_NEMESIS_LMT_DMA_THRESHOLD");
    rc = MPL_env2int("MPIR_PARAM_NEMESIS_LMT_DMA_THRESHOLD", &(MPIR_CVAR_NEMESIS_LMT_DMA_THRESHOLD));
    MPIR_ERR_CHKANDJUMP1((-1 == rc),mpi_errno,MPI_ERR_OTHER,"**envvarparse","**envvarparse %s","MPIR_PARAM_NEMESIS_LMT_DMA_THRESHOLD");
    rc = MPL_env2int("MPIR_CVAR_NEMESIS_LMT_DMA_THRESHOLD", &(MPIR_CVAR_NEMESIS_LMT_DMA_THRESHOLD));
    MPIR_ERR_CHKANDJUMP1((-1 == rc),mpi_errno,MPI_ERR_OTHER,"**envvarparse","**envvarparse %s","MPIR_CVAR_NEMESIS_LMT_DMA_THRESHOLD");

    defaultval.d = 1000;
    MPIR_T_CVAR_REGISTER_STATIC(
        MPI_INT,
        MPIR_CVAR_POLLS_BEFORE_YIELD, /* name */
        &MPIR_CVAR_POLLS_BEFORE_YIELD, /* address */
        1, /* count */
        MPI_T_VERBOSITY_USER_BASIC,
        MPI_T_SCOPE_ALL_EQ,
        defaultval,
        "NEMESIS", /* category */
        "When MPICH is in a busy waiting loop, it will periodically call a function to yield the processor.  This cvar sets the number of loops before the yield function is called.  A value of 0 disables yielding.");
    rc = MPL_env2int("MPICH_POLLS_BEFORE_YIELD", &(MPIR_CVAR_POLLS_BEFORE_YIELD));
    MPIR_ERR_CHKANDJUMP1((-1 == rc),mpi_errno,MPI_ERR_OTHER,"**envvarparse","**envvarparse %s","MPICH_POLLS_BEFORE_YIELD");
    rc = MPL_env2int("MPIR_PARAM_POLLS_BEFORE_YIELD", &(MPIR_CVAR_POLLS_BEFORE_YIELD));
    MPIR_ERR_CHKANDJUMP1((-1 == rc),mpi_errno,MPI_ERR_OTHER,"**envvarparse","**envvarparse %s","MPIR_PARAM_POLLS_BEFORE_YIELD");
    rc = MPL_env2int("MPIR_CVAR_POLLS_BEFORE_YIELD", &(MPIR_CVAR_POLLS_BEFORE_YIELD));
    MPIR_ERR_CHKANDJUMP1((-1 == rc),mpi_errno,MPI_ERR_OTHER,"**envvarparse","**envvarparse %s","MPIR_CVAR_POLLS_BEFORE_YIELD");

    defaultval.str = (char *)NULL;
    MPIR_T_CVAR_REGISTER_STATIC(
        MPI_CHAR,
        MPIR_CVAR_OFI_USE_PROVIDER, /* name */
        &MPIR_CVAR_OFI_USE_PROVIDER, /* address */
        MPIR_CVAR_MAX_STRLEN, /* count */
        MPI_T_VERBOSITY_MPIDEV_DETAIL,
        MPI_T_SCOPE_LOCAL,
        defaultval,
        "DEVELOPER", /* category */
        "If non-null, choose an OFI provider by name");
    MPIR_CVAR_GET_DEFAULT_STRING(MPIR_CVAR_OFI_USE_PROVIDER, &tmp_str);
    rc = MPL_env2str("MPICH_OFI_USE_PROVIDER", &tmp_str);
    MPIR_ERR_CHKANDJUMP1((-1 == rc),mpi_errno,MPI_ERR_OTHER,"**envvarparse","**envvarparse %s","MPICH_OFI_USE_PROVIDER");
    rc = MPL_env2str("MPIR_PARAM_OFI_USE_PROVIDER", &tmp_str);
    MPIR_ERR_CHKANDJUMP1((-1 == rc),mpi_errno,MPI_ERR_OTHER,"**envvarparse","**envvarparse %s","MPIR_PARAM_OFI_USE_PROVIDER");
    rc = MPL_env2str("MPIR_CVAR_OFI_USE_PROVIDER", &tmp_str);
    MPIR_ERR_CHKANDJUMP1((-1 == rc),mpi_errno,MPI_ERR_OTHER,"**envvarparse","**envvarparse %s","MPIR_CVAR_OFI_USE_PROVIDER");
    if (tmp_str != NULL) {
        MPIR_CVAR_OFI_USE_PROVIDER = MPIU_Strdup(tmp_str);
        MPIR_CVAR_assert(MPIR_CVAR_OFI_USE_PROVIDER);
        if (MPIR_CVAR_OFI_USE_PROVIDER == NULL) {
            MPIU_CHKMEM_SETERR(mpi_errno, strlen(tmp_str), "dup of string for MPIR_CVAR_OFI_USE_PROVIDER");
            goto fn_fail;
        }
    }
    else {
        MPIR_CVAR_OFI_USE_PROVIDER = NULL;
    }

    defaultval.d = 0;
    MPIR_T_CVAR_REGISTER_STATIC(
        MPI_INT,
        MPIR_CVAR_OFI_DUMP_PROVIDERS, /* name */
        &MPIR_CVAR_OFI_DUMP_PROVIDERS, /* address */
        1, /* count */
        MPI_T_VERBOSITY_MPIDEV_DETAIL,
        MPI_T_SCOPE_LOCAL,
        defaultval,
        "DEVELOPER", /* category */
        "If true, dump provider information at init");
    rc = MPL_env2bool("MPICH_OFI_DUMP_PROVIDERS", &(MPIR_CVAR_OFI_DUMP_PROVIDERS));
    MPIR_ERR_CHKANDJUMP1((-1 == rc),mpi_errno,MPI_ERR_OTHER,"**envvarparse","**envvarparse %s","MPICH_OFI_DUMP_PROVIDERS");
    rc = MPL_env2bool("MPIR_PARAM_OFI_DUMP_PROVIDERS", &(MPIR_CVAR_OFI_DUMP_PROVIDERS));
    MPIR_ERR_CHKANDJUMP1((-1 == rc),mpi_errno,MPI_ERR_OTHER,"**envvarparse","**envvarparse %s","MPIR_PARAM_OFI_DUMP_PROVIDERS");
    rc = MPL_env2bool("MPIR_CVAR_OFI_DUMP_PROVIDERS", &(MPIR_CVAR_OFI_DUMP_PROVIDERS));
    MPIR_ERR_CHKANDJUMP1((-1 == rc),mpi_errno,MPI_ERR_OTHER,"**envvarparse","**envvarparse %s","MPIR_CVAR_OFI_DUMP_PROVIDERS");

    defaultval.str = (char *)NULL;
    MPIR_T_CVAR_REGISTER_STATIC(
        MPI_CHAR,
        MPIR_CVAR_CH3_INTERFACE_HOSTNAME, /* name */
        &MPIR_CVAR_CH3_INTERFACE_HOSTNAME, /* address */
        MPIR_CVAR_MAX_STRLEN, /* count */
        MPI_T_VERBOSITY_USER_BASIC,
        MPI_T_SCOPE_LOCAL,
        defaultval,
        "CH3", /* category */
        "If non-NULL, this cvar specifies the IP address that other processes should use when connecting to this process. This cvar is mutually exclusive with the MPIR_CVAR_CH3_NETWORK_IFACE cvar and it is an error to set them both.");
    MPIR_CVAR_GET_DEFAULT_STRING(MPIR_CVAR_CH3_INTERFACE_HOSTNAME, &tmp_str);
    rc = MPL_env2str("MPICH_INTERFACE_HOSTNAME", &tmp_str);
    MPIR_ERR_CHKANDJUMP1((-1 == rc),mpi_errno,MPI_ERR_OTHER,"**envvarparse","**envvarparse %s","MPICH_INTERFACE_HOSTNAME");
    rc = MPL_env2str("MPIR_PARAM_INTERFACE_HOSTNAME", &tmp_str);
    MPIR_ERR_CHKANDJUMP1((-1 == rc),mpi_errno,MPI_ERR_OTHER,"**envvarparse","**envvarparse %s","MPIR_PARAM_INTERFACE_HOSTNAME");
    rc = MPL_env2str("MPIR_CVAR_INTERFACE_HOSTNAME", &tmp_str);
    MPIR_ERR_CHKANDJUMP1((-1 == rc),mpi_errno,MPI_ERR_OTHER,"**envvarparse","**envvarparse %s","MPIR_CVAR_INTERFACE_HOSTNAME");
    rc = MPL_env2str("MPICH_CH3_INTERFACE_HOSTNAME", &tmp_str);
    MPIR_ERR_CHKANDJUMP1((-1 == rc),mpi_errno,MPI_ERR_OTHER,"**envvarparse","**envvarparse %s","MPICH_CH3_INTERFACE_HOSTNAME");
    rc = MPL_env2str("MPIR_PARAM_CH3_INTERFACE_HOSTNAME", &tmp_str);
    MPIR_ERR_CHKANDJUMP1((-1 == rc),mpi_errno,MPI_ERR_OTHER,"**envvarparse","**envvarparse %s","MPIR_PARAM_CH3_INTERFACE_HOSTNAME");
    rc = MPL_env2str("MPIR_CVAR_CH3_INTERFACE_HOSTNAME", &tmp_str);
    MPIR_ERR_CHKANDJUMP1((-1 == rc),mpi_errno,MPI_ERR_OTHER,"**envvarparse","**envvarparse %s","MPIR_CVAR_CH3_INTERFACE_HOSTNAME");
    if (tmp_str != NULL) {
        MPIR_CVAR_CH3_INTERFACE_HOSTNAME = MPIU_Strdup(tmp_str);
        MPIR_CVAR_assert(MPIR_CVAR_CH3_INTERFACE_HOSTNAME);
        if (MPIR_CVAR_CH3_INTERFACE_HOSTNAME == NULL) {
            MPIU_CHKMEM_SETERR(mpi_errno, strlen(tmp_str), "dup of string for MPIR_CVAR_CH3_INTERFACE_HOSTNAME");
            goto fn_fail;
        }
    }
    else {
        MPIR_CVAR_CH3_INTERFACE_HOSTNAME = NULL;
    }

    {
        MPIR_T_cvar_range_value_t tmp = {0,0};
        defaultval.range = tmp;
    }
    MPIR_T_CVAR_REGISTER_STATIC(
        MPI_INT,
        MPIR_CVAR_CH3_PORT_RANGE, /* name */
        &MPIR_CVAR_CH3_PORT_RANGE, /* address */
        2, /* count */
        MPI_T_VERBOSITY_USER_BASIC,
        MPI_T_SCOPE_ALL_EQ,
        defaultval,
        "CH3", /* category */
        "The MPIR_CVAR_CH3_PORT_RANGE environment variable allows you to specify the range of TCP ports to be used by the process manager and the MPICH library. The format of this variable is <low>:<high>.  To specify any available port, use 0:0.");
    rc = MPL_env2range("MPICH_PORTRANGE", &(MPIR_CVAR_CH3_PORT_RANGE.low), &(MPIR_CVAR_CH3_PORT_RANGE.high));
    MPIR_ERR_CHKANDJUMP1((-1 == rc),mpi_errno,MPI_ERR_OTHER,"**envvarparse","**envvarparse %s","MPICH_PORTRANGE");
    rc = MPL_env2range("MPICH_PORT_RANGE", &(MPIR_CVAR_CH3_PORT_RANGE.low), &(MPIR_CVAR_CH3_PORT_RANGE.high));
    MPIR_ERR_CHKANDJUMP1((-1 == rc),mpi_errno,MPI_ERR_OTHER,"**envvarparse","**envvarparse %s","MPICH_PORT_RANGE");
    rc = MPL_env2range("MPIR_PARAM_PORTRANGE", &(MPIR_CVAR_CH3_PORT_RANGE.low), &(MPIR_CVAR_CH3_PORT_RANGE.high));
    MPIR_ERR_CHKANDJUMP1((-1 == rc),mpi_errno,MPI_ERR_OTHER,"**envvarparse","**envvarparse %s","MPIR_PARAM_PORTRANGE");
    rc = MPL_env2range("MPIR_PARAM_PORT_RANGE", &(MPIR_CVAR_CH3_PORT_RANGE.low), &(MPIR_CVAR_CH3_PORT_RANGE.high));
    MPIR_ERR_CHKANDJUMP1((-1 == rc),mpi_errno,MPI_ERR_OTHER,"**envvarparse","**envvarparse %s","MPIR_PARAM_PORT_RANGE");
    rc = MPL_env2range("MPIR_CVAR_PORTRANGE", &(MPIR_CVAR_CH3_PORT_RANGE.low), &(MPIR_CVAR_CH3_PORT_RANGE.high));
    MPIR_ERR_CHKANDJUMP1((-1 == rc),mpi_errno,MPI_ERR_OTHER,"**envvarparse","**envvarparse %s","MPIR_CVAR_PORTRANGE");
    rc = MPL_env2range("MPIR_CVAR_PORT_RANGE", &(MPIR_CVAR_CH3_PORT_RANGE.low), &(MPIR_CVAR_CH3_PORT_RANGE.high));
    MPIR_ERR_CHKANDJUMP1((-1 == rc),mpi_errno,MPI_ERR_OTHER,"**envvarparse","**envvarparse %s","MPIR_CVAR_PORT_RANGE");
    rc = MPL_env2range("MPICH_CH3_PORT_RANGE", &(MPIR_CVAR_CH3_PORT_RANGE.low), &(MPIR_CVAR_CH3_PORT_RANGE.high));
    MPIR_ERR_CHKANDJUMP1((-1 == rc),mpi_errno,MPI_ERR_OTHER,"**envvarparse","**envvarparse %s","MPICH_CH3_PORT_RANGE");
    rc = MPL_env2range("MPIR_PARAM_CH3_PORT_RANGE", &(MPIR_CVAR_CH3_PORT_RANGE.low), &(MPIR_CVAR_CH3_PORT_RANGE.high));
    MPIR_ERR_CHKANDJUMP1((-1 == rc),mpi_errno,MPI_ERR_OTHER,"**envvarparse","**envvarparse %s","MPIR_PARAM_CH3_PORT_RANGE");
    rc = MPL_env2range("MPIR_CVAR_CH3_PORT_RANGE", &(MPIR_CVAR_CH3_PORT_RANGE.low), &(MPIR_CVAR_CH3_PORT_RANGE.high));
    MPIR_ERR_CHKANDJUMP1((-1 == rc),mpi_errno,MPI_ERR_OTHER,"**envvarparse","**envvarparse %s","MPIR_CVAR_CH3_PORT_RANGE");

    defaultval.str = (char *)NULL;
    MPIR_T_CVAR_REGISTER_STATIC(
        MPI_CHAR,
        MPIR_CVAR_NEMESIS_TCP_NETWORK_IFACE, /* name */
        &MPIR_CVAR_NEMESIS_TCP_NETWORK_IFACE, /* address */
        MPIR_CVAR_MAX_STRLEN, /* count */
        MPI_T_VERBOSITY_USER_BASIC,
        MPI_T_SCOPE_ALL_EQ,
        defaultval,
        "NEMESIS", /* category */
        "If non-NULL, this cvar specifies which pseudo-ethernet interface the tcp netmod should use (e.g., \"eth1\", \"ib0\"). Note, this is a Linux-specific cvar. This cvar is mutually exclusive with the MPIR_CVAR_CH3_INTERFACE_HOSTNAME cvar and it is an error to set them both.");
    MPIR_CVAR_GET_DEFAULT_STRING(MPIR_CVAR_NEMESIS_TCP_NETWORK_IFACE, &tmp_str);
    rc = MPL_env2str("MPICH_NETWORK_IFACE", &tmp_str);
    MPIR_ERR_CHKANDJUMP1((-1 == rc),mpi_errno,MPI_ERR_OTHER,"**envvarparse","**envvarparse %s","MPICH_NETWORK_IFACE");
    rc = MPL_env2str("MPIR_PARAM_NETWORK_IFACE", &tmp_str);
    MPIR_ERR_CHKANDJUMP1((-1 == rc),mpi_errno,MPI_ERR_OTHER,"**envvarparse","**envvarparse %s","MPIR_PARAM_NETWORK_IFACE");
    rc = MPL_env2str("MPIR_CVAR_NETWORK_IFACE", &tmp_str);
    MPIR_ERR_CHKANDJUMP1((-1 == rc),mpi_errno,MPI_ERR_OTHER,"**envvarparse","**envvarparse %s","MPIR_CVAR_NETWORK_IFACE");
    rc = MPL_env2str("MPICH_NEMESIS_TCP_NETWORK_IFACE", &tmp_str);
    MPIR_ERR_CHKANDJUMP1((-1 == rc),mpi_errno,MPI_ERR_OTHER,"**envvarparse","**envvarparse %s","MPICH_NEMESIS_TCP_NETWORK_IFACE");
    rc = MPL_env2str("MPIR_PARAM_NEMESIS_TCP_NETWORK_IFACE", &tmp_str);
    MPIR_ERR_CHKANDJUMP1((-1 == rc),mpi_errno,MPI_ERR_OTHER,"**envvarparse","**envvarparse %s","MPIR_PARAM_NEMESIS_TCP_NETWORK_IFACE");
    rc = MPL_env2str("MPIR_CVAR_NEMESIS_TCP_NETWORK_IFACE", &tmp_str);
    MPIR_ERR_CHKANDJUMP1((-1 == rc),mpi_errno,MPI_ERR_OTHER,"**envvarparse","**envvarparse %s","MPIR_CVAR_NEMESIS_TCP_NETWORK_IFACE");
    if (tmp_str != NULL) {
        MPIR_CVAR_NEMESIS_TCP_NETWORK_IFACE = MPIU_Strdup(tmp_str);
        MPIR_CVAR_assert(MPIR_CVAR_NEMESIS_TCP_NETWORK_IFACE);
        if (MPIR_CVAR_NEMESIS_TCP_NETWORK_IFACE == NULL) {
            MPIU_CHKMEM_SETERR(mpi_errno, strlen(tmp_str), "dup of string for MPIR_CVAR_NEMESIS_TCP_NETWORK_IFACE");
            goto fn_fail;
        }
    }
    else {
        MPIR_CVAR_NEMESIS_TCP_NETWORK_IFACE = NULL;
    }

    defaultval.d = 10;
    MPIR_T_CVAR_REGISTER_STATIC(
        MPI_INT,
        MPIR_CVAR_NEMESIS_TCP_HOST_LOOKUP_RETRIES, /* name */
        &MPIR_CVAR_NEMESIS_TCP_HOST_LOOKUP_RETRIES, /* address */
        1, /* count */
        MPI_T_VERBOSITY_USER_BASIC,
        MPI_T_SCOPE_ALL_EQ,
        defaultval,
        "NEMESIS", /* category */
        "This cvar controls the number of times to retry the gethostbyname() function before giving up.");
    rc = MPL_env2int("MPICH_NEMESIS_TCP_HOST_LOOKUP_RETRIES", &(MPIR_CVAR_NEMESIS_TCP_HOST_LOOKUP_RETRIES));
    MPIR_ERR_CHKANDJUMP1((-1 == rc),mpi_errno,MPI_ERR_OTHER,"**envvarparse","**envvarparse %s","MPICH_NEMESIS_TCP_HOST_LOOKUP_RETRIES");
    rc = MPL_env2int("MPIR_PARAM_NEMESIS_TCP_HOST_LOOKUP_RETRIES", &(MPIR_CVAR_NEMESIS_TCP_HOST_LOOKUP_RETRIES));
    MPIR_ERR_CHKANDJUMP1((-1 == rc),mpi_errno,MPI_ERR_OTHER,"**envvarparse","**envvarparse %s","MPIR_PARAM_NEMESIS_TCP_HOST_LOOKUP_RETRIES");
    rc = MPL_env2int("MPIR_CVAR_NEMESIS_TCP_HOST_LOOKUP_RETRIES", &(MPIR_CVAR_NEMESIS_TCP_HOST_LOOKUP_RETRIES));
    MPIR_ERR_CHKANDJUMP1((-1 == rc),mpi_errno,MPI_ERR_OTHER,"**envvarparse","**envvarparse %s","MPIR_CVAR_NEMESIS_TCP_HOST_LOOKUP_RETRIES");

    defaultval.d = 0;
    MPIR_T_CVAR_REGISTER_STATIC(
        MPI_INT,
        MPIR_CVAR_NEMESIS_MXM_BULK_CONNECT, /* name */
        &MPIR_CVAR_NEMESIS_MXM_BULK_CONNECT, /* address */
        1, /* count */
        MPI_T_VERBOSITY_USER_BASIC,
        MPI_T_SCOPE_ALL_EQ,
        defaultval,
        "CH3", /* category */
        "If true, force mxm to connect all processes at initialization time.");
    rc = MPL_env2bool("MPICH_NEMESIS_MXM_BULK_CONNECT", &(MPIR_CVAR_NEMESIS_MXM_BULK_CONNECT));
    MPIR_ERR_CHKANDJUMP1((-1 == rc),mpi_errno,MPI_ERR_OTHER,"**envvarparse","**envvarparse %s","MPICH_NEMESIS_MXM_BULK_CONNECT");
    rc = MPL_env2bool("MPIR_PARAM_NEMESIS_MXM_BULK_CONNECT", &(MPIR_CVAR_NEMESIS_MXM_BULK_CONNECT));
    MPIR_ERR_CHKANDJUMP1((-1 == rc),mpi_errno,MPI_ERR_OTHER,"**envvarparse","**envvarparse %s","MPIR_PARAM_NEMESIS_MXM_BULK_CONNECT");
    rc = MPL_env2bool("MPIR_CVAR_NEMESIS_MXM_BULK_CONNECT", &(MPIR_CVAR_NEMESIS_MXM_BULK_CONNECT));
    MPIR_ERR_CHKANDJUMP1((-1 == rc),mpi_errno,MPI_ERR_OTHER,"**envvarparse","**envvarparse %s","MPIR_CVAR_NEMESIS_MXM_BULK_CONNECT");

    defaultval.d = 0;
    MPIR_T_CVAR_REGISTER_STATIC(
        MPI_INT,
        MPIR_CVAR_NEMESIS_MXM_BULK_DISCONNECT, /* name */
        &MPIR_CVAR_NEMESIS_MXM_BULK_DISCONNECT, /* address */
        1, /* count */
        MPI_T_VERBOSITY_USER_BASIC,
        MPI_T_SCOPE_ALL_EQ,
        defaultval,
        "CH3", /* category */
        "If true, force mxm to disconnect all processes at finalization time.");
    rc = MPL_env2bool("MPICH_NEMESIS_MXM_BULK_DISCONNECT", &(MPIR_CVAR_NEMESIS_MXM_BULK_DISCONNECT));
    MPIR_ERR_CHKANDJUMP1((-1 == rc),mpi_errno,MPI_ERR_OTHER,"**envvarparse","**envvarparse %s","MPICH_NEMESIS_MXM_BULK_DISCONNECT");
    rc = MPL_env2bool("MPIR_PARAM_NEMESIS_MXM_BULK_DISCONNECT", &(MPIR_CVAR_NEMESIS_MXM_BULK_DISCONNECT));
    MPIR_ERR_CHKANDJUMP1((-1 == rc),mpi_errno,MPI_ERR_OTHER,"**envvarparse","**envvarparse %s","MPIR_PARAM_NEMESIS_MXM_BULK_DISCONNECT");
    rc = MPL_env2bool("MPIR_CVAR_NEMESIS_MXM_BULK_DISCONNECT", &(MPIR_CVAR_NEMESIS_MXM_BULK_DISCONNECT));
    MPIR_ERR_CHKANDJUMP1((-1 == rc),mpi_errno,MPI_ERR_OTHER,"**envvarparse","**envvarparse %s","MPIR_CVAR_NEMESIS_MXM_BULK_DISCONNECT");

    defaultval.d = 0;
    MPIR_T_CVAR_REGISTER_STATIC(
        MPI_INT,
        MPIR_CVAR_NEMESIS_MXM_HUGEPAGE, /* name */
        &MPIR_CVAR_NEMESIS_MXM_HUGEPAGE, /* address */
        1, /* count */
        MPI_T_VERBOSITY_USER_BASIC,
        MPI_T_SCOPE_ALL_EQ,
        defaultval,
        "CH3", /* category */
        "If true, mxm tries detecting hugepage support.  On HPC-X 2.3 and earlier, this might cause problems on Ubuntu and other platforms even if the system provides hugepage support.");
    rc = MPL_env2bool("MPICH_NEMESIS_MXM_HUGEPAGE", &(MPIR_CVAR_NEMESIS_MXM_HUGEPAGE));
    MPIR_ERR_CHKANDJUMP1((-1 == rc),mpi_errno,MPI_ERR_OTHER,"**envvarparse","**envvarparse %s","MPICH_NEMESIS_MXM_HUGEPAGE");
    rc = MPL_env2bool("MPIR_PARAM_NEMESIS_MXM_HUGEPAGE", &(MPIR_CVAR_NEMESIS_MXM_HUGEPAGE));
    MPIR_ERR_CHKANDJUMP1((-1 == rc),mpi_errno,MPI_ERR_OTHER,"**envvarparse","**envvarparse %s","MPIR_PARAM_NEMESIS_MXM_HUGEPAGE");
    rc = MPL_env2bool("MPIR_CVAR_NEMESIS_MXM_HUGEPAGE", &(MPIR_CVAR_NEMESIS_MXM_HUGEPAGE));
    MPIR_ERR_CHKANDJUMP1((-1 == rc),mpi_errno,MPI_ERR_OTHER,"**envvarparse","**envvarparse %s","MPIR_CVAR_NEMESIS_MXM_HUGEPAGE");

fn_exit:
    return mpi_errno;
fn_fail:
    goto fn_exit;
}

int MPIR_T_cvar_finalize(void)
{
    int mpi_errno = MPI_SUCCESS;

    if (MPIR_CVAR_DEFAULT_THREAD_LEVEL != NULL) {
        MPIU_Free(MPIR_CVAR_DEFAULT_THREAD_LEVEL);
        MPIR_CVAR_DEFAULT_THREAD_LEVEL = NULL;
    }

    if (MPIR_CVAR_NAMESERV_FILE_PUBDIR != NULL) {
        MPIU_Free(MPIR_CVAR_NAMESERV_FILE_PUBDIR);
        MPIR_CVAR_NAMESERV_FILE_PUBDIR = NULL;
    }

    if (MPIR_CVAR_NEMESIS_NETMOD != NULL) {
        MPIU_Free(MPIR_CVAR_NEMESIS_NETMOD);
        MPIR_CVAR_NEMESIS_NETMOD = NULL;
    }

    if (MPIR_CVAR_OFI_USE_PROVIDER != NULL) {
        MPIU_Free(MPIR_CVAR_OFI_USE_PROVIDER);
        MPIR_CVAR_OFI_USE_PROVIDER = NULL;
    }

    if (MPIR_CVAR_CH3_INTERFACE_HOSTNAME != NULL) {
        MPIU_Free(MPIR_CVAR_CH3_INTERFACE_HOSTNAME);
        MPIR_CVAR_CH3_INTERFACE_HOSTNAME = NULL;
    }

    if (MPIR_CVAR_NEMESIS_TCP_NETWORK_IFACE != NULL) {
        MPIU_Free(MPIR_CVAR_NEMESIS_TCP_NETWORK_IFACE);
        MPIR_CVAR_NEMESIS_TCP_NETWORK_IFACE = NULL;
    }

fn_exit:
    return mpi_errno;
fn_fail:
    goto fn_exit;
}

