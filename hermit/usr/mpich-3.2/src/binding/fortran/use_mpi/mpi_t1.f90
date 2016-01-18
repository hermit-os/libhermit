!     -*- Mode: Fortran; -*-
!  (C) 2008 by Argonne National Laboratory.
!      See COPYRIGHT in top-level directory.
        MODULE MPI_t1_s
        IMPLICIT NONE
        PRIVATE
        PUBLIC :: MPI_INEIGHBOR_ALLTOALL
        INTERFACE MPI_INEIGHBOR_ALLTOALL
           MODULE PROCEDURE MPI_INEIGHBOR_ALLTOALL_T
        END INTERFACE MPI_INEIGHBOR_ALLTOALL

        PUBLIC :: MPI_RECV
        INTERFACE MPI_RECV
           MODULE PROCEDURE MPI_RECV_T
        END INTERFACE MPI_RECV

        PUBLIC :: MPI_ATTR_PUT
        INTERFACE MPI_ATTR_PUT
           MODULE PROCEDURE MPI_ATTR_PUT_T
        END INTERFACE MPI_ATTR_PUT

        PUBLIC :: MPI_IALLGATHER
        INTERFACE MPI_IALLGATHER
           MODULE PROCEDURE MPI_IALLGATHER_T
        END INTERFACE MPI_IALLGATHER

        PUBLIC :: MPI_SSEND_INIT
        INTERFACE MPI_SSEND_INIT
           MODULE PROCEDURE MPI_SSEND_INIT_T
        END INTERFACE MPI_SSEND_INIT

        PUBLIC :: MPI_BUFFER_DETACH
        INTERFACE MPI_BUFFER_DETACH
           MODULE PROCEDURE MPI_BUFFER_DETACH_T
        END INTERFACE MPI_BUFFER_DETACH

        PUBLIC :: MPI_ALLTOALLW
        INTERFACE MPI_ALLTOALLW
           MODULE PROCEDURE MPI_ALLTOALLW_T
        END INTERFACE MPI_ALLTOALLW

        PUBLIC :: MPI_SEND_INIT
        INTERFACE MPI_SEND_INIT
           MODULE PROCEDURE MPI_SEND_INIT_T
        END INTERFACE MPI_SEND_INIT

        PUBLIC :: MPI_UNPACK
        INTERFACE MPI_UNPACK
           MODULE PROCEDURE MPI_UNPACK_T
        END INTERFACE MPI_UNPACK

        PUBLIC :: MPI_WIN_ALLOCATE
        INTERFACE MPI_WIN_ALLOCATE
           MODULE PROCEDURE MPI_WIN_ALLOCATE_T
        END INTERFACE MPI_WIN_ALLOCATE

        PUBLIC :: MPI_IALLTOALL
        INTERFACE MPI_IALLTOALL
           MODULE PROCEDURE MPI_IALLTOALL_T
        END INTERFACE MPI_IALLTOALL

        PUBLIC :: MPI_RGET
        INTERFACE MPI_RGET
           MODULE PROCEDURE MPI_RGET_T
        END INTERFACE MPI_RGET

        PUBLIC :: MPI_PACK_EXTERNAL
        INTERFACE MPI_PACK_EXTERNAL
           MODULE PROCEDURE MPI_PACK_EXTERNAL_T
        END INTERFACE MPI_PACK_EXTERNAL

        PUBLIC :: MPI_WIN_ALLOCATE_SHARED
        INTERFACE MPI_WIN_ALLOCATE_SHARED
           MODULE PROCEDURE MPI_WIN_ALLOCATE_SHARED_T
        END INTERFACE MPI_WIN_ALLOCATE_SHARED

        PUBLIC :: MPI_PACK
        INTERFACE MPI_PACK
           MODULE PROCEDURE MPI_PACK_T
        END INTERFACE MPI_PACK

        PUBLIC :: MPI_IALLTOALLV
        INTERFACE MPI_IALLTOALLV
           MODULE PROCEDURE MPI_IALLTOALLV_T
        END INTERFACE MPI_IALLTOALLV

        PUBLIC :: MPI_ALLGATHERV
        INTERFACE MPI_ALLGATHERV
           MODULE PROCEDURE MPI_ALLGATHERV_T
        END INTERFACE MPI_ALLGATHERV

        PUBLIC :: MPI_COMM_CREATE_KEYVAL
        INTERFACE MPI_COMM_CREATE_KEYVAL
           MODULE PROCEDURE MPI_COMM_CREATE_KEYVAL_T
        END INTERFACE MPI_COMM_CREATE_KEYVAL

        PUBLIC :: MPI_NEIGHBOR_ALLTOALL
        INTERFACE MPI_NEIGHBOR_ALLTOALL
           MODULE PROCEDURE MPI_NEIGHBOR_ALLTOALL_T
        END INTERFACE MPI_NEIGHBOR_ALLTOALL

        PUBLIC :: MPI_COMPARE_AND_SWAP
        INTERFACE MPI_COMPARE_AND_SWAP
           MODULE PROCEDURE MPI_COMPARE_AND_SWAP_T
        END INTERFACE MPI_COMPARE_AND_SWAP

        PUBLIC :: MPI_IBCAST
        INTERFACE MPI_IBCAST
           MODULE PROCEDURE MPI_IBCAST_T
        END INTERFACE MPI_IBCAST

        PUBLIC :: MPI_GET
        INTERFACE MPI_GET
           MODULE PROCEDURE MPI_GET_T
        END INTERFACE MPI_GET

        PUBLIC :: MPI_WIN_SHARED_QUERY
        INTERFACE MPI_WIN_SHARED_QUERY
           MODULE PROCEDURE MPI_WIN_SHARED_QUERY_T
        END INTERFACE MPI_WIN_SHARED_QUERY

        PUBLIC :: MPI_RACCUMULATE
        INTERFACE MPI_RACCUMULATE
           MODULE PROCEDURE MPI_RACCUMULATE_T
        END INTERFACE MPI_RACCUMULATE

        PUBLIC :: MPI_SCATTER
        INTERFACE MPI_SCATTER
           MODULE PROCEDURE MPI_SCATTER_T
        END INTERFACE MPI_SCATTER

        PUBLIC :: MPI_GATHERV
        INTERFACE MPI_GATHERV
           MODULE PROCEDURE MPI_GATHERV_T
        END INTERFACE MPI_GATHERV

        PUBLIC :: MPI_RSEND
        INTERFACE MPI_RSEND
           MODULE PROCEDURE MPI_RSEND_T
        END INTERFACE MPI_RSEND

        PUBLIC :: MPI_COMM_GET_ATTR
        INTERFACE MPI_COMM_GET_ATTR
           MODULE PROCEDURE MPI_COMM_GET_ATTR_T
        END INTERFACE MPI_COMM_GET_ATTR

        PUBLIC :: MPI_IGATHER
        INTERFACE MPI_IGATHER
           MODULE PROCEDURE MPI_IGATHER_T
        END INTERFACE MPI_IGATHER

        PUBLIC :: MPI_UNPACK_EXTERNAL
        INTERFACE MPI_UNPACK_EXTERNAL
           MODULE PROCEDURE MPI_UNPACK_EXTERNAL_T
        END INTERFACE MPI_UNPACK_EXTERNAL

        PUBLIC :: MPI_FREE_MEM
        INTERFACE MPI_FREE_MEM
           MODULE PROCEDURE MPI_FREE_MEM_T
        END INTERFACE MPI_FREE_MEM

        PUBLIC :: MPI_RECV_INIT
        INTERFACE MPI_RECV_INIT
           MODULE PROCEDURE MPI_RECV_INIT_T
        END INTERFACE MPI_RECV_INIT

        PUBLIC :: MPI_IGATHERV
        INTERFACE MPI_IGATHERV
           MODULE PROCEDURE MPI_IGATHERV_T
        END INTERFACE MPI_IGATHERV

        PUBLIC :: MPI_ISCATTERV
        INTERFACE MPI_ISCATTERV
           MODULE PROCEDURE MPI_ISCATTERV_T
        END INTERFACE MPI_ISCATTERV

        PUBLIC :: MPI_BSEND
        INTERFACE MPI_BSEND
           MODULE PROCEDURE MPI_BSEND_T
        END INTERFACE MPI_BSEND

        PUBLIC :: MPI_IREDUCE
        INTERFACE MPI_IREDUCE
           MODULE PROCEDURE MPI_IREDUCE_T
        END INTERFACE MPI_IREDUCE

        PUBLIC :: MPI_GREQUEST_START
        INTERFACE MPI_GREQUEST_START
           MODULE PROCEDURE MPI_GREQUEST_START_T
        END INTERFACE MPI_GREQUEST_START

        PUBLIC :: MPI_BCAST
        INTERFACE MPI_BCAST
           MODULE PROCEDURE MPI_BCAST_T
        END INTERFACE MPI_BCAST

        PUBLIC :: MPI_SENDRECV
        INTERFACE MPI_SENDRECV
           MODULE PROCEDURE MPI_SENDRECV_T
        END INTERFACE MPI_SENDRECV

        PUBLIC :: MPI_TYPE_SET_ATTR
        INTERFACE MPI_TYPE_SET_ATTR
           MODULE PROCEDURE MPI_TYPE_SET_ATTR_T
        END INTERFACE MPI_TYPE_SET_ATTR

        PUBLIC :: MPI_FETCH_AND_OP
        INTERFACE MPI_FETCH_AND_OP
           MODULE PROCEDURE MPI_FETCH_AND_OP_T
        END INTERFACE MPI_FETCH_AND_OP

        PUBLIC :: MPI_RPUT
        INTERFACE MPI_RPUT
           MODULE PROCEDURE MPI_RPUT_T
        END INTERFACE MPI_RPUT

        PUBLIC :: MPI_ALLTOALL
        INTERFACE MPI_ALLTOALL
           MODULE PROCEDURE MPI_ALLTOALL_T
        END INTERFACE MPI_ALLTOALL

        PUBLIC :: MPI_INEIGHBOR_ALLTOALLV
        INTERFACE MPI_INEIGHBOR_ALLTOALLV
           MODULE PROCEDURE MPI_INEIGHBOR_ALLTOALLV_T
        END INTERFACE MPI_INEIGHBOR_ALLTOALLV

        PUBLIC :: MPI_NEIGHBOR_ALLTOALLV
        INTERFACE MPI_NEIGHBOR_ALLTOALLV
           MODULE PROCEDURE MPI_NEIGHBOR_ALLTOALLV_T
        END INTERFACE MPI_NEIGHBOR_ALLTOALLV

        PUBLIC :: MPI_INEIGHBOR_ALLTOALLW
        INTERFACE MPI_INEIGHBOR_ALLTOALLW
           MODULE PROCEDURE MPI_INEIGHBOR_ALLTOALLW_T
        END INTERFACE MPI_INEIGHBOR_ALLTOALLW

        PUBLIC :: MPI_RSEND_INIT
        INTERFACE MPI_RSEND_INIT
           MODULE PROCEDURE MPI_RSEND_INIT_T
        END INTERFACE MPI_RSEND_INIT

        PUBLIC :: MPI_COMM_SET_ATTR
        INTERFACE MPI_COMM_SET_ATTR
           MODULE PROCEDURE MPI_COMM_SET_ATTR_T
        END INTERFACE MPI_COMM_SET_ATTR

        PUBLIC :: MPI_TYPE_GET_ATTR
        INTERFACE MPI_TYPE_GET_ATTR
           MODULE PROCEDURE MPI_TYPE_GET_ATTR_T
        END INTERFACE MPI_TYPE_GET_ATTR

        PUBLIC :: MPI_ALLGATHER
        INTERFACE MPI_ALLGATHER
           MODULE PROCEDURE MPI_ALLGATHER_T
        END INTERFACE MPI_ALLGATHER

        PUBLIC :: MPI_BSEND_INIT
        INTERFACE MPI_BSEND_INIT
           MODULE PROCEDURE MPI_BSEND_INIT_T
        END INTERFACE MPI_BSEND_INIT

        PUBLIC :: MPI_REDUCE_SCATTER_BLOCK
        INTERFACE MPI_REDUCE_SCATTER_BLOCK
           MODULE PROCEDURE MPI_REDUCE_SCATTER_BLOCK_T
        END INTERFACE MPI_REDUCE_SCATTER_BLOCK

        PUBLIC :: MPI_NEIGHBOR_ALLGATHER
        INTERFACE MPI_NEIGHBOR_ALLGATHER
           MODULE PROCEDURE MPI_NEIGHBOR_ALLGATHER_T
        END INTERFACE MPI_NEIGHBOR_ALLGATHER

        PUBLIC :: MPI_GATHER
        INTERFACE MPI_GATHER
           MODULE PROCEDURE MPI_GATHER_T
        END INTERFACE MPI_GATHER

        PUBLIC :: MPI_REDUCE
        INTERFACE MPI_REDUCE
           MODULE PROCEDURE MPI_REDUCE_T
        END INTERFACE MPI_REDUCE

        PUBLIC :: MPI_WIN_CREATE
        INTERFACE MPI_WIN_CREATE
           MODULE PROCEDURE MPI_WIN_CREATE_T
        END INTERFACE MPI_WIN_CREATE

        PUBLIC :: MPI_SCATTERV
        INTERFACE MPI_SCATTERV
           MODULE PROCEDURE MPI_SCATTERV_T
        END INTERFACE MPI_SCATTERV

        PUBLIC :: MPI_IRSEND
        INTERFACE MPI_IRSEND
           MODULE PROCEDURE MPI_IRSEND_T
        END INTERFACE MPI_IRSEND

        PUBLIC :: MPI_IREDUCE_SCATTER_BLOCK
        INTERFACE MPI_IREDUCE_SCATTER_BLOCK
           MODULE PROCEDURE MPI_IREDUCE_SCATTER_BLOCK_T
        END INTERFACE MPI_IREDUCE_SCATTER_BLOCK

        PUBLIC :: MPI_ISCAN
        INTERFACE MPI_ISCAN
           MODULE PROCEDURE MPI_ISCAN_T
        END INTERFACE MPI_ISCAN

        PUBLIC :: MPI_TYPE_CREATE_KEYVAL
        INTERFACE MPI_TYPE_CREATE_KEYVAL
           MODULE PROCEDURE MPI_TYPE_CREATE_KEYVAL_T
        END INTERFACE MPI_TYPE_CREATE_KEYVAL

        PUBLIC :: MPI_PUT
        INTERFACE MPI_PUT
           MODULE PROCEDURE MPI_PUT_T
        END INTERFACE MPI_PUT

        PUBLIC :: MPI_WIN_SET_ATTR
        INTERFACE MPI_WIN_SET_ATTR
           MODULE PROCEDURE MPI_WIN_SET_ATTR_T
        END INTERFACE MPI_WIN_SET_ATTR

        PUBLIC :: MPI_EXSCAN
        INTERFACE MPI_EXSCAN
           MODULE PROCEDURE MPI_EXSCAN_T
        END INTERFACE MPI_EXSCAN

        PUBLIC :: MPI_ISCATTER
        INTERFACE MPI_ISCATTER
           MODULE PROCEDURE MPI_ISCATTER_T
        END INTERFACE MPI_ISCATTER

        PUBLIC :: MPI_NEIGHBOR_ALLTOALLW
        INTERFACE MPI_NEIGHBOR_ALLTOALLW
           MODULE PROCEDURE MPI_NEIGHBOR_ALLTOALLW_T
        END INTERFACE MPI_NEIGHBOR_ALLTOALLW

        PUBLIC :: MPI_ALLREDUCE
        INTERFACE MPI_ALLREDUCE
           MODULE PROCEDURE MPI_ALLREDUCE_T
        END INTERFACE MPI_ALLREDUCE

        PUBLIC :: MPI_WIN_GET_ATTR
        INTERFACE MPI_WIN_GET_ATTR
           MODULE PROCEDURE MPI_WIN_GET_ATTR_T
        END INTERFACE MPI_WIN_GET_ATTR

        PUBLIC :: MPI_ALLTOALLV
        INTERFACE MPI_ALLTOALLV
           MODULE PROCEDURE MPI_ALLTOALLV_T
        END INTERFACE MPI_ALLTOALLV

        PUBLIC :: MPI_SENDRECV_REPLACE
        INTERFACE MPI_SENDRECV_REPLACE
           MODULE PROCEDURE MPI_SENDRECV_REPLACE_T
        END INTERFACE MPI_SENDRECV_REPLACE

        PUBLIC :: MPI_WIN_DETACH
        INTERFACE MPI_WIN_DETACH
           MODULE PROCEDURE MPI_WIN_DETACH_T
        END INTERFACE MPI_WIN_DETACH

        PUBLIC :: MPI_INEIGHBOR_ALLGATHER
        INTERFACE MPI_INEIGHBOR_ALLGATHER
           MODULE PROCEDURE MPI_INEIGHBOR_ALLGATHER_T
        END INTERFACE MPI_INEIGHBOR_ALLGATHER

        PUBLIC :: MPI_RGET_ACCUMULATE
        INTERFACE MPI_RGET_ACCUMULATE
           MODULE PROCEDURE MPI_RGET_ACCUMULATE_T
        END INTERFACE MPI_RGET_ACCUMULATE

        PUBLIC :: MPI_ISSEND
        INTERFACE MPI_ISSEND
           MODULE PROCEDURE MPI_ISSEND_T
        END INTERFACE MPI_ISSEND

        PUBLIC :: MPI_SCAN
        INTERFACE MPI_SCAN
           MODULE PROCEDURE MPI_SCAN_T
        END INTERFACE MPI_SCAN

        PUBLIC :: MPI_IBSEND
        INTERFACE MPI_IBSEND
           MODULE PROCEDURE MPI_IBSEND_T
        END INTERFACE MPI_IBSEND

        PUBLIC :: MPI_MRECV
        INTERFACE MPI_MRECV
           MODULE PROCEDURE MPI_MRECV_T
        END INTERFACE MPI_MRECV

        PUBLIC :: MPI_KEYVAL_CREATE
        INTERFACE MPI_KEYVAL_CREATE
           MODULE PROCEDURE MPI_KEYVAL_CREATE_T
        END INTERFACE MPI_KEYVAL_CREATE

        PUBLIC :: MPI_IRECV
        INTERFACE MPI_IRECV
           MODULE PROCEDURE MPI_IRECV_T
        END INTERFACE MPI_IRECV

        PUBLIC :: MPI_INEIGHBOR_ALLGATHERV
        INTERFACE MPI_INEIGHBOR_ALLGATHERV
           MODULE PROCEDURE MPI_INEIGHBOR_ALLGATHERV_T
        END INTERFACE MPI_INEIGHBOR_ALLGATHERV

        PUBLIC :: MPI_IREDUCE_SCATTER
        INTERFACE MPI_IREDUCE_SCATTER
           MODULE PROCEDURE MPI_IREDUCE_SCATTER_T
        END INTERFACE MPI_IREDUCE_SCATTER

        PUBLIC :: MPI_ACCUMULATE
        INTERFACE MPI_ACCUMULATE
           MODULE PROCEDURE MPI_ACCUMULATE_T
        END INTERFACE MPI_ACCUMULATE

        PUBLIC :: MPI_REDUCE_LOCAL
        INTERFACE MPI_REDUCE_LOCAL
           MODULE PROCEDURE MPI_REDUCE_LOCAL_T
        END INTERFACE MPI_REDUCE_LOCAL

        PUBLIC :: MPI_SSEND
        INTERFACE MPI_SSEND
           MODULE PROCEDURE MPI_SSEND_T
        END INTERFACE MPI_SSEND

        PUBLIC :: MPI_WIN_CREATE_KEYVAL
        INTERFACE MPI_WIN_CREATE_KEYVAL
           MODULE PROCEDURE MPI_WIN_CREATE_KEYVAL_T
        END INTERFACE MPI_WIN_CREATE_KEYVAL

        PUBLIC :: MPI_BUFFER_ATTACH
        INTERFACE MPI_BUFFER_ATTACH
           MODULE PROCEDURE MPI_BUFFER_ATTACH_T
        END INTERFACE MPI_BUFFER_ATTACH

        PUBLIC :: MPI_ATTR_GET
        INTERFACE MPI_ATTR_GET
           MODULE PROCEDURE MPI_ATTR_GET_T
        END INTERFACE MPI_ATTR_GET

        PUBLIC :: MPI_WIN_ATTACH
        INTERFACE MPI_WIN_ATTACH
           MODULE PROCEDURE MPI_WIN_ATTACH_T
        END INTERFACE MPI_WIN_ATTACH

        PUBLIC :: MPI_ALLOC_MEM
        INTERFACE MPI_ALLOC_MEM
           MODULE PROCEDURE MPI_ALLOC_MEM_T
        END INTERFACE MPI_ALLOC_MEM

        PUBLIC :: MPI_IALLREDUCE
        INTERFACE MPI_IALLREDUCE
           MODULE PROCEDURE MPI_IALLREDUCE_T
        END INTERFACE MPI_IALLREDUCE

        PUBLIC :: MPI_REDUCE_SCATTER
        INTERFACE MPI_REDUCE_SCATTER
           MODULE PROCEDURE MPI_REDUCE_SCATTER_T
        END INTERFACE MPI_REDUCE_SCATTER

        PUBLIC :: MPI_NEIGHBOR_ALLGATHERV
        INTERFACE MPI_NEIGHBOR_ALLGATHERV
           MODULE PROCEDURE MPI_NEIGHBOR_ALLGATHERV_T
        END INTERFACE MPI_NEIGHBOR_ALLGATHERV

        PUBLIC :: MPI_IALLTOALLW
        INTERFACE MPI_IALLTOALLW
           MODULE PROCEDURE MPI_IALLTOALLW_T
        END INTERFACE MPI_IALLTOALLW

        PUBLIC :: MPI_ISEND
        INTERFACE MPI_ISEND
           MODULE PROCEDURE MPI_ISEND_T
        END INTERFACE MPI_ISEND

        PUBLIC :: MPI_SEND
        INTERFACE MPI_SEND
           MODULE PROCEDURE MPI_SEND_T
        END INTERFACE MPI_SEND

        PUBLIC :: MPI_GET_ADDRESS
        INTERFACE MPI_GET_ADDRESS
           MODULE PROCEDURE MPI_GET_ADDRESS_T
        END INTERFACE MPI_GET_ADDRESS

        PUBLIC :: MPI_ADDRESS
        INTERFACE MPI_ADDRESS
           MODULE PROCEDURE MPI_ADDRESS_T
        END INTERFACE MPI_ADDRESS

        PUBLIC :: MPI_IMRECV
        INTERFACE MPI_IMRECV
           MODULE PROCEDURE MPI_IMRECV_T
        END INTERFACE MPI_IMRECV

        PUBLIC :: MPI_GET_ACCUMULATE
        INTERFACE MPI_GET_ACCUMULATE
           MODULE PROCEDURE MPI_GET_ACCUMULATE_T
        END INTERFACE MPI_GET_ACCUMULATE

        PUBLIC :: MPI_IEXSCAN
        INTERFACE MPI_IEXSCAN
           MODULE PROCEDURE MPI_IEXSCAN_T
        END INTERFACE MPI_IEXSCAN

        PUBLIC :: MPI_IALLGATHERV
        INTERFACE MPI_IALLGATHERV
           MODULE PROCEDURE MPI_IALLGATHERV_T
        END INTERFACE MPI_IALLGATHERV

        CONTAINS

      SUBROUTINE MPI_INEIGHBOR_ALLTOALL_T(sendbuf,sendcount,sendtype,recvbuf,&
                  recvcount,recvtype,comm,request,ierror)
        <type> sendbuf<dims>
        INTEGER sendcount
        INTEGER sendtype
        <type1> recvbuf<dims1>
        INTEGER recvcount
        INTEGER recvtype
        INTEGER comm
        INTEGER request
        INTEGER ierror
        EXTERNAL MPI_INEIGHBOR_ALLTOALL
        CALL MPI_INEIGHBOR_ALLTOALL(sendbuf,sendcount,sendtype,recvbuf,&
                    recvcount,recvtype,comm,request,ierror)
      END SUBROUTINE MPI_INEIGHBOR_ALLTOALL_T

      SUBROUTINE MPI_RECV_T(buf,count,datatype,source,tag,comm,status,ierror)
        <type> buf<dims>
        INTEGER count
        INTEGER datatype
        INTEGER source
        INTEGER tag
        INTEGER comm
        INTEGER status(MPI_STATUS_SIZE)
        INTEGER ierror
        EXTERNAL MPI_RECV
        CALL MPI_RECV(buf,count,datatype,source,tag,comm,status,ierror)
      END SUBROUTINE MPI_RECV_T

      SUBROUTINE MPI_ATTR_PUT_T(comm,keyval,attribute_val,ierror)
        INTEGER comm
        INTEGER keyval
        <type> attribute_val<dims>
        INTEGER ierror
        EXTERNAL MPI_ATTR_PUT
        CALL MPI_ATTR_PUT(comm,keyval,attribute_val,ierror)
      END SUBROUTINE MPI_ATTR_PUT_T

      SUBROUTINE MPI_IALLGATHER_T(sendbuf,sendcount,sendtype,recvbuf,recvcount,&
                  recvtype,comm,request,ierror)
        <type> sendbuf<dims>
        INTEGER sendcount
        INTEGER sendtype
        <type1> recvbuf<dims1>
        INTEGER recvcount
        INTEGER recvtype
        INTEGER comm
        INTEGER request
        INTEGER ierror
        EXTERNAL MPI_IALLGATHER
        CALL MPI_IALLGATHER(sendbuf,sendcount,sendtype,recvbuf,recvcount,&
                    recvtype,comm,request,ierror)
      END SUBROUTINE MPI_IALLGATHER_T

      SUBROUTINE MPI_SSEND_INIT_T(buf,count,datatype,dest,tag,comm,request,&
                  ierror)
        <type> buf<dims>
        INTEGER count
        INTEGER datatype
        INTEGER dest
        INTEGER tag
        INTEGER comm
        INTEGER request
        INTEGER ierror
        EXTERNAL MPI_SSEND_INIT
        CALL MPI_SSEND_INIT(buf,count,datatype,dest,tag,comm,request,&
                    ierror)
      END SUBROUTINE MPI_SSEND_INIT_T

      SUBROUTINE MPI_BUFFER_DETACH_T(buffer_addr,size,ierror)
        <type> buffer_addr<dims>
        INTEGER size
        INTEGER ierror
        EXTERNAL MPI_BUFFER_DETACH
        CALL MPI_BUFFER_DETACH(buffer_addr,size,ierror)
      END SUBROUTINE MPI_BUFFER_DETACH_T

      SUBROUTINE MPI_ALLTOALLW_T(sendbuf,sendcounts,sdispls,sendtypes,recvbuf,&
                  recvcounts,rdispls,recvtypes,comm,ierror)
        <type> sendbuf<dims>
        INTEGER sendcounts(*)
        INTEGER sdispls(*)
        INTEGER sendtypes(*)
        <type1> recvbuf<dims1>
        INTEGER recvcounts(*)
        INTEGER rdispls(*)
        INTEGER recvtypes(*)
        INTEGER comm
        INTEGER ierror
        EXTERNAL MPI_ALLTOALLW
        CALL MPI_ALLTOALLW(sendbuf,sendcounts,sdispls,sendtypes,recvbuf,&
                    recvcounts,rdispls,recvtypes,comm,ierror)
      END SUBROUTINE MPI_ALLTOALLW_T

      SUBROUTINE MPI_SEND_INIT_T(buf,count,datatype,dest,tag,comm,request,&
                  ierror)
        <type> buf<dims>
        INTEGER count
        INTEGER datatype
        INTEGER dest
        INTEGER tag
        INTEGER comm
        INTEGER request
        INTEGER ierror
        EXTERNAL MPI_SEND_INIT
        CALL MPI_SEND_INIT(buf,count,datatype,dest,tag,comm,request,&
                    ierror)
      END SUBROUTINE MPI_SEND_INIT_T

      SUBROUTINE MPI_UNPACK_T(inbuf,insize,position,outbuf,outcount,datatype,&
                  comm,ierror)
        <type> inbuf<dims>
        INTEGER insize
        INTEGER position
        <type1> outbuf<dims1>
        INTEGER outcount
        INTEGER datatype
        INTEGER comm
        INTEGER ierror
        EXTERNAL MPI_UNPACK
        CALL MPI_UNPACK(inbuf,insize,position,outbuf,outcount,datatype,&
                    comm,ierror)
      END SUBROUTINE MPI_UNPACK_T

      SUBROUTINE MPI_WIN_ALLOCATE_T(size,disp_unit,info,comm,baseptr,win,&
                  ierror)
        INTEGER(KIND=MPI_ADDRESS_KIND) size
        INTEGER disp_unit
        INTEGER info
        INTEGER comm
        <type> baseptr<dims>
        INTEGER win
        INTEGER ierror
        EXTERNAL MPI_WIN_ALLOCATE
        CALL MPI_WIN_ALLOCATE(size,disp_unit,info,comm,baseptr,win,&
                    ierror)
      END SUBROUTINE MPI_WIN_ALLOCATE_T

      SUBROUTINE MPI_IALLTOALL_T(sendbuf,sendcount,sendtype,recvbuf,recvcount,&
                  recvtype,comm,request,ierror)
        <type> sendbuf<dims>
        INTEGER sendcount
        INTEGER sendtype
        <type1> recvbuf<dims1>
        INTEGER recvcount
        INTEGER recvtype
        INTEGER comm
        INTEGER request
        INTEGER ierror
        EXTERNAL MPI_IALLTOALL
        CALL MPI_IALLTOALL(sendbuf,sendcount,sendtype,recvbuf,recvcount,&
                    recvtype,comm,request,ierror)
      END SUBROUTINE MPI_IALLTOALL_T

      SUBROUTINE MPI_RGET_T(origin_addr,origin_count,origin_datatype,&
                  target_rank,target_disp,target_count,target_datatype,win,&
                  request,ierror)
        <type> origin_addr<dims>
        INTEGER origin_count
        INTEGER origin_datatype
        INTEGER target_rank
        INTEGER(KIND=MPI_ADDRESS_KIND) target_disp
        INTEGER target_count
        INTEGER target_datatype
        INTEGER win
        INTEGER request
        INTEGER ierror
        EXTERNAL MPI_RGET
        CALL MPI_RGET(origin_addr,origin_count,origin_datatype,&
                    target_rank,target_disp,target_count,target_datatype,win,&
                    request,ierror)
      END SUBROUTINE MPI_RGET_T

      SUBROUTINE MPI_PACK_EXTERNAL_T(datarep,inbuf,incount,datatype,outbuf,&
                  outsize,position,ierror)
        CHARACTER (LEN=*) datarep
        <type> inbuf<dims>
        INTEGER incount
        INTEGER datatype
        <type1> outbuf<dims1>
        INTEGER(KIND=MPI_ADDRESS_KIND) outsize
        INTEGER(KIND=MPI_ADDRESS_KIND) position
        INTEGER ierror
        EXTERNAL MPI_PACK_EXTERNAL
        CALL MPI_PACK_EXTERNAL(datarep,inbuf,incount,datatype,outbuf,&
                    outsize,position,ierror)
      END SUBROUTINE MPI_PACK_EXTERNAL_T

      SUBROUTINE MPI_WIN_ALLOCATE_SHARED_T(size,disp_unit,info,comm,baseptr,&
                  win,ierror)
        INTEGER(KIND=MPI_ADDRESS_KIND) size
        INTEGER disp_unit
        INTEGER info
        INTEGER comm
        <type> baseptr<dims>
        INTEGER win
        INTEGER ierror
        EXTERNAL MPI_WIN_ALLOCATE_SHARED
        CALL MPI_WIN_ALLOCATE_SHARED(size,disp_unit,info,comm,baseptr,&
                    win,ierror)
      END SUBROUTINE MPI_WIN_ALLOCATE_SHARED_T

      SUBROUTINE MPI_PACK_T(inbuf,incount,datatype,outbuf,outsize,position,&
                  comm,ierror)
        <type> inbuf<dims>
        INTEGER incount
        INTEGER datatype
        <type1> outbuf<dims1>
        INTEGER outsize
        INTEGER position
        INTEGER comm
        INTEGER ierror
        EXTERNAL MPI_PACK
        CALL MPI_PACK(inbuf,incount,datatype,outbuf,outsize,position,&
                    comm,ierror)
      END SUBROUTINE MPI_PACK_T

      SUBROUTINE MPI_IALLTOALLV_T(sendbuf,sendcounts,sdispls,sendtype,recvbuf,&
                  recvcounts,rdispls,recvtype,comm,request,ierror)
        <type> sendbuf<dims>
        INTEGER sendcounts(*)
        INTEGER sdispls(*)
        INTEGER sendtype
        <type1> recvbuf<dims1>
        INTEGER recvcounts(*)
        INTEGER rdispls(*)
        INTEGER recvtype
        INTEGER comm
        INTEGER request
        INTEGER ierror
        EXTERNAL MPI_IALLTOALLV
        CALL MPI_IALLTOALLV(sendbuf,sendcounts,sdispls,sendtype,recvbuf,&
                    recvcounts,rdispls,recvtype,comm,request,ierror)
      END SUBROUTINE MPI_IALLTOALLV_T

      SUBROUTINE MPI_ALLGATHERV_T(sendbuf,sendcount,sendtype,recvbuf,&
                  recvcounts,displs,recvtype,comm,ierror)
        <type> sendbuf<dims>
        INTEGER sendcount
        INTEGER sendtype
        <type1> recvbuf<dims1>
        INTEGER recvcounts(*)
        INTEGER displs(*)
        INTEGER recvtype
        INTEGER comm
        INTEGER ierror
        EXTERNAL MPI_ALLGATHERV
        CALL MPI_ALLGATHERV(sendbuf,sendcount,sendtype,recvbuf,&
                    recvcounts,displs,recvtype,comm,ierror)
      END SUBROUTINE MPI_ALLGATHERV_T

      SUBROUTINE MPI_COMM_CREATE_KEYVAL_T(comm_copy_attr_fn,&
                  comm_delete_attr_fn,comm_keyval,extra_state,ierror)
        EXTERNAL comm_copy_attr_fn
        EXTERNAL comm_delete_attr_fn
        INTEGER comm_keyval
        <type> extra_state<dims>
        INTEGER ierror
        EXTERNAL MPI_COMM_CREATE_KEYVAL
        CALL MPI_COMM_CREATE_KEYVAL(comm_copy_attr_fn,&
                    comm_delete_attr_fn,comm_keyval,extra_state,ierror)
      END SUBROUTINE MPI_COMM_CREATE_KEYVAL_T

      SUBROUTINE MPI_NEIGHBOR_ALLTOALL_T(sendbuf,sendcount,sendtype,recvbuf,&
                  recvcount,recvtype,comm,ierror)
        <type> sendbuf<dims>
        INTEGER sendcount
        INTEGER sendtype
        <type1> recvbuf<dims1>
        INTEGER recvcount
        INTEGER recvtype
        INTEGER comm
        INTEGER ierror
        EXTERNAL MPI_NEIGHBOR_ALLTOALL
        CALL MPI_NEIGHBOR_ALLTOALL(sendbuf,sendcount,sendtype,recvbuf,&
                    recvcount,recvtype,comm,ierror)
      END SUBROUTINE MPI_NEIGHBOR_ALLTOALL_T

      SUBROUTINE MPI_COMPARE_AND_SWAP_T(origin_addr,compare_addr,result_addr,&
                  datatype,target_rank,target_disp,win,ierror)
        <type> origin_addr<dims>
        <type1> compare_addr<dims1>
        <type2> result_addr<dims2>
        INTEGER datatype
        INTEGER target_rank
        INTEGER(KIND=MPI_ADDRESS_KIND) target_disp
        INTEGER win
        INTEGER ierror
        EXTERNAL MPI_COMPARE_AND_SWAP
        CALL MPI_COMPARE_AND_SWAP(origin_addr,compare_addr,result_addr,&
                    datatype,target_rank,target_disp,win,ierror)
      END SUBROUTINE MPI_COMPARE_AND_SWAP_T

      SUBROUTINE MPI_IBCAST_T(buffer,count,datatype,root,comm,request,ierror)
        <type> buffer<dims>
        INTEGER count
        INTEGER datatype
        INTEGER root
        INTEGER comm
        INTEGER request
        INTEGER ierror
        EXTERNAL MPI_IBCAST
        CALL MPI_IBCAST(buffer,count,datatype,root,comm,request,ierror)
      END SUBROUTINE MPI_IBCAST_T

      SUBROUTINE MPI_GET_T(origin_addr,origin_count,origin_datatype,&
                  target_rank,target_disp,target_count,target_datatype,win,&
                  ierror)
        <type> origin_addr<dims>
        INTEGER origin_count
        INTEGER origin_datatype
        INTEGER target_rank
        INTEGER(KIND=MPI_ADDRESS_KIND) target_disp
        INTEGER target_count
        INTEGER target_datatype
        INTEGER win
        INTEGER ierror
        EXTERNAL MPI_GET
        CALL MPI_GET(origin_addr,origin_count,origin_datatype,&
                    target_rank,target_disp,target_count,target_datatype,win,&
                    ierror)
      END SUBROUTINE MPI_GET_T

      SUBROUTINE MPI_WIN_SHARED_QUERY_T(win,rank,size,disp_unit,baseptr,ierror)
        INTEGER win
        INTEGER rank
        INTEGER(KIND=MPI_ADDRESS_KIND) size
        INTEGER disp_unit
        <type> baseptr<dims>
        INTEGER ierror
        EXTERNAL MPI_WIN_SHARED_QUERY
        CALL MPI_WIN_SHARED_QUERY(win,rank,size,disp_unit,baseptr,ierror)
      END SUBROUTINE MPI_WIN_SHARED_QUERY_T

      SUBROUTINE MPI_RACCUMULATE_T(origin_addr,origin_count,origin_datatype,&
                  target_rank,target_disp,target_count,target_datatype,op,win,&
                  request,ierror)
        <type> origin_addr<dims>
        INTEGER origin_count
        INTEGER origin_datatype
        INTEGER target_rank
        INTEGER(KIND=MPI_ADDRESS_KIND) target_disp
        INTEGER target_count
        INTEGER target_datatype
        INTEGER op
        INTEGER win
        INTEGER request
        INTEGER ierror
        EXTERNAL MPI_RACCUMULATE
        CALL MPI_RACCUMULATE(origin_addr,origin_count,origin_datatype,&
                    target_rank,target_disp,target_count,target_datatype,op,&
                    win,request,ierror)
      END SUBROUTINE MPI_RACCUMULATE_T

      SUBROUTINE MPI_SCATTER_T(sendbuf,sendcount,sendtype,recvbuf,recvcount,&
                  recvtype,root,comm,ierror)
        <type> sendbuf<dims>
        INTEGER sendcount
        INTEGER sendtype
        <type1> recvbuf<dims1>
        INTEGER recvcount
        INTEGER recvtype
        INTEGER root
        INTEGER comm
        INTEGER ierror
        EXTERNAL MPI_SCATTER
        CALL MPI_SCATTER(sendbuf,sendcount,sendtype,recvbuf,recvcount,&
                    recvtype,root,comm,ierror)
      END SUBROUTINE MPI_SCATTER_T

      SUBROUTINE MPI_GATHERV_T(sendbuf,sendcount,sendtype,recvbuf,recvcounts,&
                  displs,recvtype,root,comm,ierror)
        <type> sendbuf<dims>
        INTEGER sendcount
        INTEGER sendtype
        <type1> recvbuf<dims1>
        INTEGER recvcounts(*)
        INTEGER displs(*)
        INTEGER recvtype
        INTEGER root
        INTEGER comm
        INTEGER ierror
        EXTERNAL MPI_GATHERV
        CALL MPI_GATHERV(sendbuf,sendcount,sendtype,recvbuf,recvcounts,&
                    displs,recvtype,root,comm,ierror)
      END SUBROUTINE MPI_GATHERV_T

      SUBROUTINE MPI_RSEND_T(buf,count,datatype,dest,tag,comm,ierror)
        <type> buf<dims>
        INTEGER count
        INTEGER datatype
        INTEGER dest
        INTEGER tag
        INTEGER comm
        INTEGER ierror
        EXTERNAL MPI_RSEND
        CALL MPI_RSEND(buf,count,datatype,dest,tag,comm,ierror)
      END SUBROUTINE MPI_RSEND_T

      SUBROUTINE MPI_COMM_GET_ATTR_T(comm,comm_keyval,attribute_val,flag,&
                  ierror)
        INTEGER comm
        INTEGER comm_keyval
        <type> attribute_val<dims>
        LOGICAL flag
        INTEGER ierror
        EXTERNAL MPI_COMM_GET_ATTR
        CALL MPI_COMM_GET_ATTR(comm,comm_keyval,attribute_val,flag,&
                    ierror)
      END SUBROUTINE MPI_COMM_GET_ATTR_T

      SUBROUTINE MPI_IGATHER_T(sendbuf,sendcount,sendtype,recvbuf,recvcount,&
                  recvtype,root,comm,request,ierror)
        <type> sendbuf<dims>
        INTEGER sendcount
        INTEGER sendtype
        <type1> recvbuf<dims1>
        INTEGER recvcount
        INTEGER recvtype
        INTEGER root
        INTEGER comm
        INTEGER request
        INTEGER ierror
        EXTERNAL MPI_IGATHER
        CALL MPI_IGATHER(sendbuf,sendcount,sendtype,recvbuf,recvcount,&
                    recvtype,root,comm,request,ierror)
      END SUBROUTINE MPI_IGATHER_T

      SUBROUTINE MPI_UNPACK_EXTERNAL_T(datarep,inbuf,insize,position,outbuf,&
                  outcount,datatype,ierror)
        CHARACTER (LEN=*) datarep
        <type> inbuf<dims>
        INTEGER(KIND=MPI_ADDRESS_KIND) insize
        INTEGER(KIND=MPI_ADDRESS_KIND) position
        <type1> outbuf<dims1>
        INTEGER outcount
        INTEGER datatype
        INTEGER ierror
        EXTERNAL MPI_UNPACK_EXTERNAL
        CALL MPI_UNPACK_EXTERNAL(datarep,inbuf,insize,position,outbuf,&
                    outcount,datatype,ierror)
      END SUBROUTINE MPI_UNPACK_EXTERNAL_T

      SUBROUTINE MPI_FREE_MEM_T(base,ierror)
        <type> base<dims>
        INTEGER ierror
        EXTERNAL MPI_FREE_MEM
        CALL MPI_FREE_MEM(base,ierror)
      END SUBROUTINE MPI_FREE_MEM_T

      SUBROUTINE MPI_RECV_INIT_T(buf,count,datatype,source,tag,comm,request,&
                  ierror)
        <type> buf<dims>
        INTEGER count
        INTEGER datatype
        INTEGER source
        INTEGER tag
        INTEGER comm
        INTEGER request
        INTEGER ierror
        EXTERNAL MPI_RECV_INIT
        CALL MPI_RECV_INIT(buf,count,datatype,source,tag,comm,request,&
                    ierror)
      END SUBROUTINE MPI_RECV_INIT_T

      SUBROUTINE MPI_IGATHERV_T(sendbuf,sendcount,sendtype,recvbuf,recvcounts,&
                  displs,recvtype,root,comm,request,ierror)
        <type> sendbuf<dims>
        INTEGER sendcount
        INTEGER sendtype
        <type1> recvbuf<dims1>
        INTEGER recvcounts(*)
        INTEGER displs(*)
        INTEGER recvtype
        INTEGER root
        INTEGER comm
        INTEGER request
        INTEGER ierror
        EXTERNAL MPI_IGATHERV
        CALL MPI_IGATHERV(sendbuf,sendcount,sendtype,recvbuf,recvcounts,&
                    displs,recvtype,root,comm,request,ierror)
      END SUBROUTINE MPI_IGATHERV_T

      SUBROUTINE MPI_ISCATTERV_T(sendbuf,sendcounts,displs,sendtype,recvbuf,&
                  recvcount,recvtype,root,comm,request,ierror)
        <type> sendbuf<dims>
        INTEGER sendcounts(*)
        INTEGER displs(*)
        INTEGER sendtype
        <type1> recvbuf<dims1>
        INTEGER recvcount
        INTEGER recvtype
        INTEGER root
        INTEGER comm
        INTEGER request
        INTEGER ierror
        EXTERNAL MPI_ISCATTERV
        CALL MPI_ISCATTERV(sendbuf,sendcounts,displs,sendtype,recvbuf,&
                    recvcount,recvtype,root,comm,request,ierror)
      END SUBROUTINE MPI_ISCATTERV_T

      SUBROUTINE MPI_BSEND_T(buf,count,datatype,dest,tag,comm,ierror)
        <type> buf<dims>
        INTEGER count
        INTEGER datatype
        INTEGER dest
        INTEGER tag
        INTEGER comm
        INTEGER ierror
        EXTERNAL MPI_BSEND
        CALL MPI_BSEND(buf,count,datatype,dest,tag,comm,ierror)
      END SUBROUTINE MPI_BSEND_T

      SUBROUTINE MPI_IREDUCE_T(sendbuf,recvbuf,count,datatype,op,root,comm,&
                  request,ierror)
        <type> sendbuf<dims>
        <type1> recvbuf<dims1>
        INTEGER count
        INTEGER datatype
        INTEGER op
        INTEGER root
        INTEGER comm
        INTEGER request
        INTEGER ierror
        EXTERNAL MPI_IREDUCE
        CALL MPI_IREDUCE(sendbuf,recvbuf,count,datatype,op,root,comm,&
                    request,ierror)
      END SUBROUTINE MPI_IREDUCE_T

      SUBROUTINE MPI_GREQUEST_START_T(query_fn,free_fn,cancel_fn,extra_state,&
                  request,ierror)
        EXTERNAL query_fn
        EXTERNAL free_fn
        EXTERNAL cancel_fn
        <type> extra_state<dims>
        INTEGER request
        INTEGER ierror
        EXTERNAL MPI_GREQUEST_START
        CALL MPI_GREQUEST_START(query_fn,free_fn,cancel_fn,extra_state,&
                    request,ierror)
      END SUBROUTINE MPI_GREQUEST_START_T

      SUBROUTINE MPI_BCAST_T(buffer,count,datatype,root,comm,ierror)
        <type> buffer<dims>
        INTEGER count
        INTEGER datatype
        INTEGER root
        INTEGER comm
        INTEGER ierror
        EXTERNAL MPI_BCAST
        CALL MPI_BCAST(buffer,count,datatype,root,comm,ierror)
      END SUBROUTINE MPI_BCAST_T

      SUBROUTINE MPI_SENDRECV_T(sendbuf,sendcount,sendtype,dest,sendtag,&
                  recvbuf,recvcount,recvtype,source,recvtag,comm,status,ierror)
        <type> sendbuf<dims>
        INTEGER sendcount
        INTEGER sendtype
        INTEGER dest
        INTEGER sendtag
        <type1> recvbuf<dims1>
        INTEGER recvcount
        INTEGER recvtype
        INTEGER source
        INTEGER recvtag
        INTEGER comm
        INTEGER status(MPI_STATUS_SIZE)
        INTEGER ierror
        EXTERNAL MPI_SENDRECV
        CALL MPI_SENDRECV(sendbuf,sendcount,sendtype,dest,sendtag,&
                    recvbuf,recvcount,recvtype,source,recvtag,comm,status,&
                    ierror)
      END SUBROUTINE MPI_SENDRECV_T

      SUBROUTINE MPI_TYPE_SET_ATTR_T(datatype,type_keyval,attribute_val,ierror)
        INTEGER datatype
        INTEGER type_keyval
        <type> attribute_val<dims>
        INTEGER ierror
        EXTERNAL MPI_TYPE_SET_ATTR
        CALL MPI_TYPE_SET_ATTR(datatype,type_keyval,attribute_val,ierror)
      END SUBROUTINE MPI_TYPE_SET_ATTR_T

      SUBROUTINE MPI_FETCH_AND_OP_T(origin_addr,result_addr,datatype,&
                  target_rank,target_disp,op,win,ierror)
        <type> origin_addr<dims>
        <type1> result_addr<dims1>
        INTEGER datatype
        INTEGER target_rank
        INTEGER(KIND=MPI_ADDRESS_KIND) target_disp
        INTEGER op
        INTEGER win
        INTEGER ierror
        EXTERNAL MPI_FETCH_AND_OP
        CALL MPI_FETCH_AND_OP(origin_addr,result_addr,datatype,&
                    target_rank,target_disp,op,win,ierror)
      END SUBROUTINE MPI_FETCH_AND_OP_T

      SUBROUTINE MPI_RPUT_T(origin_addr,origin_count,origin_datatype,&
                  target_rank,target_disp,target_count,target_datatype,win,&
                  request,ierror)
        <type> origin_addr<dims>
        INTEGER origin_count
        INTEGER origin_datatype
        INTEGER target_rank
        INTEGER(KIND=MPI_ADDRESS_KIND) target_disp
        INTEGER target_count
        INTEGER target_datatype
        INTEGER win
        INTEGER request
        INTEGER ierror
        EXTERNAL MPI_RPUT
        CALL MPI_RPUT(origin_addr,origin_count,origin_datatype,&
                    target_rank,target_disp,target_count,target_datatype,win,&
                    request,ierror)
      END SUBROUTINE MPI_RPUT_T

      SUBROUTINE MPI_ALLTOALL_T(sendbuf,sendcount,sendtype,recvbuf,recvcount,&
                  recvtype,comm,ierror)
        <type> sendbuf<dims>
        INTEGER sendcount
        INTEGER sendtype
        <type1> recvbuf<dims1>
        INTEGER recvcount
        INTEGER recvtype
        INTEGER comm
        INTEGER ierror
        EXTERNAL MPI_ALLTOALL
        CALL MPI_ALLTOALL(sendbuf,sendcount,sendtype,recvbuf,recvcount,&
                    recvtype,comm,ierror)
      END SUBROUTINE MPI_ALLTOALL_T

      SUBROUTINE MPI_INEIGHBOR_ALLTOALLV_T(sendbuf,sendcounts,sdispls,sendtype,&
                  recvbuf,recvcounts,rdispls,recvtype,comm,request,ierror)
        <type> sendbuf<dims>
        INTEGER sendcounts(*)
        INTEGER sdispls(*)
        INTEGER sendtype
        <type1> recvbuf<dims1>
        INTEGER recvcounts(*)
        INTEGER rdispls(*)
        INTEGER recvtype
        INTEGER comm
        INTEGER request
        INTEGER ierror
        EXTERNAL MPI_INEIGHBOR_ALLTOALLV
        CALL MPI_INEIGHBOR_ALLTOALLV(sendbuf,sendcounts,sdispls,sendtype,&
                    recvbuf,recvcounts,rdispls,recvtype,comm,request,ierror)
      END SUBROUTINE MPI_INEIGHBOR_ALLTOALLV_T

      SUBROUTINE MPI_NEIGHBOR_ALLTOALLV_T(sendbuf,sendcounts,sdispls,sendtype,&
                  recvbuf,recvcounts,rdispls,recvtype,comm,ierror)
        <type> sendbuf<dims>
        INTEGER sendcounts(*)
        INTEGER sdispls(*)
        INTEGER sendtype
        <type1> recvbuf<dims1>
        INTEGER recvcounts(*)
        INTEGER rdispls(*)
        INTEGER recvtype
        INTEGER comm
        INTEGER ierror
        EXTERNAL MPI_NEIGHBOR_ALLTOALLV
        CALL MPI_NEIGHBOR_ALLTOALLV(sendbuf,sendcounts,sdispls,sendtype,&
                    recvbuf,recvcounts,rdispls,recvtype,comm,ierror)
      END SUBROUTINE MPI_NEIGHBOR_ALLTOALLV_T

      SUBROUTINE MPI_INEIGHBOR_ALLTOALLW_T(sendbuf,sendcounts,sdispls,&
                  sendtypes,recvbuf,recvcounts,rdispls,recvtypes,comm,request,&
                  ierror)
        <type> sendbuf<dims>
        INTEGER sendcounts(*)
        INTEGER(KIND=MPI_ADDRESS_KIND) sdispls(*)
        INTEGER sendtypes(*)
        <type1> recvbuf<dims1>
        INTEGER recvcounts(*)
        INTEGER(KIND=MPI_ADDRESS_KIND) rdispls(*)
        INTEGER recvtypes(*)
        INTEGER comm
        INTEGER request
        INTEGER ierror
        EXTERNAL MPI_INEIGHBOR_ALLTOALLW
        CALL MPI_INEIGHBOR_ALLTOALLW(sendbuf,sendcounts,sdispls,&
                    sendtypes,recvbuf,recvcounts,rdispls,recvtypes,comm,&
                    request,ierror)
      END SUBROUTINE MPI_INEIGHBOR_ALLTOALLW_T

      SUBROUTINE MPI_RSEND_INIT_T(buf,count,datatype,dest,tag,comm,request,&
                  ierror)
        <type> buf<dims>
        INTEGER count
        INTEGER datatype
        INTEGER dest
        INTEGER tag
        INTEGER comm
        INTEGER request
        INTEGER ierror
        EXTERNAL MPI_RSEND_INIT
        CALL MPI_RSEND_INIT(buf,count,datatype,dest,tag,comm,request,&
                    ierror)
      END SUBROUTINE MPI_RSEND_INIT_T

      SUBROUTINE MPI_COMM_SET_ATTR_T(comm,comm_keyval,attribute_val,ierror)
        INTEGER comm
        INTEGER comm_keyval
        <type> attribute_val<dims>
        INTEGER ierror
        EXTERNAL MPI_COMM_SET_ATTR
        CALL MPI_COMM_SET_ATTR(comm,comm_keyval,attribute_val,ierror)
      END SUBROUTINE MPI_COMM_SET_ATTR_T

      SUBROUTINE MPI_TYPE_GET_ATTR_T(datatype,type_keyval,attribute_val,flag,&
                  ierror)
        INTEGER datatype
        INTEGER type_keyval
        <type> attribute_val<dims>
        LOGICAL flag
        INTEGER ierror
        EXTERNAL MPI_TYPE_GET_ATTR
        CALL MPI_TYPE_GET_ATTR(datatype,type_keyval,attribute_val,flag,&
                    ierror)
      END SUBROUTINE MPI_TYPE_GET_ATTR_T

      SUBROUTINE MPI_ALLGATHER_T(sendbuf,sendcount,sendtype,recvbuf,recvcount,&
                  recvtype,comm,ierror)
        <type> sendbuf<dims>
        INTEGER sendcount
        INTEGER sendtype
        <type1> recvbuf<dims1>
        INTEGER recvcount
        INTEGER recvtype
        INTEGER comm
        INTEGER ierror
        EXTERNAL MPI_ALLGATHER
        CALL MPI_ALLGATHER(sendbuf,sendcount,sendtype,recvbuf,recvcount,&
                    recvtype,comm,ierror)
      END SUBROUTINE MPI_ALLGATHER_T

      SUBROUTINE MPI_BSEND_INIT_T(buf,count,datatype,dest,tag,comm,request,&
                  ierror)
        <type> buf<dims>
        INTEGER count
        INTEGER datatype
        INTEGER dest
        INTEGER tag
        INTEGER comm
        INTEGER request
        INTEGER ierror
        EXTERNAL MPI_BSEND_INIT
        CALL MPI_BSEND_INIT(buf,count,datatype,dest,tag,comm,request,&
                    ierror)
      END SUBROUTINE MPI_BSEND_INIT_T

      SUBROUTINE MPI_REDUCE_SCATTER_BLOCK_T(sendbuf,recvbuf,recvcount,datatype,&
                  op,comm,ierror)
        <type> sendbuf<dims>
        <type1> recvbuf<dims1>
        INTEGER recvcount
        INTEGER datatype
        INTEGER op
        INTEGER comm
        INTEGER ierror
        EXTERNAL MPI_REDUCE_SCATTER_BLOCK
        CALL MPI_REDUCE_SCATTER_BLOCK(sendbuf,recvbuf,recvcount,datatype,&
                    op,comm,ierror)
      END SUBROUTINE MPI_REDUCE_SCATTER_BLOCK_T

      SUBROUTINE MPI_NEIGHBOR_ALLGATHER_T(sendbuf,sendcount,sendtype,recvbuf,&
                  recvcount,recvtype,comm,ierror)
        <type> sendbuf<dims>
        INTEGER sendcount
        INTEGER sendtype
        <type1> recvbuf<dims1>
        INTEGER recvcount
        INTEGER recvtype
        INTEGER comm
        INTEGER ierror
        EXTERNAL MPI_NEIGHBOR_ALLGATHER
        CALL MPI_NEIGHBOR_ALLGATHER(sendbuf,sendcount,sendtype,recvbuf,&
                    recvcount,recvtype,comm,ierror)
      END SUBROUTINE MPI_NEIGHBOR_ALLGATHER_T

      SUBROUTINE MPI_GATHER_T(sendbuf,sendcount,sendtype,recvbuf,recvcount,&
                  recvtype,root,comm,ierror)
        <type> sendbuf<dims>
        INTEGER sendcount
        INTEGER sendtype
        <type1> recvbuf<dims1>
        INTEGER recvcount
        INTEGER recvtype
        INTEGER root
        INTEGER comm
        INTEGER ierror
        EXTERNAL MPI_GATHER
        CALL MPI_GATHER(sendbuf,sendcount,sendtype,recvbuf,recvcount,&
                    recvtype,root,comm,ierror)
      END SUBROUTINE MPI_GATHER_T

      SUBROUTINE MPI_REDUCE_T(sendbuf,recvbuf,count,datatype,op,root,comm,&
                  ierror)
        <type> sendbuf<dims>
        <type1> recvbuf<dims1>
        INTEGER count
        INTEGER datatype
        INTEGER op
        INTEGER root
        INTEGER comm
        INTEGER ierror
        EXTERNAL MPI_REDUCE
        CALL MPI_REDUCE(sendbuf,recvbuf,count,datatype,op,root,comm,&
                    ierror)
      END SUBROUTINE MPI_REDUCE_T

      SUBROUTINE MPI_WIN_CREATE_T(base,size,disp_unit,info,comm,win,ierror)
        <type> base<dims>
        INTEGER(KIND=MPI_ADDRESS_KIND) size
        INTEGER disp_unit
        INTEGER info
        INTEGER comm
        INTEGER win
        INTEGER ierror
        EXTERNAL MPI_WIN_CREATE
        CALL MPI_WIN_CREATE(base,size,disp_unit,info,comm,win,ierror)
      END SUBROUTINE MPI_WIN_CREATE_T

      SUBROUTINE MPI_SCATTERV_T(sendbuf,sendcounts,displs,sendtype,recvbuf,&
                  recvcount,recvtype,root,comm,ierror)
        <type> sendbuf<dims>
        INTEGER sendcounts(*)
        INTEGER displs(*)
        INTEGER sendtype
        <type1> recvbuf<dims1>
        INTEGER recvcount
        INTEGER recvtype
        INTEGER root
        INTEGER comm
        INTEGER ierror
        EXTERNAL MPI_SCATTERV
        CALL MPI_SCATTERV(sendbuf,sendcounts,displs,sendtype,recvbuf,&
                    recvcount,recvtype,root,comm,ierror)
      END SUBROUTINE MPI_SCATTERV_T

      SUBROUTINE MPI_IRSEND_T(buf,count,datatype,dest,tag,comm,request,ierror)
        <type> buf<dims>
        INTEGER count
        INTEGER datatype
        INTEGER dest
        INTEGER tag
        INTEGER comm
        INTEGER request
        INTEGER ierror
        EXTERNAL MPI_IRSEND
        CALL MPI_IRSEND(buf,count,datatype,dest,tag,comm,request,ierror)
      END SUBROUTINE MPI_IRSEND_T

      SUBROUTINE MPI_IREDUCE_SCATTER_BLOCK_T(sendbuf,recvbuf,recvcount,&
                  datatype,op,comm,request,ierror)
        <type> sendbuf<dims>
        <type1> recvbuf<dims1>
        INTEGER recvcount
        INTEGER datatype
        INTEGER op
        INTEGER comm
        INTEGER request
        INTEGER ierror
        EXTERNAL MPI_IREDUCE_SCATTER_BLOCK
        CALL MPI_IREDUCE_SCATTER_BLOCK(sendbuf,recvbuf,recvcount,&
                    datatype,op,comm,request,ierror)
      END SUBROUTINE MPI_IREDUCE_SCATTER_BLOCK_T

      SUBROUTINE MPI_ISCAN_T(sendbuf,recvbuf,count,datatype,op,comm,request,&
                  ierror)
        <type> sendbuf<dims>
        <type1> recvbuf<dims1>
        INTEGER count
        INTEGER datatype
        INTEGER op
        INTEGER comm
        INTEGER request
        INTEGER ierror
        EXTERNAL MPI_ISCAN
        CALL MPI_ISCAN(sendbuf,recvbuf,count,datatype,op,comm,request,&
                    ierror)
      END SUBROUTINE MPI_ISCAN_T

      SUBROUTINE MPI_TYPE_CREATE_KEYVAL_T(type_copy_attr_fn,&
                  type_delete_attr_fn,type_keyval,extra_state,ierror)
        EXTERNAL type_copy_attr_fn
        EXTERNAL type_delete_attr_fn
        INTEGER type_keyval
        <type> extra_state<dims>
        INTEGER ierror
        EXTERNAL MPI_TYPE_CREATE_KEYVAL
        CALL MPI_TYPE_CREATE_KEYVAL(type_copy_attr_fn,&
                    type_delete_attr_fn,type_keyval,extra_state,ierror)
      END SUBROUTINE MPI_TYPE_CREATE_KEYVAL_T

      SUBROUTINE MPI_PUT_T(origin_addr,origin_count,origin_datatype,&
                  target_rank,target_disp,target_count,target_datatype,win,&
                  ierror)
        <type> origin_addr<dims>
        INTEGER origin_count
        INTEGER origin_datatype
        INTEGER target_rank
        INTEGER(KIND=MPI_ADDRESS_KIND) target_disp
        INTEGER target_count
        INTEGER target_datatype
        INTEGER win
        INTEGER ierror
        EXTERNAL MPI_PUT
        CALL MPI_PUT(origin_addr,origin_count,origin_datatype,&
                    target_rank,target_disp,target_count,target_datatype,win,&
                    ierror)
      END SUBROUTINE MPI_PUT_T

      SUBROUTINE MPI_WIN_SET_ATTR_T(win,win_keyval,attribute_val,ierror)
        INTEGER win
        INTEGER win_keyval
        <type> attribute_val<dims>
        INTEGER ierror
        EXTERNAL MPI_WIN_SET_ATTR
        CALL MPI_WIN_SET_ATTR(win,win_keyval,attribute_val,ierror)
      END SUBROUTINE MPI_WIN_SET_ATTR_T

      SUBROUTINE MPI_EXSCAN_T(sendbuf,recvbuf,count,datatype,op,comm,ierror)
        <type> sendbuf<dims>
        <type1> recvbuf<dims1>
        INTEGER count
        INTEGER datatype
        INTEGER op
        INTEGER comm
        INTEGER ierror
        EXTERNAL MPI_EXSCAN
        CALL MPI_EXSCAN(sendbuf,recvbuf,count,datatype,op,comm,ierror)
      END SUBROUTINE MPI_EXSCAN_T

      SUBROUTINE MPI_ISCATTER_T(sendbuf,sendcount,sendtype,recvbuf,recvcount,&
                  recvtype,root,comm,request,ierror)
        <type> sendbuf<dims>
        INTEGER sendcount
        INTEGER sendtype
        <type1> recvbuf<dims1>
        INTEGER recvcount
        INTEGER recvtype
        INTEGER root
        INTEGER comm
        INTEGER request
        INTEGER ierror
        EXTERNAL MPI_ISCATTER
        CALL MPI_ISCATTER(sendbuf,sendcount,sendtype,recvbuf,recvcount,&
                    recvtype,root,comm,request,ierror)
      END SUBROUTINE MPI_ISCATTER_T

      SUBROUTINE MPI_NEIGHBOR_ALLTOALLW_T(sendbuf,sendcounts,sdispls,sendtypes,&
                  recvbuf,recvcounts,rdispls,recvtypes,comm,ierror)
        <type> sendbuf<dims>
        INTEGER sendcounts(*)
        INTEGER(KIND=MPI_ADDRESS_KIND) sdispls(*)
        INTEGER sendtypes(*)
        <type1> recvbuf<dims1>
        INTEGER recvcounts(*)
        INTEGER(KIND=MPI_ADDRESS_KIND) rdispls(*)
        INTEGER recvtypes(*)
        INTEGER comm
        INTEGER ierror
        EXTERNAL MPI_NEIGHBOR_ALLTOALLW
        CALL MPI_NEIGHBOR_ALLTOALLW(sendbuf,sendcounts,sdispls,sendtypes,&
                    recvbuf,recvcounts,rdispls,recvtypes,comm,ierror)
      END SUBROUTINE MPI_NEIGHBOR_ALLTOALLW_T

      SUBROUTINE MPI_ALLREDUCE_T(sendbuf,recvbuf,count,datatype,op,comm,ierror)
        <type> sendbuf<dims>
        <type1> recvbuf<dims1>
        INTEGER count
        INTEGER datatype
        INTEGER op
        INTEGER comm
        INTEGER ierror
        EXTERNAL MPI_ALLREDUCE
        CALL MPI_ALLREDUCE(sendbuf,recvbuf,count,datatype,op,comm,ierror)
      END SUBROUTINE MPI_ALLREDUCE_T

      SUBROUTINE MPI_WIN_GET_ATTR_T(win,win_keyval,attribute_val,flag,ierror)
        INTEGER win
        INTEGER win_keyval
        <type> attribute_val<dims>
        LOGICAL flag
        INTEGER ierror
        EXTERNAL MPI_WIN_GET_ATTR
        CALL MPI_WIN_GET_ATTR(win,win_keyval,attribute_val,flag,ierror)
      END SUBROUTINE MPI_WIN_GET_ATTR_T

      SUBROUTINE MPI_ALLTOALLV_T(sendbuf,sendcounts,sdispls,sendtype,recvbuf,&
                  recvcounts,rdispls,recvtype,comm,ierror)
        <type> sendbuf<dims>
        INTEGER sendcounts(*)
        INTEGER sdispls(*)
        INTEGER sendtype
        <type1> recvbuf<dims1>
        INTEGER recvcounts(*)
        INTEGER rdispls(*)
        INTEGER recvtype
        INTEGER comm
        INTEGER ierror
        EXTERNAL MPI_ALLTOALLV
        CALL MPI_ALLTOALLV(sendbuf,sendcounts,sdispls,sendtype,recvbuf,&
                    recvcounts,rdispls,recvtype,comm,ierror)
      END SUBROUTINE MPI_ALLTOALLV_T

      SUBROUTINE MPI_SENDRECV_REPLACE_T(buf,count,datatype,dest,sendtag,source,&
                  recvtag,comm,status,ierror)
        <type> buf<dims>
        INTEGER count
        INTEGER datatype
        INTEGER dest
        INTEGER sendtag
        INTEGER source
        INTEGER recvtag
        INTEGER comm
        INTEGER status(MPI_STATUS_SIZE)
        INTEGER ierror
        EXTERNAL MPI_SENDRECV_REPLACE
        CALL MPI_SENDRECV_REPLACE(buf,count,datatype,dest,sendtag,source,&
                    recvtag,comm,status,ierror)
      END SUBROUTINE MPI_SENDRECV_REPLACE_T

      SUBROUTINE MPI_WIN_DETACH_T(win,base,ierror)
        INTEGER win
        <type> base<dims>
        INTEGER ierror
        EXTERNAL MPI_WIN_DETACH
        CALL MPI_WIN_DETACH(win,base,ierror)
      END SUBROUTINE MPI_WIN_DETACH_T

      SUBROUTINE MPI_INEIGHBOR_ALLGATHER_T(sendbuf,sendcount,sendtype,recvbuf,&
                  recvcount,recvtype,comm,request,ierror)
        <type> sendbuf<dims>
        INTEGER sendcount
        INTEGER sendtype
        <type1> recvbuf<dims1>
        INTEGER recvcount
        INTEGER recvtype
        INTEGER comm
        INTEGER request
        INTEGER ierror
        EXTERNAL MPI_INEIGHBOR_ALLGATHER
        CALL MPI_INEIGHBOR_ALLGATHER(sendbuf,sendcount,sendtype,recvbuf,&
                    recvcount,recvtype,comm,request,ierror)
      END SUBROUTINE MPI_INEIGHBOR_ALLGATHER_T

      SUBROUTINE MPI_RGET_ACCUMULATE_T(origin_addr,origin_count,&
                  origin_datatype,result_addr,result_count,result_datatype,&
                  target_rank,target_disp,target_count,target_datatype,op,win,&
                  request,ierror)
        <type> origin_addr<dims>
        INTEGER origin_count
        INTEGER origin_datatype
        <type1> result_addr<dims1>
        INTEGER result_count
        INTEGER result_datatype
        INTEGER target_rank
        INTEGER(KIND=MPI_ADDRESS_KIND) target_disp
        INTEGER target_count
        INTEGER target_datatype
        INTEGER op
        INTEGER win
        INTEGER request
        INTEGER ierror
        EXTERNAL MPI_RGET_ACCUMULATE
        CALL MPI_RGET_ACCUMULATE(origin_addr,origin_count,&
                    origin_datatype,result_addr,result_count,result_datatype,&
                    target_rank,target_disp,target_count,target_datatype,op,&
                    win,request,ierror)
      END SUBROUTINE MPI_RGET_ACCUMULATE_T

      SUBROUTINE MPI_ISSEND_T(buf,count,datatype,dest,tag,comm,request,ierror)
        <type> buf<dims>
        INTEGER count
        INTEGER datatype
        INTEGER dest
        INTEGER tag
        INTEGER comm
        INTEGER request
        INTEGER ierror
        EXTERNAL MPI_ISSEND
        CALL MPI_ISSEND(buf,count,datatype,dest,tag,comm,request,ierror)
      END SUBROUTINE MPI_ISSEND_T

      SUBROUTINE MPI_SCAN_T(sendbuf,recvbuf,count,datatype,op,comm,ierror)
        <type> sendbuf<dims>
        <type1> recvbuf<dims1>
        INTEGER count
        INTEGER datatype
        INTEGER op
        INTEGER comm
        INTEGER ierror
        EXTERNAL MPI_SCAN
        CALL MPI_SCAN(sendbuf,recvbuf,count,datatype,op,comm,ierror)
      END SUBROUTINE MPI_SCAN_T

      SUBROUTINE MPI_IBSEND_T(buf,count,datatype,dest,tag,comm,request,ierror)
        <type> buf<dims>
        INTEGER count
        INTEGER datatype
        INTEGER dest
        INTEGER tag
        INTEGER comm
        INTEGER request
        INTEGER ierror
        EXTERNAL MPI_IBSEND
        CALL MPI_IBSEND(buf,count,datatype,dest,tag,comm,request,ierror)
      END SUBROUTINE MPI_IBSEND_T

      SUBROUTINE MPI_MRECV_T(buf,count,datatype,message,status,ierror)
        <type> buf<dims>
        INTEGER count
        INTEGER datatype
        INTEGER message
        INTEGER status(MPI_STATUS_SIZE)
        INTEGER ierror
        EXTERNAL MPI_MRECV
        CALL MPI_MRECV(buf,count,datatype,message,status,ierror)
      END SUBROUTINE MPI_MRECV_T

      SUBROUTINE MPI_KEYVAL_CREATE_T(copy_fn,delete_fn,keyval,extra_state,&
                  ierror)
        EXTERNAL copy_fn
        EXTERNAL delete_fn
        INTEGER keyval
        <type> extra_state<dims>
        INTEGER ierror
        EXTERNAL MPI_KEYVAL_CREATE
        CALL MPI_KEYVAL_CREATE(copy_fn,delete_fn,keyval,extra_state,&
                    ierror)
      END SUBROUTINE MPI_KEYVAL_CREATE_T

      SUBROUTINE MPI_IRECV_T(buf,count,datatype,source,tag,comm,request,ierror)
        <type> buf<dims>
        INTEGER count
        INTEGER datatype
        INTEGER source
        INTEGER tag
        INTEGER comm
        INTEGER request
        INTEGER ierror
        EXTERNAL MPI_IRECV
        CALL MPI_IRECV(buf,count,datatype,source,tag,comm,request,ierror)
      END SUBROUTINE MPI_IRECV_T

      SUBROUTINE MPI_INEIGHBOR_ALLGATHERV_T(sendbuf,sendcount,sendtype,recvbuf,&
                  recvcounts,displs,recvtype,comm,request,ierror)
        <type> sendbuf<dims>
        INTEGER sendcount
        INTEGER sendtype
        <type1> recvbuf<dims1>
        INTEGER recvcounts(*)
        INTEGER displs(*)
        INTEGER recvtype
        INTEGER comm
        INTEGER request
        INTEGER ierror
        EXTERNAL MPI_INEIGHBOR_ALLGATHERV
        CALL MPI_INEIGHBOR_ALLGATHERV(sendbuf,sendcount,sendtype,recvbuf,&
                    recvcounts,displs,recvtype,comm,request,ierror)
      END SUBROUTINE MPI_INEIGHBOR_ALLGATHERV_T

      SUBROUTINE MPI_IREDUCE_SCATTER_T(sendbuf,recvbuf,recvcounts,datatype,op,&
                  comm,request,ierror)
        <type> sendbuf<dims>
        <type1> recvbuf<dims1>
        INTEGER recvcounts(*)
        INTEGER datatype
        INTEGER op
        INTEGER comm
        INTEGER request
        INTEGER ierror
        EXTERNAL MPI_IREDUCE_SCATTER
        CALL MPI_IREDUCE_SCATTER(sendbuf,recvbuf,recvcounts,datatype,op,&
                    comm,request,ierror)
      END SUBROUTINE MPI_IREDUCE_SCATTER_T

      SUBROUTINE MPI_ACCUMULATE_T(origin_addr,origin_count,origin_datatype,&
                  target_rank,target_disp,target_count,target_datatype,op,win,&
                  ierror)
        <type> origin_addr<dims>
        INTEGER origin_count
        INTEGER origin_datatype
        INTEGER target_rank
        INTEGER(KIND=MPI_ADDRESS_KIND) target_disp
        INTEGER target_count
        INTEGER target_datatype
        INTEGER op
        INTEGER win
        INTEGER ierror
        EXTERNAL MPI_ACCUMULATE
        CALL MPI_ACCUMULATE(origin_addr,origin_count,origin_datatype,&
                    target_rank,target_disp,target_count,target_datatype,op,&
                    win,ierror)
      END SUBROUTINE MPI_ACCUMULATE_T

      SUBROUTINE MPI_REDUCE_LOCAL_T(inbuf,inoutbuf,count,datatype,op,ierror)
        <type> inbuf<dims>
        <type1> inoutbuf<dims1>
        INTEGER count
        INTEGER datatype
        INTEGER op
        INTEGER ierror
        EXTERNAL MPI_REDUCE_LOCAL
        CALL MPI_REDUCE_LOCAL(inbuf,inoutbuf,count,datatype,op,ierror)
      END SUBROUTINE MPI_REDUCE_LOCAL_T

      SUBROUTINE MPI_SSEND_T(buf,count,datatype,dest,tag,comm,ierror)
        <type> buf<dims>
        INTEGER count
        INTEGER datatype
        INTEGER dest
        INTEGER tag
        INTEGER comm
        INTEGER ierror
        EXTERNAL MPI_SSEND
        CALL MPI_SSEND(buf,count,datatype,dest,tag,comm,ierror)
      END SUBROUTINE MPI_SSEND_T

      SUBROUTINE MPI_WIN_CREATE_KEYVAL_T(win_copy_attr_fn,win_delete_attr_fn,&
                  win_keyval,extra_state,ierror)
        EXTERNAL win_copy_attr_fn
        EXTERNAL win_delete_attr_fn
        INTEGER win_keyval
        <type> extra_state<dims>
        INTEGER ierror
        EXTERNAL MPI_WIN_CREATE_KEYVAL
        CALL MPI_WIN_CREATE_KEYVAL(win_copy_attr_fn,win_delete_attr_fn,&
                    win_keyval,extra_state,ierror)
      END SUBROUTINE MPI_WIN_CREATE_KEYVAL_T

      SUBROUTINE MPI_BUFFER_ATTACH_T(buffer,size,ierror)
        <type> buffer<dims>
        INTEGER size
        INTEGER ierror
        EXTERNAL MPI_BUFFER_ATTACH
        CALL MPI_BUFFER_ATTACH(buffer,size,ierror)
      END SUBROUTINE MPI_BUFFER_ATTACH_T

      SUBROUTINE MPI_ATTR_GET_T(comm,keyval,attribute_val,flag,ierror)
        INTEGER comm
        INTEGER keyval
        <type> attribute_val<dims>
        LOGICAL flag
        INTEGER ierror
        EXTERNAL MPI_ATTR_GET
        CALL MPI_ATTR_GET(comm,keyval,attribute_val,flag,ierror)
      END SUBROUTINE MPI_ATTR_GET_T

      SUBROUTINE MPI_WIN_ATTACH_T(win,base,size,ierror)
        INTEGER win
        <type> base<dims>
        INTEGER(KIND=MPI_ADDRESS_KIND) size
        INTEGER ierror
        EXTERNAL MPI_WIN_ATTACH
        CALL MPI_WIN_ATTACH(win,base,size,ierror)
      END SUBROUTINE MPI_WIN_ATTACH_T

      SUBROUTINE MPI_ALLOC_MEM_T(size,info,baseptr,ierror)
        INTEGER(KIND=MPI_ADDRESS_KIND) size
        INTEGER info
        <type> baseptr<dims>
        INTEGER ierror
        EXTERNAL MPI_ALLOC_MEM
        CALL MPI_ALLOC_MEM(size,info,baseptr,ierror)
      END SUBROUTINE MPI_ALLOC_MEM_T

      SUBROUTINE MPI_IALLREDUCE_T(sendbuf,recvbuf,count,datatype,op,comm,&
                  request,ierror)
        <type> sendbuf<dims>
        <type1> recvbuf<dims1>
        INTEGER count
        INTEGER datatype
        INTEGER op
        INTEGER comm
        INTEGER request
        INTEGER ierror
        EXTERNAL MPI_IALLREDUCE
        CALL MPI_IALLREDUCE(sendbuf,recvbuf,count,datatype,op,comm,&
                    request,ierror)
      END SUBROUTINE MPI_IALLREDUCE_T

      SUBROUTINE MPI_REDUCE_SCATTER_T(sendbuf,recvbuf,recvcounts,datatype,op,&
                  comm,ierror)
        <type> sendbuf<dims>
        <type1> recvbuf<dims1>
        INTEGER recvcounts(*)
        INTEGER datatype
        INTEGER op
        INTEGER comm
        INTEGER ierror
        EXTERNAL MPI_REDUCE_SCATTER
        CALL MPI_REDUCE_SCATTER(sendbuf,recvbuf,recvcounts,datatype,op,&
                    comm,ierror)
      END SUBROUTINE MPI_REDUCE_SCATTER_T

      SUBROUTINE MPI_NEIGHBOR_ALLGATHERV_T(sendbuf,sendcount,sendtype,recvbuf,&
                  recvcounts,displs,recvtype,comm,ierror)
        <type> sendbuf<dims>
        INTEGER sendcount
        INTEGER sendtype
        <type1> recvbuf<dims1>
        INTEGER recvcounts(*)
        INTEGER displs(*)
        INTEGER recvtype
        INTEGER comm
        INTEGER ierror
        EXTERNAL MPI_NEIGHBOR_ALLGATHERV
        CALL MPI_NEIGHBOR_ALLGATHERV(sendbuf,sendcount,sendtype,recvbuf,&
                    recvcounts,displs,recvtype,comm,ierror)
      END SUBROUTINE MPI_NEIGHBOR_ALLGATHERV_T

      SUBROUTINE MPI_IALLTOALLW_T(sendbuf,sendcounts,sdispls,sendtypes,recvbuf,&
                  recvcounts,rdispls,recvtypes,comm,request,ierror)
        <type> sendbuf<dims>
        INTEGER sendcounts(*)
        INTEGER sdispls(*)
        INTEGER sendtypes(*)
        <type1> recvbuf<dims1>
        INTEGER recvcounts(*)
        INTEGER rdispls(*)
        INTEGER recvtypes(*)
        INTEGER comm
        INTEGER request
        INTEGER ierror
        EXTERNAL MPI_IALLTOALLW
        CALL MPI_IALLTOALLW(sendbuf,sendcounts,sdispls,sendtypes,recvbuf,&
                    recvcounts,rdispls,recvtypes,comm,request,ierror)
      END SUBROUTINE MPI_IALLTOALLW_T

      SUBROUTINE MPI_ISEND_T(buf,count,datatype,dest,tag,comm,request,ierror)
        <type> buf<dims>
        INTEGER count
        INTEGER datatype
        INTEGER dest
        INTEGER tag
        INTEGER comm
        INTEGER request
        INTEGER ierror
        EXTERNAL MPI_ISEND
        CALL MPI_ISEND(buf,count,datatype,dest,tag,comm,request,ierror)
      END SUBROUTINE MPI_ISEND_T

      SUBROUTINE MPI_SEND_T(buf,count,datatype,dest,tag,comm,ierror)
        <type> buf<dims>
        INTEGER count
        INTEGER datatype
        INTEGER dest
        INTEGER tag
        INTEGER comm
        INTEGER ierror
        EXTERNAL MPI_SEND
        CALL MPI_SEND(buf,count,datatype,dest,tag,comm,ierror)
      END SUBROUTINE MPI_SEND_T

      SUBROUTINE MPI_GET_ADDRESS_T(location,address,ierror)
        <type> location<dims>
        INTEGER(KIND=MPI_ADDRESS_KIND) address
        INTEGER ierror
        EXTERNAL MPI_GET_ADDRESS
        CALL MPI_GET_ADDRESS(location,address,ierror)
      END SUBROUTINE MPI_GET_ADDRESS_T

      SUBROUTINE MPI_ADDRESS_T(location,address,ierror)
        <type> location<dims>
        INTEGER(KIND=MPI_ADDRESS_KIND) address
        INTEGER ierror
        EXTERNAL MPI_ADDRESS
        CALL MPI_ADDRESS(location,address,ierror)
      END SUBROUTINE MPI_ADDRESS_T

      SUBROUTINE MPI_IMRECV_T(buf,count,datatype,message,request,ierror)
        <type> buf<dims>
        INTEGER count
        INTEGER datatype
        INTEGER message
        INTEGER request
        INTEGER ierror
        EXTERNAL MPI_IMRECV
        CALL MPI_IMRECV(buf,count,datatype,message,request,ierror)
      END SUBROUTINE MPI_IMRECV_T

      SUBROUTINE MPI_GET_ACCUMULATE_T(origin_addr,origin_count,origin_datatype,&
                  result_addr,result_count,result_datatype,target_rank,&
                  target_disp,target_count,target_datatype,op,win,ierror)
        <type> origin_addr<dims>
        INTEGER origin_count
        INTEGER origin_datatype
        <type1> result_addr<dims1>
        INTEGER result_count
        INTEGER result_datatype
        INTEGER target_rank
        INTEGER(KIND=MPI_ADDRESS_KIND) target_disp
        INTEGER target_count
        INTEGER target_datatype
        INTEGER op
        INTEGER win
        INTEGER ierror
        EXTERNAL MPI_GET_ACCUMULATE
        CALL MPI_GET_ACCUMULATE(origin_addr,origin_count,origin_datatype,&
                    result_addr,result_count,result_datatype,target_rank,&
                    target_disp,target_count,target_datatype,op,win,ierror)
      END SUBROUTINE MPI_GET_ACCUMULATE_T

      SUBROUTINE MPI_IEXSCAN_T(sendbuf,recvbuf,count,datatype,op,comm,request,&
                  ierror)
        <type> sendbuf<dims>
        <type1> recvbuf<dims1>
        INTEGER count
        INTEGER datatype
        INTEGER op
        INTEGER comm
        INTEGER request
        INTEGER ierror
        EXTERNAL MPI_IEXSCAN
        CALL MPI_IEXSCAN(sendbuf,recvbuf,count,datatype,op,comm,request,&
                    ierror)
      END SUBROUTINE MPI_IEXSCAN_T

      SUBROUTINE MPI_IALLGATHERV_T(sendbuf,sendcount,sendtype,recvbuf,&
                  recvcounts,displs,recvtype,comm,request,ierror)
        <type> sendbuf<dims>
        INTEGER sendcount
        INTEGER sendtype
        <type1> recvbuf<dims1>
        INTEGER recvcounts(*)
        INTEGER displs(*)
        INTEGER recvtype
        INTEGER comm
        INTEGER request
        INTEGER ierror
        EXTERNAL MPI_IALLGATHERV
        CALL MPI_IALLGATHERV(sendbuf,sendcount,sendtype,recvbuf,&
                    recvcounts,displs,recvtype,comm,request,ierror)
      END SUBROUTINE MPI_IALLGATHERV_T

      END MODULE MPI_t1_s
