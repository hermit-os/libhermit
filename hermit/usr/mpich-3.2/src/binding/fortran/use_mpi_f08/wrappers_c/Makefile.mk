## DO NOT EDIT
## This file created by buildiface
##
## vim: set ft=automake :

# ensure that the buildiface script ends up in the release tarball
EXTRA_DIST += src/binding/fortran/use_mpi_f08/wrappers_c/buildiface

if BUILD_F08_BINDING
mpi_fc_sources += \
	src/binding/fortran/use_mpi_f08/wrappers_c/send_cdesc.c \
	src/binding/fortran/use_mpi_f08/wrappers_c/recv_cdesc.c \
	src/binding/fortran/use_mpi_f08/wrappers_c/bsend_cdesc.c \
	src/binding/fortran/use_mpi_f08/wrappers_c/ssend_cdesc.c \
	src/binding/fortran/use_mpi_f08/wrappers_c/rsend_cdesc.c \
	src/binding/fortran/use_mpi_f08/wrappers_c/buffer_attach_cdesc.c \
	src/binding/fortran/use_mpi_f08/wrappers_c/isend_cdesc.c \
	src/binding/fortran/use_mpi_f08/wrappers_c/ibsend_cdesc.c \
	src/binding/fortran/use_mpi_f08/wrappers_c/issend_cdesc.c \
	src/binding/fortran/use_mpi_f08/wrappers_c/irsend_cdesc.c \
	src/binding/fortran/use_mpi_f08/wrappers_c/irecv_cdesc.c \
	src/binding/fortran/use_mpi_f08/wrappers_c/send_init_cdesc.c \
	src/binding/fortran/use_mpi_f08/wrappers_c/bsend_init_cdesc.c \
	src/binding/fortran/use_mpi_f08/wrappers_c/ssend_init_cdesc.c \
	src/binding/fortran/use_mpi_f08/wrappers_c/rsend_init_cdesc.c \
	src/binding/fortran/use_mpi_f08/wrappers_c/recv_init_cdesc.c \
	src/binding/fortran/use_mpi_f08/wrappers_c/sendrecv_cdesc.c \
	src/binding/fortran/use_mpi_f08/wrappers_c/sendrecv_replace_cdesc.c \
	src/binding/fortran/use_mpi_f08/wrappers_c/pack_cdesc.c \
	src/binding/fortran/use_mpi_f08/wrappers_c/unpack_cdesc.c \
	src/binding/fortran/use_mpi_f08/wrappers_c/bcast_cdesc.c \
	src/binding/fortran/use_mpi_f08/wrappers_c/gather_cdesc.c \
	src/binding/fortran/use_mpi_f08/wrappers_c/gatherv_cdesc.c \
	src/binding/fortran/use_mpi_f08/wrappers_c/scatter_cdesc.c \
	src/binding/fortran/use_mpi_f08/wrappers_c/scatterv_cdesc.c \
	src/binding/fortran/use_mpi_f08/wrappers_c/allgather_cdesc.c \
	src/binding/fortran/use_mpi_f08/wrappers_c/allgatherv_cdesc.c \
	src/binding/fortran/use_mpi_f08/wrappers_c/alltoall_cdesc.c \
	src/binding/fortran/use_mpi_f08/wrappers_c/alltoallv_cdesc.c \
	src/binding/fortran/use_mpi_f08/wrappers_c/alltoallw_cdesc.c \
	src/binding/fortran/use_mpi_f08/wrappers_c/exscan_cdesc.c \
	src/binding/fortran/use_mpi_f08/wrappers_c/reduce_cdesc.c \
	src/binding/fortran/use_mpi_f08/wrappers_c/allreduce_cdesc.c \
	src/binding/fortran/use_mpi_f08/wrappers_c/reduce_scatter_cdesc.c \
	src/binding/fortran/use_mpi_f08/wrappers_c/scan_cdesc.c \
	src/binding/fortran/use_mpi_f08/wrappers_c/accumulate_cdesc.c \
	src/binding/fortran/use_mpi_f08/wrappers_c/get_cdesc.c \
	src/binding/fortran/use_mpi_f08/wrappers_c/put_cdesc.c \
	src/binding/fortran/use_mpi_f08/wrappers_c/win_create_cdesc.c \
	src/binding/fortran/use_mpi_f08/wrappers_c/win_attach_cdesc.c \
	src/binding/fortran/use_mpi_f08/wrappers_c/win_detach_cdesc.c \
	src/binding/fortran/use_mpi_f08/wrappers_c/get_accumulate_cdesc.c \
	src/binding/fortran/use_mpi_f08/wrappers_c/fetch_and_op_cdesc.c \
	src/binding/fortran/use_mpi_f08/wrappers_c/compare_and_swap_cdesc.c \
	src/binding/fortran/use_mpi_f08/wrappers_c/rput_cdesc.c \
	src/binding/fortran/use_mpi_f08/wrappers_c/rget_cdesc.c \
	src/binding/fortran/use_mpi_f08/wrappers_c/raccumulate_cdesc.c \
	src/binding/fortran/use_mpi_f08/wrappers_c/rget_accumulate_cdesc.c \
	src/binding/fortran/use_mpi_f08/wrappers_c/free_mem_cdesc.c \
	src/binding/fortran/use_mpi_f08/wrappers_c/get_address_cdesc.c \
	src/binding/fortran/use_mpi_f08/wrappers_c/pack_external_cdesc.c \
	src/binding/fortran/use_mpi_f08/wrappers_c/unpack_external_cdesc.c \
	src/binding/fortran/use_mpi_f08/wrappers_c/reduce_local_cdesc.c \
	src/binding/fortran/use_mpi_f08/wrappers_c/reduce_scatter_block_cdesc.c \
	src/binding/fortran/use_mpi_f08/wrappers_c/imrecv_cdesc.c \
	src/binding/fortran/use_mpi_f08/wrappers_c/mrecv_cdesc.c \
	src/binding/fortran/use_mpi_f08/wrappers_c/ibcast_cdesc.c \
	src/binding/fortran/use_mpi_f08/wrappers_c/igather_cdesc.c \
	src/binding/fortran/use_mpi_f08/wrappers_c/igatherv_cdesc.c \
	src/binding/fortran/use_mpi_f08/wrappers_c/iscatter_cdesc.c \
	src/binding/fortran/use_mpi_f08/wrappers_c/iscatterv_cdesc.c \
	src/binding/fortran/use_mpi_f08/wrappers_c/iallgather_cdesc.c \
	src/binding/fortran/use_mpi_f08/wrappers_c/iallgatherv_cdesc.c \
	src/binding/fortran/use_mpi_f08/wrappers_c/ialltoall_cdesc.c \
	src/binding/fortran/use_mpi_f08/wrappers_c/ialltoallv_cdesc.c \
	src/binding/fortran/use_mpi_f08/wrappers_c/ialltoallw_cdesc.c \
	src/binding/fortran/use_mpi_f08/wrappers_c/ireduce_cdesc.c \
	src/binding/fortran/use_mpi_f08/wrappers_c/iallreduce_cdesc.c \
	src/binding/fortran/use_mpi_f08/wrappers_c/ireduce_scatter_cdesc.c \
	src/binding/fortran/use_mpi_f08/wrappers_c/ireduce_scatter_block_cdesc.c \
	src/binding/fortran/use_mpi_f08/wrappers_c/iscan_cdesc.c \
	src/binding/fortran/use_mpi_f08/wrappers_c/iexscan_cdesc.c \
	src/binding/fortran/use_mpi_f08/wrappers_c/ineighbor_allgather_cdesc.c \
	src/binding/fortran/use_mpi_f08/wrappers_c/ineighbor_allgatherv_cdesc.c \
	src/binding/fortran/use_mpi_f08/wrappers_c/ineighbor_alltoall_cdesc.c \
	src/binding/fortran/use_mpi_f08/wrappers_c/ineighbor_alltoallv_cdesc.c \
	src/binding/fortran/use_mpi_f08/wrappers_c/ineighbor_alltoallw_cdesc.c \
	src/binding/fortran/use_mpi_f08/wrappers_c/neighbor_allgather_cdesc.c \
	src/binding/fortran/use_mpi_f08/wrappers_c/neighbor_allgatherv_cdesc.c \
	src/binding/fortran/use_mpi_f08/wrappers_c/neighbor_alltoall_cdesc.c \
	src/binding/fortran/use_mpi_f08/wrappers_c/neighbor_alltoallv_cdesc.c \
	src/binding/fortran/use_mpi_f08/wrappers_c/neighbor_alltoallw_cdesc.c \
	src/binding/fortran/use_mpi_f08/wrappers_c/file_read_at_cdesc.c \
	src/binding/fortran/use_mpi_f08/wrappers_c/file_read_at_all_cdesc.c \
	src/binding/fortran/use_mpi_f08/wrappers_c/file_write_at_cdesc.c \
	src/binding/fortran/use_mpi_f08/wrappers_c/file_write_at_all_cdesc.c \
	src/binding/fortran/use_mpi_f08/wrappers_c/file_iread_at_cdesc.c \
	src/binding/fortran/use_mpi_f08/wrappers_c/file_iwrite_at_cdesc.c \
	src/binding/fortran/use_mpi_f08/wrappers_c/file_read_cdesc.c \
	src/binding/fortran/use_mpi_f08/wrappers_c/file_read_all_cdesc.c \
	src/binding/fortran/use_mpi_f08/wrappers_c/file_write_cdesc.c \
	src/binding/fortran/use_mpi_f08/wrappers_c/file_write_all_cdesc.c \
	src/binding/fortran/use_mpi_f08/wrappers_c/file_iread_cdesc.c \
	src/binding/fortran/use_mpi_f08/wrappers_c/file_iwrite_cdesc.c \
	src/binding/fortran/use_mpi_f08/wrappers_c/file_read_shared_cdesc.c \
	src/binding/fortran/use_mpi_f08/wrappers_c/file_write_shared_cdesc.c \
	src/binding/fortran/use_mpi_f08/wrappers_c/file_iread_shared_cdesc.c \
	src/binding/fortran/use_mpi_f08/wrappers_c/file_iwrite_shared_cdesc.c \
	src/binding/fortran/use_mpi_f08/wrappers_c/file_read_ordered_cdesc.c \
	src/binding/fortran/use_mpi_f08/wrappers_c/file_write_ordered_cdesc.c \
	src/binding/fortran/use_mpi_f08/wrappers_c/file_read_at_all_begin_cdesc.c \
	src/binding/fortran/use_mpi_f08/wrappers_c/file_read_at_all_end_cdesc.c \
	src/binding/fortran/use_mpi_f08/wrappers_c/file_write_at_all_begin_cdesc.c \
	src/binding/fortran/use_mpi_f08/wrappers_c/file_write_at_all_end_cdesc.c \
	src/binding/fortran/use_mpi_f08/wrappers_c/file_read_all_begin_cdesc.c \
	src/binding/fortran/use_mpi_f08/wrappers_c/file_read_all_end_cdesc.c \
	src/binding/fortran/use_mpi_f08/wrappers_c/file_write_all_begin_cdesc.c \
	src/binding/fortran/use_mpi_f08/wrappers_c/file_write_all_end_cdesc.c \
	src/binding/fortran/use_mpi_f08/wrappers_c/file_read_ordered_begin_cdesc.c \
	src/binding/fortran/use_mpi_f08/wrappers_c/file_read_ordered_end_cdesc.c \
	src/binding/fortran/use_mpi_f08/wrappers_c/file_write_ordered_begin_cdesc.c \
	src/binding/fortran/use_mpi_f08/wrappers_c/file_write_ordered_end_cdesc.c \
	src/binding/fortran/use_mpi_f08/wrappers_c/file_iread_at_all_cdesc.c \
	src/binding/fortran/use_mpi_f08/wrappers_c/file_iwrite_at_all_cdesc.c \
	src/binding/fortran/use_mpi_f08/wrappers_c/file_iread_all_cdesc.c \
	src/binding/fortran/use_mpi_f08/wrappers_c/file_iwrite_all_cdesc.c \
	src/binding/fortran/use_mpi_f08/wrappers_c/cdesc.c \
	src/binding/fortran/use_mpi_f08/wrappers_c/comm_spawn_c.c \
	src/binding/fortran/use_mpi_f08/wrappers_c/comm_spawn_multiple_c.c \
	src/binding/fortran/use_mpi_f08/wrappers_c/f_sync_reg_c.c \
	src/binding/fortran/use_mpi_f08/wrappers_c/utils.c

AM_CPPFLAGS += -I${master_top_srcdir}/src/binding/fortran/use_mpi_f08/wrappers_c

noinst_HEADERS += src/binding/fortran/use_mpi_f08/wrappers_c/cdesc.h

endif BUILD_F08_BINDING
