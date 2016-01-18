!   -*- Mode: Fortran; -*-
!
!   (C) 2014 by Argonne National Laboratory.
!   See COPYRIGHT in top-level directory.
!

! MPI-3.0 A.3
module pmpi_f08
use,intrinsic :: iso_c_binding, only: c_ptr
use :: mpi_f08_types
use :: mpi_f08_compile_constants
use :: mpi_f08_link_constants
use :: mpi_f08_callbacks

implicit none

interface PMPI_Bsend
    subroutine PMPIR_Bsend_f08ts(buf, count, datatype, dest, tag, comm, ierror)
        use :: mpi_f08_types, only : MPI_Datatype, MPI_Comm, MPI_Request
        implicit none
        type(*), dimension(..), intent(in) :: buf
        integer, intent(in) :: count, dest, tag
        type(MPI_Datatype), intent(in) :: datatype
        type(MPI_Comm), intent(in) :: comm
        integer, optional, intent(out) :: ierror
    end subroutine PMPIR_Bsend_f08ts
end interface PMPI_Bsend

interface PMPI_Bsend_init
    subroutine PMPIR_Bsend_init_f08ts(buf, count, datatype, dest, tag, comm, request, ierror)
        use :: mpi_f08_types, only : MPI_Datatype, MPI_Comm, MPI_Request
        implicit none
        type(*), dimension(..) :: buf
        integer, intent(in) :: count, dest, tag
        type(MPI_Datatype), intent(in) :: datatype
        type(MPI_Comm), intent(in) :: comm
        type(MPI_Request), intent(out) :: request
        integer, optional, intent(out) :: ierror
    end subroutine PMPIR_Bsend_init_f08ts
end interface PMPI_Bsend_init

interface PMPI_Buffer_attach
    subroutine PMPIR_Buffer_attach_f08ts(buffer, size, ierror)
        implicit none
        type(*), dimension(..) :: buffer
        integer, intent(in) :: size
        integer, optional, intent(out) :: ierror
    end subroutine PMPIR_Buffer_attach_f08ts
end interface PMPI_Buffer_attach

interface PMPI_Buffer_detach
    subroutine PMPIR_Buffer_detach_f08(buffer_addr, size, ierror)
        use, intrinsic :: iso_c_binding, only : c_ptr
        implicit none
        type(c_ptr) :: buffer_addr
        integer, intent(out) :: size
        integer, optional, intent(out) :: ierror
    end subroutine PMPIR_Buffer_detach_f08
end interface PMPI_Buffer_detach

interface PMPI_Cancel
    subroutine PMPIR_Cancel_f08(request, ierror)
        use :: mpi_f08_types, only : MPI_Request
        implicit none
        type(MPI_Request), intent(in) :: request
        integer, optional, intent(out) :: ierror
    end subroutine PMPIR_Cancel_f08
end interface PMPI_Cancel

interface PMPI_Get_count
    subroutine PMPIR_Get_count_f08(status, datatype, count, ierror)
        use :: mpi_f08_types, only : MPI_Status, MPI_Datatype
        implicit none
        type(MPI_Status), intent(in) :: status
        type(MPI_Datatype), intent(in) :: datatype
        integer, intent(out) :: count
        integer, optional, intent(out) :: ierror
    end subroutine PMPIR_Get_count_f08
end interface PMPI_Get_count

interface PMPI_Ibsend
    subroutine PMPIR_Ibsend_f08ts(buf, count, datatype, dest, tag, comm, request, ierror)
        use :: mpi_f08_types, only : MPI_Datatype, MPI_Comm, MPI_Request
        implicit none
        type(*), dimension(..), intent(in), asynchronous :: buf
        integer, intent(in) :: count, dest, tag
        type(MPI_Datatype), intent(in) :: datatype
        type(MPI_Comm), intent(in) :: comm
        type(MPI_Request), intent(out) :: request
        integer, optional, intent(out) :: ierror
    end subroutine PMPIR_Ibsend_f08ts
end interface PMPI_Ibsend

interface PMPI_Iprobe
    subroutine PMPIR_Iprobe_f08(source, tag, comm, flag, status, ierror)
        use :: mpi_f08_types, only : MPI_Comm, MPI_Status
        implicit none
        integer, intent(in) :: source, tag
        type(MPI_Comm), intent(in) :: comm
        logical, intent(out) :: flag
        type(MPI_Status) :: status
        integer, optional, intent(out) :: ierror
    end subroutine PMPIR_Iprobe_f08
end interface PMPI_Iprobe

interface PMPI_Irecv
    subroutine PMPIR_Irecv_f08ts(buf, count, datatype, source, tag, comm, request, ierror)
        use :: mpi_f08_types, only : MPI_Datatype, MPI_Comm, MPI_Request
        implicit none
        type(*), dimension(..), asynchronous :: buf
        integer, intent(in) :: count, source, tag
        type(MPI_Datatype), intent(in) :: datatype
        type(MPI_Comm), intent(in) :: comm
        type(MPI_Request), intent(out) :: request
        integer, optional, intent(out) :: ierror
    end subroutine PMPIR_Irecv_f08ts
end interface PMPI_Irecv

interface PMPI_Irsend
    subroutine PMPIR_Irsend_f08ts(buf, count, datatype, dest, tag, comm, request, ierror)
        use :: mpi_f08_types, only : MPI_Datatype, MPI_Comm, MPI_Request
        implicit none
        type(*), dimension(..), intent(in), asynchronous :: buf
        integer, intent(in) :: count, dest, tag
        type(MPI_Datatype), intent(in) :: datatype
        type(MPI_Comm), intent(in) :: comm
        type(MPI_Request), intent(out) :: request
        integer, optional, intent(out) :: ierror
    end subroutine PMPIR_Irsend_f08ts
end interface PMPI_Irsend

interface PMPI_Isend
    subroutine PMPIR_Isend_f08ts(buf, count, datatype, dest, tag, comm, request, ierror)
        use :: mpi_f08_types, only : MPI_Datatype, MPI_Comm, MPI_Request
        implicit none
        type(*), dimension(..), intent(in), asynchronous :: buf
        integer, intent(in) :: count, dest, tag
        type(MPI_Datatype), intent(in) :: datatype
        type(MPI_Comm), intent(in) :: comm
        type(MPI_Request), intent(out) :: request
        integer, optional, intent(out) :: ierror
    end subroutine PMPIR_Isend_f08ts
end interface PMPI_Isend

interface PMPI_Issend
    subroutine PMPIR_Issend_f08ts(buf, count, datatype, dest, tag, comm, request, ierror)
        use :: mpi_f08_types, only : MPI_Datatype, MPI_Comm, MPI_Request
        implicit none
        type(*), dimension(..), intent(in), asynchronous :: buf
        integer, intent(in) :: count, dest, tag
        type(MPI_Datatype), intent(in) :: datatype
        type(MPI_Comm), intent(in) :: comm
        type(MPI_Request), intent(out) :: request
        integer, optional, intent(out) :: ierror
    end subroutine PMPIR_Issend_f08ts
end interface PMPI_Issend

interface PMPI_Probe
    subroutine PMPIR_Probe_f08(source, tag, comm, status, ierror)
        use :: mpi_f08_types, only : MPI_Comm, MPI_Status
        implicit none
        integer, intent(in) :: source, tag
        type(MPI_Comm), intent(in) :: comm
        type(MPI_Status) :: status
        integer, optional, intent(out) :: ierror
    end subroutine PMPIR_Probe_f08
end interface PMPI_Probe

interface PMPI_Recv
    subroutine PMPIR_Recv_f08ts(buf, count, datatype, source, tag, comm, status, ierror)
        use :: mpi_f08_types, only : MPI_Datatype, MPI_Comm, MPI_Status
        implicit none
        type(*), dimension(..) :: buf
        integer, intent(in) :: count, source, tag
        type(MPI_Datatype), intent(in) :: datatype
        type(MPI_Comm), intent(in) :: comm
        type(MPI_Status) :: status
        integer, optional, intent(out) :: ierror
    end subroutine PMPIR_Recv_f08ts
end interface PMPI_Recv

interface PMPI_Recv_init
    subroutine PMPIR_Recv_init_f08ts(buf, count, datatype, source, tag, comm, request, ierror)
        use :: mpi_f08_types, only : MPI_Datatype, MPI_Comm, MPI_Request
        implicit none
        type(*), dimension(..) :: buf
        integer, intent(in) :: count, source, tag
        type(MPI_Datatype), intent(in) :: datatype
        type(MPI_Comm), intent(in) :: comm
        type(MPI_Request), intent(out) :: request
        integer, optional, intent(out) :: ierror
    end subroutine PMPIR_Recv_init_f08ts
end interface PMPI_Recv_init

interface PMPI_Request_free
    subroutine PMPIR_Request_free_f08(request, ierror)
        use :: mpi_f08_types, only : MPI_Request
        implicit none
        type(MPI_Request), intent(inout) :: request
        integer, optional, intent(out) :: ierror
    end subroutine PMPIR_Request_free_f08
end interface PMPI_Request_free

interface PMPI_Request_get_status
    subroutine PMPIR_Request_get_status_f08(request, flag, status, ierror)
        use :: mpi_f08_types, only : MPI_Request, MPI_Status
        implicit none
        type(MPI_Request), intent(in) :: request
        logical, intent(out) :: flag
        type(MPI_Status) :: status
        integer, optional, intent(out) :: ierror
    end subroutine PMPIR_Request_get_status_f08
end interface PMPI_Request_get_status

interface PMPI_Rsend
    subroutine PMPIR_Rsend_f08ts(buf, count, datatype, dest, tag, comm, ierror)
        use :: mpi_f08_types, only : MPI_Datatype, MPI_Comm
        implicit none
        type(*), dimension(..), intent(in) :: buf
        integer, intent(in) :: count, dest, tag
        type(MPI_Datatype), intent(in) :: datatype
        type(MPI_Comm), intent(in) :: comm
        integer, optional, intent(out) :: ierror
    end subroutine PMPIR_Rsend_f08ts
end interface PMPI_Rsend

interface PMPI_Rsend_init
    subroutine PMPIR_Rsend_init_f08ts(buf, count, datatype, dest, tag, comm, request, ierror)
        use :: mpi_f08_types, only : MPI_Datatype, MPI_Comm, MPI_Request
        implicit none
        type(*), dimension(..) :: buf
        integer, intent(in) :: count, dest, tag
        type(MPI_Datatype), intent(in) :: datatype
        type(MPI_Comm), intent(in) :: comm
        type(MPI_Request), intent(out) :: request
        integer, optional, intent(out) :: ierror
    end subroutine PMPIR_Rsend_init_f08ts
end interface PMPI_Rsend_init

interface PMPI_Send
    subroutine PMPIR_Send_f08ts(buf, count, datatype, dest, tag, comm, ierror)
        use :: mpi_f08_types, only : MPI_Datatype, MPI_Comm
        implicit none
        type(*), dimension(..), intent(in) :: buf
        integer, intent(in) :: count, dest, tag
        type(MPI_Datatype), intent(in) :: datatype
        type(MPI_Comm), intent(in) :: comm
        integer, optional, intent(out) :: ierror
    end subroutine PMPIR_Send_f08ts
end interface PMPI_Send

interface PMPI_Sendrecv
    subroutine PMPIR_Sendrecv_f08ts(sendbuf, sendcount, sendtype, dest, sendtag, recvbuf, &
                   recvcount, recvtype, source, recvtag, comm, status, ierror)
        use :: mpi_f08_types, only : MPI_Datatype, MPI_Comm, MPI_Status
        implicit none
        type(*), dimension(..), intent(in) :: sendbuf
        type(*), dimension(..) :: recvbuf
        integer, intent(in) :: sendcount, dest, sendtag, recvcount, source, recvtag
        type(MPI_Datatype), intent(in) :: sendtype, recvtype
        type(MPI_Comm), intent(in) :: comm
        type(MPI_Status) :: status
        integer, optional, intent(out) :: ierror
    end subroutine PMPIR_Sendrecv_f08ts
end interface PMPI_Sendrecv

interface PMPI_Sendrecv_replace
    subroutine PMPIR_Sendrecv_replace_f08ts(buf, count, datatype, dest, sendtag, source, recvtag, &
                   comm, status, ierror)
        use :: mpi_f08_types, only : MPI_Datatype, MPI_Comm, MPI_Status
        implicit none
        type(*), dimension(..) :: buf
        integer, intent(in) :: count, dest, sendtag, source, recvtag
        type(MPI_Datatype), intent(in) :: datatype
        type(MPI_Comm), intent(in) :: comm
        type(MPI_Status) :: status
        integer, optional, intent(out) :: ierror
    end subroutine PMPIR_Sendrecv_replace_f08ts
end interface PMPI_Sendrecv_replace

interface PMPI_Send_init
    subroutine PMPIR_Send_init_f08ts(buf, count, datatype, dest, tag, comm, request, ierror)
        use :: mpi_f08_types, only : MPI_Datatype, MPI_Comm, MPI_Request
        implicit none
        type(*), dimension(..) :: buf
        integer, intent(in) :: count, dest, tag
        type(MPI_Datatype), intent(in) :: datatype
        type(MPI_Comm), intent(in) :: comm
        type(MPI_Request), intent(out) :: request
        integer, optional, intent(out) :: ierror
    end subroutine PMPIR_Send_init_f08ts
end interface PMPI_Send_init

interface PMPI_Ssend
    subroutine PMPIR_Ssend_f08ts(buf, count, datatype, dest, tag, comm, ierror)
        use :: mpi_f08_types, only : MPI_Datatype, MPI_Comm
        implicit none
        type(*), dimension(..), intent(in) :: buf
        integer, intent(in) :: count, dest, tag
        type(MPI_Datatype), intent(in) :: datatype
        type(MPI_Comm), intent(in) :: comm
        integer, optional, intent(out) :: ierror
    end subroutine PMPIR_Ssend_f08ts
end interface PMPI_Ssend

interface PMPI_Ssend_init
    subroutine PMPIR_Ssend_init_f08ts(buf, count, datatype, dest, tag, comm, request, ierror)
        use :: mpi_f08_types, only : MPI_Datatype, MPI_Comm, MPI_Request
        implicit none
        type(*), dimension(..) :: buf
        integer, intent(in) :: count, dest, tag
        type(MPI_Datatype), intent(in) :: datatype
        type(MPI_Comm), intent(in) :: comm
        type(MPI_Request), intent(out) :: request
        integer, optional, intent(out) :: ierror
    end subroutine PMPIR_Ssend_init_f08ts
end interface PMPI_Ssend_init

interface PMPI_Start
    subroutine PMPIR_Start_f08(request, ierror)
        use :: mpi_f08_types, only : MPI_Request
        implicit none
        type(MPI_Request), intent(inout) :: request
        integer, optional, intent(out) :: ierror
    end subroutine PMPIR_Start_f08
end interface PMPI_Start

interface PMPI_Startall
    subroutine PMPIR_Startall_f08(count, array_of_requests, ierror)
        use :: mpi_f08_types, only : MPI_Request
        implicit none
        integer, intent(in) :: count
        type(MPI_Request), intent(inout) :: array_of_requests(count)
        integer, optional, intent(out) :: ierror
    end subroutine PMPIR_Startall_f08
end interface PMPI_Startall

interface PMPI_Test
    subroutine PMPIR_Test_f08(request, flag, status, ierror)
        use :: mpi_f08_types, only : MPI_Request, MPI_Status
        implicit none
        type(MPI_Request), intent(inout) :: request
        logical, intent(out) :: flag
        type(MPI_Status) :: status
        integer, optional, intent(out) :: ierror
    end subroutine PMPIR_Test_f08
end interface PMPI_Test

interface PMPI_Testall
    subroutine PMPIR_Testall_f08(count, array_of_requests, flag, array_of_statuses, ierror)
        use :: mpi_f08_types, only : MPI_Request, MPI_Status
        implicit none
        integer, intent(in) :: count
        type(MPI_Request), intent(inout) :: array_of_requests(count)
        logical, intent(out) :: flag
        type(MPI_Status) :: array_of_statuses(*)
        integer, optional, intent(out) :: ierror
    end subroutine PMPIR_Testall_f08
end interface PMPI_Testall

interface PMPI_Testany
    subroutine PMPIR_Testany_f08(count, array_of_requests, index, flag, status, ierror)
        use :: mpi_f08_types, only : MPI_Request, MPI_Status
        implicit none
        integer, intent(in) :: count
        type(MPI_Request), intent(inout) :: array_of_requests(count)
        integer, intent(out) :: index
        logical, intent(out) :: flag
        type(MPI_Status) :: status
        integer, optional, intent(out) :: ierror
    end subroutine PMPIR_Testany_f08
end interface PMPI_Testany

interface PMPI_Testsome
    subroutine PMPIR_Testsome_f08(incount, array_of_requests, outcount, &
                   array_of_indices, array_of_statuses, ierror)
        use :: mpi_f08_types, only : MPI_Request, MPI_Status
        implicit none
        integer, intent(in) :: incount
        type(MPI_Request), intent(inout) :: array_of_requests(incount)
        integer, intent(out) :: outcount, array_of_indices(*)
        type(MPI_Status) :: array_of_statuses(*)
        integer, optional, intent(out) :: ierror
    end subroutine PMPIR_Testsome_f08
end interface PMPI_Testsome

interface PMPI_Test_cancelled
    subroutine PMPIR_Test_cancelled_f08(status, flag, ierror)
        use :: mpi_f08_types, only : MPI_Status
        implicit none
        type(MPI_Status), intent(in) :: status
        logical, intent(out) :: flag
        integer, optional, intent(out) :: ierror
    end subroutine PMPIR_Test_cancelled_f08
end interface PMPI_Test_cancelled

interface PMPI_Wait
    subroutine PMPIR_Wait_f08(request, status, ierror)
        use :: mpi_f08_types, only : MPI_Request, MPI_Status
        implicit none
        type(MPI_Request), intent(inout) :: request
        type(MPI_Status) :: status
        integer, optional, intent(out) :: ierror
    end subroutine PMPIR_Wait_f08
end interface PMPI_Wait

interface PMPI_Waitall
    subroutine PMPIR_Waitall_f08(count, array_of_requests, array_of_statuses, ierror)
        use :: mpi_f08_types, only : MPI_Request, MPI_Status
        implicit none
        integer, intent(in) :: count
        type(MPI_Request), intent(inout) :: array_of_requests(count)
        type(MPI_Status) :: array_of_statuses(*)
        integer, optional, intent(out) :: ierror
    end subroutine PMPIR_Waitall_f08
end interface PMPI_Waitall

interface PMPI_Waitany
    subroutine PMPIR_Waitany_f08(count, array_of_requests, index, status, ierror)
        use :: mpi_f08_types, only : MPI_Request, MPI_Status
        implicit none
        integer, intent(in) :: count
        type(MPI_Request), intent(inout) :: array_of_requests(count)
        integer, intent(out) :: index
        type(MPI_Status) :: status
        integer, optional, intent(out) :: ierror
    end subroutine PMPIR_Waitany_f08
end interface PMPI_Waitany

interface PMPI_Waitsome
    subroutine PMPIR_Waitsome_f08(incount, array_of_requests, outcount, &
                   array_of_indices, array_of_statuses, ierror)
        use :: mpi_f08_types, only : MPI_Request, MPI_Status
        implicit none
        integer, intent(in) :: incount
        type(MPI_Request), intent(inout) :: array_of_requests(incount)
        integer, intent(out) :: outcount, array_of_indices(*)
        type(MPI_Status) :: array_of_statuses(*)
        integer, optional, intent(out) :: ierror
    end subroutine PMPIR_Waitsome_f08
end interface PMPI_Waitsome

interface PMPI_Get_address
    subroutine PMPIR_Get_address_f08ts(location, address, ierror)
        use :: mpi_f08_compile_constants, only : MPI_ADDRESS_KIND
        implicit none
        type(*), dimension(..), asynchronous :: location
        integer(MPI_ADDRESS_KIND), intent(out) :: address
        integer, optional, intent(out) :: ierror
    end subroutine PMPIR_Get_address_f08ts
end interface PMPI_Get_address

interface PMPI_Get_elements
    subroutine PMPIR_Get_elements_f08(status, datatype, count, ierror)
        use :: mpi_f08_types, only : MPI_Status, MPI_Datatype
        implicit none
        type(MPI_Status), intent(in) :: status
        type(MPI_Datatype), intent(in) :: datatype
        integer, intent(out) :: count
        integer, optional, intent(out) :: ierror
    end subroutine PMPIR_Get_elements_f08
end interface PMPI_Get_elements

interface PMPI_Get_elements_x
    subroutine PMPIR_Get_elements_x_f08(status, datatype, count, ierror)
        use :: mpi_f08_types, only : MPI_Status, MPI_Datatype
        use :: mpi_f08_compile_constants, only : MPI_COUNT_KIND
        implicit none
        type(MPI_Status), intent(in) :: status
        type(MPI_Datatype), intent(in) :: datatype
        integer(MPI_COUNT_KIND), intent(out) :: count
        integer, optional, intent(out) :: ierror
    end subroutine PMPIR_Get_elements_x_f08
end interface PMPI_Get_elements_x

interface PMPI_Pack
    subroutine PMPIR_Pack_f08ts(inbuf, incount, datatype, outbuf, outsize, position, comm, ierror)
        use :: mpi_f08_types, only : MPI_Datatype, MPI_Comm
        implicit none
        type(*), dimension(..), intent(in) :: inbuf
        type(*), dimension(..) :: outbuf
        integer, intent(in) :: incount, outsize
        type(MPI_Datatype), intent(in) :: datatype
        integer, intent(inout) :: position
        type(MPI_Comm), intent(in) :: comm
        integer, optional, intent(out) :: ierror
    end subroutine PMPIR_Pack_f08ts
end interface PMPI_Pack

interface PMPI_Pack_external
    subroutine PMPIR_Pack_external_f08ts(datarep, inbuf, incount, datatype, outbuf, outsize, &
                                      position, ierror)
        use :: mpi_f08_types, only : MPI_Datatype
        use :: mpi_f08_compile_constants, only : MPI_ADDRESS_KIND
        implicit none
        character(len=*), intent(in) :: datarep
        type(*), dimension(..), intent(in) :: inbuf
        type(*), dimension(..) :: outbuf
        integer, intent(in) :: incount
        type(MPI_Datatype), intent(in) :: datatype
        integer(MPI_ADDRESS_KIND), intent(in) :: outsize
        integer(MPI_ADDRESS_KIND), intent(inout) :: position
        integer, optional, intent(out) :: ierror
    end subroutine PMPIR_Pack_external_f08ts
end interface PMPI_Pack_external

interface PMPI_Pack_external_size
    subroutine PMPIR_Pack_external_size_f08(datarep, incount, datatype, size, ierror)
        use :: mpi_f08_types, only : MPI_Datatype
        use :: mpi_f08_compile_constants, only : MPI_ADDRESS_KIND
        implicit none
        type(MPI_Datatype), intent(in) :: datatype
        integer, intent(in) :: incount
        character(len=*), intent(in) :: datarep
        integer(MPI_ADDRESS_KIND), intent(out) :: size
        integer, optional, intent(out) :: ierror
    end subroutine PMPIR_Pack_external_size_f08
end interface PMPI_Pack_external_size

interface PMPI_Pack_size
    subroutine PMPIR_Pack_size_f08(incount, datatype, comm, size, ierror)
        use :: mpi_f08_types, only : MPI_Datatype, MPI_Comm
        implicit none
        integer, intent(in) :: incount
        type(MPI_Datatype), intent(in) :: datatype
        type(MPI_Comm), intent(in) :: comm
        integer, intent(out) :: size
        integer, optional, intent(out) :: ierror
    end subroutine PMPIR_Pack_size_f08
end interface PMPI_Pack_size

interface PMPI_Type_commit
    subroutine PMPIR_Type_commit_f08(datatype, ierror)
        use :: mpi_f08_types, only : MPI_Datatype
        implicit none
        type(MPI_Datatype), intent(inout) :: datatype
        integer, optional, intent(out) :: ierror
    end subroutine PMPIR_Type_commit_f08
end interface PMPI_Type_commit

interface PMPI_Type_contiguous
    subroutine PMPIR_Type_contiguous_f08(count, oldtype, newtype, ierror)
        use :: mpi_f08_types, only : MPI_Datatype
        implicit none
        integer, intent(in) :: count
        type(MPI_Datatype), intent(in) :: oldtype
        type(MPI_Datatype), intent(out) :: newtype
        integer, optional, intent(out) :: ierror
    end subroutine PMPIR_Type_contiguous_f08
end interface PMPI_Type_contiguous

interface PMPI_Type_create_darray
    subroutine PMPIR_Type_create_darray_f08(size, rank, ndims, array_of_gsizes, &
                   array_of_distribs, array_of_dargs, array_of_psizes, order, &
                   oldtype, newtype, ierror)
        use :: mpi_f08_types, only : MPI_Datatype
        implicit none
        integer, intent(in) :: size, rank, ndims, order
        integer, intent(in) :: array_of_gsizes(ndims), array_of_distribs(ndims)
        integer, intent(in) :: array_of_dargs(ndims), array_of_psizes(ndims)
        type(MPI_Datatype), intent(in) :: oldtype
        type(MPI_Datatype), intent(out) :: newtype
        integer, optional, intent(out) :: ierror
    end subroutine PMPIR_Type_create_darray_f08
end interface PMPI_Type_create_darray

interface PMPI_Type_create_hindexed
    subroutine PMPIR_Type_create_hindexed_f08(count, array_of_blocklengths, &
                   array_of_displacements, oldtype, newtype, ierror)
        use :: mpi_f08_types, only : MPI_Datatype
        use :: mpi_f08_compile_constants, only : MPI_ADDRESS_KIND
        implicit none
        integer, intent(in) :: count
        integer, intent(in) :: array_of_blocklengths(count)
        integer(MPI_ADDRESS_KIND), intent(in) :: array_of_displacements(count)
        type(MPI_Datatype), intent(in) :: oldtype
        type(MPI_Datatype), intent(out) :: newtype
        integer, optional, intent(out) :: ierror
    end subroutine PMPIR_Type_create_hindexed_f08
end interface PMPI_Type_create_hindexed

interface PMPI_Type_create_hvector
    subroutine PMPIR_Type_create_hvector_f08(count, blocklength, stride, oldtype, newtype, ierror)
        use :: mpi_f08_types, only : MPI_Datatype
        use :: mpi_f08_compile_constants, only : MPI_ADDRESS_KIND
        implicit none
        integer, intent(in) :: count, blocklength
        integer(MPI_ADDRESS_KIND), intent(in) :: stride
        type(MPI_Datatype), intent(in) :: oldtype
        type(MPI_Datatype), intent(out) :: newtype
        integer, optional, intent(out) :: ierror
    end subroutine PMPIR_Type_create_hvector_f08
end interface PMPI_Type_create_hvector

interface PMPI_Type_create_indexed_block
    subroutine PMPIR_Type_create_indexed_block_f08(count, blocklength, &
                   array_of_displacements, oldtype, newtype, ierror)
        use :: mpi_f08_types, only : MPI_Datatype
        implicit none
        integer, intent(in) :: count, blocklength
        integer, intent(in) :: array_of_displacements(count)
        type(MPI_Datatype), intent(in) :: oldtype
        type(MPI_Datatype), intent(out) :: newtype
        integer, optional, intent(out) :: ierror
    end subroutine PMPIR_Type_create_indexed_block_f08
end interface PMPI_Type_create_indexed_block

interface PMPI_Type_create_hindexed_block
    subroutine PMPIR_Type_create_hindexed_block_f08(count, blocklength, &
                                array_of_displacements, oldtype, newtype, ierror)
        use :: mpi_f08_types, only : MPI_Datatype
        use :: mpi_f08_compile_constants, only : MPI_ADDRESS_KIND
        implicit none
        integer, intent(in) :: count, blocklength
        integer(MPI_ADDRESS_KIND), intent(in) :: array_of_displacements(count)
        type(MPI_Datatype), intent(in) :: oldtype
        type(MPI_Datatype), intent(out) :: newtype
        integer, optional, intent(out) :: ierror
    end subroutine PMPIR_Type_create_hindexed_block_f08
end interface PMPI_Type_create_hindexed_block

interface PMPI_Type_create_resized
    subroutine PMPIR_Type_create_resized_f08(oldtype, lb, extent, newtype, ierror)
        use :: mpi_f08_types, only : MPI_Datatype
        use :: mpi_f08_compile_constants, only : MPI_ADDRESS_KIND
        implicit none
        integer(MPI_ADDRESS_KIND), intent(in) :: lb, extent
        type(MPI_Datatype), intent(in) :: oldtype
        type(MPI_Datatype), intent(out) :: newtype
        integer, optional, intent(out) :: ierror
    end subroutine PMPIR_Type_create_resized_f08
end interface PMPI_Type_create_resized

interface PMPI_Type_create_struct
    subroutine PMPIR_Type_create_struct_f08(count, array_of_blocklengths, &
                                array_of_displacements, array_of_types, newtype, ierror)
        use :: mpi_f08_types, only : MPI_Datatype
        use :: mpi_f08_compile_constants, only : MPI_ADDRESS_KIND
        implicit none
        integer, intent(in) :: count
        integer, intent(in) :: array_of_blocklengths(count)
        integer(MPI_ADDRESS_KIND), intent(in) :: array_of_displacements(count)
        type(MPI_Datatype), intent(in) :: array_of_types(count)
        type(MPI_Datatype), intent(out) :: newtype
        integer, optional, intent(out) :: ierror
    end subroutine PMPIR_Type_create_struct_f08
end interface PMPI_Type_create_struct

interface PMPI_Type_create_subarray
    subroutine PMPIR_Type_create_subarray_f08(ndims, array_of_sizes, array_of_subsizes, &
                         array_of_starts, order, oldtype, newtype, ierror)
        use :: mpi_f08_types, only : MPI_Datatype
        implicit none
        integer, intent(in) :: ndims, order
        integer, intent(in) :: array_of_sizes(ndims), array_of_subsizes(ndims)
        integer, intent(in) :: array_of_starts(ndims)
        type(MPI_Datatype), intent(in) :: oldtype
        type(MPI_Datatype), intent(out) :: newtype
        integer, optional, intent(out) :: ierror
    end subroutine PMPIR_Type_create_subarray_f08
end interface PMPI_Type_create_subarray

interface PMPI_Type_dup
    subroutine PMPIR_Type_dup_f08(oldtype, newtype, ierror)
        use :: mpi_f08_types, only : MPI_Datatype
        implicit none
        type(MPI_Datatype), intent(in) :: oldtype
        type(MPI_Datatype), intent(out) :: newtype
        integer, optional, intent(out) :: ierror
    end subroutine PMPIR_Type_dup_f08
end interface PMPI_Type_dup

interface PMPI_Type_free
    subroutine PMPIR_Type_free_f08(datatype, ierror)
        use :: mpi_f08_types, only : MPI_Datatype
        implicit none
        type(MPI_Datatype), intent(inout) :: datatype
        integer, optional, intent(out) :: ierror
    end subroutine PMPIR_Type_free_f08
end interface PMPI_Type_free

interface PMPI_Type_get_contents
    subroutine PMPIR_Type_get_contents_f08(datatype, max_integers, max_addresses, max_datatypes, &
                 array_of_integers, array_of_addresses, array_of_datatypes, ierror)
        use :: mpi_f08_types, only : MPI_Datatype
        use :: mpi_f08_compile_constants, only : MPI_ADDRESS_KIND
        implicit none
        type(MPI_Datatype), intent(in) :: datatype
        integer, intent(in) :: max_integers, max_addresses, max_datatypes
        integer, intent(out) :: array_of_integers(max_integers)
        integer(MPI_ADDRESS_KIND), intent(out) :: array_of_addresses(max_addresses)
        type(MPI_Datatype), intent(out) :: array_of_datatypes(max_datatypes)
        integer, optional, intent(out) :: ierror
    end subroutine PMPIR_Type_get_contents_f08
end interface PMPI_Type_get_contents

interface PMPI_Type_get_envelope
    subroutine PMPIR_Type_get_envelope_f08(datatype, num_integers, num_addresses, num_datatypes, &
                                          combiner, ierror)
        use :: mpi_f08_types, only : MPI_Datatype
        implicit none
        type(MPI_Datatype), intent(in) :: datatype
        integer, intent(out) :: num_integers, num_addresses, num_datatypes, combiner
        integer, optional, intent(out) :: ierror
    end subroutine PMPIR_Type_get_envelope_f08
end interface PMPI_Type_get_envelope

interface PMPI_Type_get_extent
    subroutine PMPIR_Type_get_extent_f08(datatype, lb, extent, ierror)
        use :: mpi_f08_types, only : MPI_Datatype
        use :: mpi_f08_compile_constants, only : MPI_ADDRESS_KIND
        implicit none
        type(MPI_Datatype), intent(in) :: datatype
        integer(MPI_ADDRESS_KIND), intent(out) :: lb, extent
        integer, optional, intent(out) :: ierror
    end subroutine PMPIR_Type_get_extent_f08
end interface PMPI_Type_get_extent

interface PMPI_Type_get_extent_x
    subroutine PMPIR_Type_get_extent_x_f08(datatype, lb, extent, ierror)
        use :: mpi_f08_types, only : MPI_Datatype
        use :: mpi_f08_compile_constants, only : MPI_COUNT_KIND
        implicit none
        type(MPI_Datatype), intent(in) :: datatype
        integer(MPI_COUNT_KIND), intent(out) :: lb, extent
        integer, optional, intent(out) :: ierror
    end subroutine PMPIR_Type_get_extent_x_f08
end interface PMPI_Type_get_extent_x

interface PMPI_Type_get_true_extent
    subroutine PMPIR_Type_get_true_extent_f08(datatype, true_lb, true_extent, ierror)
        use :: mpi_f08_types, only : MPI_Datatype
        use :: mpi_f08_compile_constants, only : MPI_ADDRESS_KIND
        implicit none
        type(MPI_Datatype), intent(in) :: datatype
        integer(MPI_ADDRESS_KIND), intent(out) :: true_lb, true_extent
        integer, optional, intent(out) :: ierror
    end subroutine PMPIR_Type_get_true_extent_f08
end interface PMPI_Type_get_true_extent

interface PMPI_Type_get_true_extent_x
    subroutine PMPIR_Type_get_true_extent_x_f08(datatype, true_lb, true_extent, ierror)
        use :: mpi_f08_types, only : MPI_Datatype
        use :: mpi_f08_compile_constants, only : MPI_ADDRESS_KIND
        use :: mpi_f08_compile_constants, only : MPI_COUNT_KIND
        implicit none
        type(MPI_Datatype), intent(in) :: datatype
        integer(MPI_COUNT_KIND), intent(out) :: true_lb, true_extent
        integer, optional, intent(out) :: ierror
    end subroutine PMPIR_Type_get_true_extent_x_f08
end interface PMPI_Type_get_true_extent_x

interface PMPI_Type_indexed
    subroutine PMPIR_Type_indexed_f08(count, array_of_blocklengths, &
                                     array_of_displacements, oldtype, newtype, ierror)
        use :: mpi_f08_types, only : MPI_Datatype
        implicit none
        integer, intent(in) :: count
        integer, intent(in) :: array_of_blocklengths(count), array_of_displacements(count)
        type(MPI_Datatype), intent(in) :: oldtype
        type(MPI_Datatype), intent(out) :: newtype
        integer, optional, intent(out) :: ierror
    end subroutine PMPIR_Type_indexed_f08
end interface PMPI_Type_indexed

interface PMPI_Type_size
    subroutine PMPIR_Type_size_f08(datatype, size, ierror)
        use :: mpi_f08_types, only : MPI_Datatype
        implicit none
        type(MPI_Datatype), intent(in) :: datatype
        integer, intent(out) :: size
        integer, optional, intent(out) :: ierror
    end subroutine PMPIR_Type_size_f08
end interface PMPI_Type_size

interface PMPI_Type_size_x
    subroutine PMPIR_Type_size_x_f08(datatype, size, ierror)
        use :: mpi_f08_types, only : MPI_Datatype
        use :: mpi_f08_compile_constants, only : MPI_COUNT_KIND
        implicit none
        type(MPI_Datatype), intent(in) :: datatype
        integer(MPI_COUNT_KIND), intent(out) :: size
        integer, optional, intent(out) :: ierror
    end subroutine PMPIR_Type_size_x_f08
end interface PMPI_Type_size_x

interface PMPI_Type_vector
    subroutine PMPIR_Type_vector_f08(count, blocklength, stride, oldtype, newtype, ierror)
        use :: mpi_f08_types, only : MPI_Datatype
        implicit none
        integer, intent(in) :: count, blocklength, stride
        type(MPI_Datatype), intent(in) :: oldtype
        type(MPI_Datatype), intent(out) :: newtype
        integer, optional, intent(out) :: ierror
    end subroutine PMPIR_Type_vector_f08
end interface PMPI_Type_vector

interface PMPI_Unpack
    subroutine PMPIR_Unpack_f08ts(inbuf, insize, position, outbuf, outcount, datatype, comm, &
                               ierror)
        use :: mpi_f08_types, only : MPI_Datatype, MPI_Comm
        implicit none
        type(*), dimension(..), intent(in) :: inbuf
        type(*), dimension(..) :: outbuf
        integer, intent(in) :: insize, outcount
        integer, intent(inout) :: position
        type(MPI_Datatype), intent(in) :: datatype
        type(MPI_Comm), intent(in) :: comm
        integer, optional, intent(out) :: ierror
    end subroutine PMPIR_Unpack_f08ts
end interface PMPI_Unpack

interface PMPI_Unpack_external
    subroutine PMPIR_Unpack_external_f08ts(datarep, inbuf, insize, position, outbuf, outcount, &
                                        datatype, ierror)
        use :: mpi_f08_types, only : MPI_Datatype
        use :: mpi_f08_compile_constants, only : MPI_ADDRESS_KIND
        implicit none
        character(len=*), intent(in) :: datarep
        type(*), dimension(..), intent(in) :: inbuf
        type(*), dimension(..) :: outbuf
        integer(MPI_ADDRESS_KIND), intent(in) :: insize
        integer(MPI_ADDRESS_KIND), intent(inout) :: position
        integer, intent(in) :: outcount
        type(MPI_Datatype), intent(in) :: datatype
        integer, optional, intent(out) :: ierror
    end subroutine PMPIR_Unpack_external_f08ts
end interface PMPI_Unpack_external

interface PMPI_Allgather
    subroutine PMPIR_Allgather_f08ts(sendbuf, sendcount, sendtype, recvbuf, recvcount, recvtype, &
                                  comm, ierror)
        use :: mpi_f08_types, only : MPI_Datatype, MPI_Comm
        implicit none
        type(*), dimension(..), intent(in) :: sendbuf
        type(*), dimension(..) :: recvbuf
        integer, intent(in) :: sendcount, recvcount
        type(MPI_Datatype), intent(in) :: sendtype, recvtype
        type(MPI_Comm), intent(in) :: comm
        integer, optional, intent(out) :: ierror
    end subroutine PMPIR_Allgather_f08ts
end interface PMPI_Allgather

interface PMPI_Iallgather
    subroutine PMPIR_Iallgather_f08ts(sendbuf, sendcount, sendtype, recvbuf, recvcount, recvtype, &
                                  comm, request, ierror)
        use :: mpi_f08_types, only : MPI_Datatype, MPI_Comm, MPI_Request
        implicit none
        type(*), dimension(..), intent(in), asynchronous :: sendbuf
        type(*), dimension(..), asynchronous :: recvbuf
        integer, intent(in) :: sendcount, recvcount
        type(MPI_Datatype), intent(in) :: sendtype, recvtype
        type(MPI_Comm), intent(in) :: comm
        type(MPI_Request), intent(out) :: request
        integer, optional, intent(out) :: ierror
    end subroutine PMPIR_Iallgather_f08ts
end interface PMPI_Iallgather

interface PMPI_Allgatherv
    subroutine PMPIR_Allgatherv_f08ts(sendbuf, sendcount, sendtype, recvbuf, recvcounts, displs, &
                                   recvtype, comm, ierror)
        use :: mpi_f08_types, only : MPI_Datatype, MPI_Comm
        implicit none
        type(*), dimension(..), intent(in) :: sendbuf
        type(*), dimension(..) :: recvbuf
        integer, intent(in) :: sendcount
        integer, intent(in) :: recvcounts(*), displs(*)
        type(MPI_Datatype), intent(in) :: sendtype, recvtype
        type(MPI_Comm), intent(in) :: comm
        integer, optional, intent(out) :: ierror
    end subroutine PMPIR_Allgatherv_f08ts
end interface PMPI_Allgatherv

interface PMPI_Iallgatherv
    subroutine PMPIR_Iallgatherv_f08ts(sendbuf, sendcount, sendtype, recvbuf, recvcounts, displs, &
                                   recvtype, comm, request, ierror)
        use :: mpi_f08_types, only : MPI_Datatype, MPI_Comm, MPI_Request
        implicit none
        type(*), dimension(..), intent(in), asynchronous :: sendbuf
        type(*), dimension(..), asynchronous :: recvbuf
        integer, intent(in) :: sendcount
        integer, intent(in) :: recvcounts(*), displs(*)
        type(MPI_Datatype), intent(in) :: sendtype, recvtype
        type(MPI_Comm), intent(in) :: comm
        type(MPI_Request), intent(out) :: request
        integer, optional, intent(out) :: ierror
    end subroutine PMPIR_Iallgatherv_f08ts
end interface PMPI_Iallgatherv

interface PMPI_Allreduce
    subroutine PMPIR_Allreduce_f08ts(sendbuf, recvbuf, count, datatype, op, comm, ierror)
        use :: mpi_f08_types, only : MPI_Datatype, MPI_Op, MPI_Comm
        implicit none
        type(*), dimension(..), intent(in) :: sendbuf
        type(*), dimension(..) :: recvbuf
        integer, intent(in) :: count
        type(MPI_Datatype), intent(in) :: datatype
        type(MPI_Op), intent(in) :: op
        type(MPI_Comm), intent(in) :: comm
        integer, optional, intent(out) :: ierror
    end subroutine PMPIR_Allreduce_f08ts
end interface PMPI_Allreduce

interface PMPI_Iallreduce
    subroutine PMPIR_Iallreduce_f08ts(sendbuf, recvbuf, count, datatype, op, comm, request, ierror)
        use :: mpi_f08_types, only : MPI_Datatype, MPI_Op, MPI_Comm, MPI_Request
        implicit none
        type(*), dimension(..), intent(in), asynchronous :: sendbuf
        type(*), dimension(..), asynchronous :: recvbuf
        integer, intent(in) :: count
        type(MPI_Datatype), intent(in) :: datatype
        type(MPI_Op), intent(in) :: op
        type(MPI_Comm), intent(in) :: comm
        type(MPI_Request), intent(out) :: request
        integer, optional, intent(out) :: ierror
    end subroutine PMPIR_Iallreduce_f08ts
end interface PMPI_Iallreduce

interface PMPI_Alltoall
    subroutine PMPIR_Alltoall_f08ts(sendbuf, sendcount, sendtype, recvbuf, recvcount, recvtype, &
                                 comm, ierror)
        use :: mpi_f08_types, only : MPI_Datatype, MPI_Comm
        implicit none
        type(*), dimension(..), intent(in) :: sendbuf
        type(*), dimension(..) :: recvbuf
        integer, intent(in) :: sendcount, recvcount
        type(MPI_Datatype), intent(in) :: sendtype, recvtype
        type(MPI_Comm), intent(in) :: comm
        integer, optional, intent(out) :: ierror
    end subroutine PMPIR_Alltoall_f08ts
end interface PMPI_Alltoall

interface PMPI_Ialltoall
    subroutine PMPIR_Ialltoall_f08ts(sendbuf, sendcount, sendtype, recvbuf, recvcount, recvtype, &
                                 comm, request, ierror)
        use :: mpi_f08_types, only : MPI_Datatype, MPI_Comm, MPI_Request
        implicit none
        type(*), dimension(..), intent(in), asynchronous :: sendbuf
        type(*), dimension(..), asynchronous :: recvbuf
        integer, intent(in) :: sendcount, recvcount
        type(MPI_Datatype), intent(in) :: sendtype, recvtype
        type(MPI_Comm), intent(in) :: comm
        type(MPI_Request), intent(out) :: request
        integer, optional, intent(out) :: ierror
    end subroutine PMPIR_Ialltoall_f08ts
end interface PMPI_Ialltoall

interface PMPI_Alltoallv
    subroutine PMPIR_Alltoallv_f08ts(sendbuf, sendcounts, sdispls, sendtype, recvbuf, recvcounts, &
                                  rdispls, recvtype, comm, ierror)
        use :: mpi_f08_types, only : MPI_Datatype, MPI_Comm
        implicit none
        type(*), dimension(..), intent(in) :: sendbuf
        type(*), dimension(..) :: recvbuf
        integer, intent(in) :: sendcounts(*), sdispls(*), recvcounts(*), rdispls(*)
        type(MPI_Datatype), intent(in) :: sendtype, recvtype
        type(MPI_Comm), intent(in) :: comm
        integer, optional, intent(out) :: ierror
    end subroutine PMPIR_Alltoallv_f08ts
end interface PMPI_Alltoallv

interface PMPI_Ialltoallv
    subroutine PMPIR_Ialltoallv_f08ts(sendbuf, sendcounts, sdispls, sendtype, recvbuf, recvcounts, &
                                  rdispls, recvtype, comm, request, ierror)
        use :: mpi_f08_types, only : MPI_Datatype, MPI_Comm, MPI_Request
        implicit none
        type(*), dimension(..), intent(in), asynchronous :: sendbuf
        type(*), dimension(..), asynchronous :: recvbuf
        integer, intent(in) :: sendcounts(*), sdispls(*), recvcounts(*), rdispls(*)
        type(MPI_Datatype), intent(in) :: sendtype, recvtype
        type(MPI_Comm), intent(in) :: comm
        type(MPI_Request), intent(out) :: request
        integer, optional, intent(out) :: ierror
    end subroutine PMPIR_Ialltoallv_f08ts
end interface PMPI_Ialltoallv

interface PMPI_Alltoallw
    subroutine PMPIR_Alltoallw_f08ts(sendbuf, sendcounts, sdispls, sendtypes, recvbuf, recvcounts, &
                                  rdispls, recvtypes, comm, ierror)
        use :: mpi_f08_types, only : MPI_Datatype, MPI_Comm
        implicit none
        type(*), dimension(..), intent(in) :: sendbuf
        type(*), dimension(..) :: recvbuf
        integer, intent(in) :: sendcounts(*), sdispls(*), recvcounts(*), rdispls(*)
        type(MPI_Datatype), intent(in) :: sendtypes(*), recvtypes(*)
        type(MPI_Comm), intent(in) :: comm
        integer, optional, intent(out) :: ierror
    end subroutine PMPIR_Alltoallw_f08ts
end interface PMPI_Alltoallw

interface PMPI_Ialltoallw
    subroutine PMPIR_Ialltoallw_f08ts(sendbuf, sendcounts, sdispls, sendtypes, recvbuf, recvcounts, &
                                  rdispls, recvtypes, comm, request, ierror)
        use :: mpi_f08_types, only : MPI_Datatype, MPI_Comm, MPI_Request
        implicit none
        type(*), dimension(..), intent(in), asynchronous :: sendbuf
        type(*), dimension(..), asynchronous :: recvbuf
        integer, intent(in) :: sendcounts(*), sdispls(*), recvcounts(*), rdispls(*)
        type(MPI_Datatype), intent(in) :: sendtypes(*), recvtypes(*)
        type(MPI_Comm), intent(in) :: comm
        type(MPI_Request), intent(out) :: request
        integer, optional, intent(out) :: ierror
    end subroutine PMPIR_Ialltoallw_f08ts
end interface PMPI_Ialltoallw

interface PMPI_Barrier
    subroutine PMPIR_Barrier_f08(comm, ierror)
        use :: mpi_f08_types, only : MPI_Comm
        implicit none
        type(MPI_Comm), intent(in) :: comm
        integer, optional, intent(out) :: ierror
    end subroutine PMPIR_Barrier_f08
end interface PMPI_Barrier

interface PMPI_Ibarrier
    subroutine PMPIR_Ibarrier_f08(comm, request, ierror)
        use :: mpi_f08_types, only : MPI_Comm, MPI_Request
        implicit none
        type(MPI_Comm), intent(in) :: comm
        type(MPI_Request), intent(out) :: request
        integer, optional, intent(out) :: ierror
    end subroutine PMPIR_Ibarrier_f08
end interface PMPI_Ibarrier

interface PMPI_Bcast
    subroutine PMPIR_Bcast_f08ts(buffer, count, datatype, root, comm, ierror)
        use :: mpi_f08_types, only : MPI_Datatype, MPI_Comm
        implicit none
        type(*), dimension(..) :: buffer
        integer, intent(in) :: count, root
        type(MPI_Datatype), intent(in) :: datatype
        type(MPI_Comm), intent(in) :: comm
        integer, optional, intent(out) :: ierror
    end subroutine PMPIR_Bcast_f08ts
end interface PMPI_Bcast

interface PMPI_Ibcast
    subroutine PMPIR_Ibcast_f08ts(buffer, count, datatype, root, comm, request, ierror)
        use :: mpi_f08_types, only : MPI_Datatype, MPI_Comm, MPI_Request
        implicit none
        type(*), dimension(..), asynchronous :: buffer
        integer, intent(in) :: count, root
        type(MPI_Datatype), intent(in) :: datatype
        type(MPI_Comm), intent(in) :: comm
        type(MPI_Request), intent(out) :: request
        integer, optional, intent(out) :: ierror
    end subroutine PMPIR_Ibcast_f08ts
end interface PMPI_Ibcast

interface PMPI_Exscan
    subroutine PMPIR_Exscan_f08ts(sendbuf, recvbuf, count, datatype, op, comm, ierror)
        use :: mpi_f08_types, only : MPI_Datatype, MPI_Op, MPI_Comm
        implicit none
        type(*), dimension(..), intent(in) :: sendbuf
        type(*), dimension(..) :: recvbuf
        integer, intent(in) :: count
        type(MPI_Datatype), intent(in) :: datatype
        type(MPI_Op), intent(in) :: op
        type(MPI_Comm), intent(in) :: comm
        integer, optional, intent(out) :: ierror
    end subroutine PMPIR_Exscan_f08ts
end interface PMPI_Exscan

interface PMPI_Iexscan
    subroutine PMPIR_Iexscan_f08ts(sendbuf, recvbuf, count, datatype, op, comm, request, ierror)
        use :: mpi_f08_types, only : MPI_Datatype, MPI_Op, MPI_Comm, MPI_Request
        implicit none
        type(*), dimension(..), intent(in), asynchronous :: sendbuf
        type(*), dimension(..), asynchronous :: recvbuf
        integer, intent(in) :: count
        type(MPI_Datatype), intent(in) :: datatype
        type(MPI_Op), intent(in) :: op
        type(MPI_Comm), intent(in) :: comm
        type(MPI_Request), intent(out) :: request
        integer, optional, intent(out) :: ierror
    end subroutine PMPIR_Iexscan_f08ts
end interface PMPI_Iexscan

interface PMPI_Gather
    subroutine PMPIR_Gather_f08ts(sendbuf, sendcount, sendtype, recvbuf, recvcount, recvtype, &
                               root, comm, ierror)
        use :: mpi_f08_types, only : MPI_Datatype, MPI_Comm
        implicit none
        type(*), dimension(..), intent(in) :: sendbuf
        type(*), dimension(..) :: recvbuf
        integer, intent(in) :: sendcount, recvcount, root
        type(MPI_Datatype), intent(in) :: sendtype, recvtype
        type(MPI_Comm), intent(in) :: comm
        integer, optional, intent(out) :: ierror
    end subroutine PMPIR_Gather_f08ts
end interface PMPI_Gather

interface PMPI_Igather
    subroutine PMPIR_Igather_f08ts(sendbuf, sendcount, sendtype, recvbuf, recvcount, recvtype, &
                               root, comm, request, ierror)
        use :: mpi_f08_types, only : MPI_Datatype, MPI_Comm, MPI_Request
        implicit none
        type(*), dimension(..), intent(in), asynchronous :: sendbuf
        type(*), dimension(..), asynchronous :: recvbuf
        integer, intent(in) :: sendcount, recvcount, root
        type(MPI_Datatype), intent(in) :: sendtype, recvtype
        type(MPI_Comm), intent(in) :: comm
        type(MPI_Request), intent(out) :: request
        integer, optional, intent(out) :: ierror
    end subroutine PMPIR_Igather_f08ts
end interface PMPI_Igather

interface PMPI_Gatherv
    subroutine PMPIR_Gatherv_f08ts(sendbuf, sendcount, sendtype, recvbuf, recvcounts, displs, &
                                recvtype, root, comm, ierror)
        use :: mpi_f08_types, only : MPI_Datatype, MPI_Comm
        implicit none
        type(*), dimension(..), intent(in) :: sendbuf
        type(*), dimension(..) :: recvbuf
        integer, intent(in) :: sendcount, root
        integer, intent(in) :: recvcounts(*), displs(*)
        type(MPI_Datatype), intent(in) :: sendtype, recvtype
        type(MPI_Comm), intent(in) :: comm
        integer, optional, intent(out) :: ierror
    end subroutine PMPIR_Gatherv_f08ts
end interface PMPI_Gatherv

interface PMPI_Igatherv
    subroutine PMPIR_Igatherv_f08ts(sendbuf, sendcount, sendtype, recvbuf, recvcounts, displs, &
                                recvtype, root, comm, request, ierror)
        use :: mpi_f08_types, only : MPI_Datatype, MPI_Comm, MPI_Request
        implicit none
        type(*), dimension(..), intent(in), asynchronous :: sendbuf
        type(*), dimension(..), asynchronous :: recvbuf
        integer, intent(in) :: sendcount, root
        integer, intent(in) :: recvcounts(*), displs(*)
        type(MPI_Datatype), intent(in) :: sendtype, recvtype
        type(MPI_Comm), intent(in) :: comm
        type(MPI_Request), intent(out) :: request
        integer, optional, intent(out) :: ierror
    end subroutine PMPIR_Igatherv_f08ts
end interface PMPI_Igatherv

interface PMPI_Op_commutative
    subroutine PMPIR_Op_commutative_f08(op, commute, ierror)
        use :: mpi_f08_types, only : MPI_Op
        implicit none
        type(MPI_Op), intent(in) :: op
        logical, intent(out) :: commute
        integer, optional, intent(out) :: ierror
    end subroutine PMPIR_Op_commutative_f08
end interface PMPI_Op_commutative

interface PMPI_Op_create
    subroutine PMPIR_Op_create_f08(user_fn, commute, op, ierror)
        use :: mpi_f08_types, only : MPI_Op
        use :: mpi_f08_callbacks, only : MPI_User_function
        implicit none
        procedure(MPI_User_function) :: user_fn
        logical, intent(in) :: commute
        type(MPI_Op), intent(out) :: op
        integer, optional, intent(out) :: ierror
    end subroutine PMPIR_Op_create_f08
end interface PMPI_Op_create

interface PMPI_Op_free
    subroutine PMPIR_Op_free_f08(op, ierror)
        use :: mpi_f08_types, only : MPI_Op
        implicit none
        type(MPI_Op), intent(inout) :: op
        integer, optional, intent(out) :: ierror
    end subroutine PMPIR_Op_free_f08
end interface PMPI_Op_free

interface PMPI_Reduce
    subroutine PMPIR_Reduce_f08ts(sendbuf, recvbuf, count, datatype, op, root, comm, ierror)
        use :: mpi_f08_types, only : MPI_Datatype, MPI_Op, MPI_Comm
        implicit none
        type(*), dimension(..), intent(in) :: sendbuf
        type(*), dimension(..) :: recvbuf
        integer, intent(in) :: count, root
        type(MPI_Datatype), intent(in) :: datatype
        type(MPI_Op), intent(in) :: op
        type(MPI_Comm), intent(in) :: comm
        integer, optional, intent(out) :: ierror
    end subroutine PMPIR_Reduce_f08ts
end interface PMPI_Reduce

interface PMPI_Ireduce
    subroutine PMPIR_Ireduce_f08ts(sendbuf, recvbuf, count, datatype, op, root, comm, request, ierror)
        use :: mpi_f08_types, only : MPI_Datatype, MPI_Op, MPI_Comm, MPI_Request
        implicit none
        type(*), dimension(..), intent(in), asynchronous :: sendbuf
        type(*), dimension(..), asynchronous :: recvbuf
        integer, intent(in) :: count, root
        type(MPI_Datatype), intent(in) :: datatype
        type(MPI_Op), intent(in) :: op
        type(MPI_Comm), intent(in) :: comm
        type(MPI_Request), intent(out) :: request
        integer, optional, intent(out) :: ierror
    end subroutine PMPIR_Ireduce_f08ts
end interface PMPI_Ireduce

interface PMPI_Reduce_local
    subroutine PMPIR_Reduce_local_f08ts(inbuf, inoutbuf, count, datatype, op, ierror)
        use :: mpi_f08_types, only : MPI_Datatype, MPI_Op
        implicit none
        type(*), dimension(..), intent(in) :: inbuf
        type(*), dimension(..) :: inoutbuf
        integer, intent(in) :: count
        type(MPI_Datatype), intent(in) :: datatype
        type(MPI_Op), intent(in) :: op
        integer, optional, intent(out) :: ierror
    end subroutine PMPIR_Reduce_local_f08ts
end interface PMPI_Reduce_local

interface PMPI_Reduce_scatter
    subroutine PMPIR_Reduce_scatter_f08ts(sendbuf, recvbuf, recvcounts, datatype, op, comm, &
                                       ierror)
        use :: mpi_f08_types, only : MPI_Datatype, MPI_Op, MPI_Comm
        implicit none
        type(*), dimension(..), intent(in) :: sendbuf
        type(*), dimension(..) :: recvbuf
        integer, intent(in) :: recvcounts(*)
        type(MPI_Datatype), intent(in) :: datatype
        type(MPI_Op), intent(in) :: op
        type(MPI_Comm), intent(in) :: comm
        integer, optional, intent(out) :: ierror
    end subroutine PMPIR_Reduce_scatter_f08ts
end interface PMPI_Reduce_scatter

interface PMPI_Ireduce_scatter
    subroutine PMPIR_Ireduce_scatter_f08ts(sendbuf, recvbuf, recvcounts, datatype, op, comm, &
                                       request, ierror)
        use :: mpi_f08_types, only : MPI_Datatype, MPI_Op, MPI_Comm, MPI_Request
        implicit none
        type(*), dimension(..), intent(in), asynchronous :: sendbuf
        type(*), dimension(..), asynchronous :: recvbuf
        integer, intent(in) :: recvcounts(*)
        type(MPI_Datatype), intent(in) :: datatype
        type(MPI_Op), intent(in) :: op
        type(MPI_Comm), intent(in) :: comm
        type(MPI_Request), intent(out) :: request
        integer, optional, intent(out) :: ierror
    end subroutine PMPIR_Ireduce_scatter_f08ts
end interface PMPI_Ireduce_scatter

interface PMPI_Reduce_scatter_block
    subroutine PMPIR_Reduce_scatter_block_f08ts(sendbuf, recvbuf, recvcount, datatype, op, comm, &
                                             ierror)
        use :: mpi_f08_types, only : MPI_Datatype, MPI_Op, MPI_Comm
        implicit none
        type(*), dimension(..), intent(in) :: sendbuf
        type(*), dimension(..) :: recvbuf
        integer, intent(in) :: recvcount
        type(MPI_Datatype), intent(in) :: datatype
        type(MPI_Op), intent(in) :: op
        type(MPI_Comm), intent(in) :: comm
        integer, optional, intent(out) :: ierror
    end subroutine PMPIR_Reduce_scatter_block_f08ts
end interface PMPI_Reduce_scatter_block

interface PMPI_Ireduce_scatter_block
    subroutine PMPIR_Ireduce_scatter_block_f08ts(sendbuf, recvbuf, recvcount, datatype, op, comm, &
                                             request, ierror)
        use :: mpi_f08_types, only : MPI_Datatype, MPI_Op, MPI_Comm, MPI_Request
        implicit none
        type(*), dimension(..), intent(in), asynchronous :: sendbuf
        type(*), dimension(..), asynchronous :: recvbuf
        integer, intent(in) :: recvcount
        type(MPI_Datatype), intent(in) :: datatype
        type(MPI_Op), intent(in) :: op
        type(MPI_Comm), intent(in) :: comm
        type(MPI_Request), intent(out) :: request
        integer, optional, intent(out) :: ierror
    end subroutine PMPIR_Ireduce_scatter_block_f08ts
end interface PMPI_Ireduce_scatter_block

interface PMPI_Scan
    subroutine PMPIR_Scan_f08ts(sendbuf, recvbuf, count, datatype, op, comm, ierror)
        use :: mpi_f08_types, only : MPI_Datatype, MPI_Op, MPI_Comm
        implicit none
        type(*), dimension(..), intent(in) :: sendbuf
        type(*), dimension(..) :: recvbuf
        integer, intent(in) :: count
        type(MPI_Datatype), intent(in) :: datatype
        type(MPI_Op), intent(in) :: op
        type(MPI_Comm), intent(in) :: comm
        integer, optional, intent(out) :: ierror
    end subroutine PMPIR_Scan_f08ts
end interface PMPI_Scan

interface PMPI_Iscan
    subroutine PMPIR_Iscan_f08ts(sendbuf, recvbuf, count, datatype, op, comm, request, ierror)
        use :: mpi_f08_types, only : MPI_Datatype, MPI_Op, MPI_Comm, MPI_Request
        implicit none
        type(*), dimension(..), intent(in), asynchronous :: sendbuf
        type(*), dimension(..), asynchronous :: recvbuf
        integer, intent(in) :: count
        type(MPI_Datatype), intent(in) :: datatype
        type(MPI_Op), intent(in) :: op
        type(MPI_Comm), intent(in) :: comm
        type(MPI_Request), intent(out) :: request
        integer, optional, intent(out) :: ierror
    end subroutine PMPIR_Iscan_f08ts
end interface PMPI_Iscan

interface PMPI_Scatter
    subroutine PMPIR_Scatter_f08ts(sendbuf, sendcount, sendtype, recvbuf, recvcount, recvtype, &
                                root, comm, ierror)
        use :: mpi_f08_types, only : MPI_Datatype, MPI_Comm
        implicit none
        type(*), dimension(..), intent(in) :: sendbuf
        type(*), dimension(..) :: recvbuf
        integer, intent(in) :: sendcount, recvcount, root
        type(MPI_Datatype), intent(in) :: sendtype, recvtype
        type(MPI_Comm), intent(in) :: comm
        integer, optional, intent(out) :: ierror
    end subroutine PMPIR_Scatter_f08ts
end interface PMPI_Scatter

interface PMPI_Iscatter
    subroutine PMPIR_Iscatter_f08ts(sendbuf, sendcount, sendtype, recvbuf, recvcount, recvtype, &
                                root, comm, request, ierror)
        use :: mpi_f08_types, only : MPI_Datatype, MPI_Comm, MPI_Request
        implicit none
        type(*), dimension(..), intent(in), asynchronous :: sendbuf
        type(*), dimension(..), asynchronous :: recvbuf
        integer, intent(in) :: sendcount, recvcount, root
        type(MPI_Datatype), intent(in) :: sendtype, recvtype
        type(MPI_Comm), intent(in) :: comm
        type(MPI_Request), intent(out) :: request
        integer, optional, intent(out) :: ierror
    end subroutine PMPIR_Iscatter_f08ts
end interface PMPI_Iscatter

interface PMPI_Scatterv
    subroutine PMPIR_Scatterv_f08ts(sendbuf, sendcounts, displs, sendtype, recvbuf, recvcount, &
                                 recvtype, root, comm, ierror)
        use :: mpi_f08_types, only : MPI_Datatype, MPI_Comm
        implicit none
        type(*), dimension(..), intent(in) :: sendbuf
        type(*), dimension(..) :: recvbuf
        integer, intent(in) :: recvcount, root
        integer, intent(in) :: sendcounts(*), displs(*)
        type(MPI_Datatype), intent(in) :: sendtype, recvtype
        type(MPI_Comm), intent(in) :: comm
        integer, optional, intent(out) :: ierror
    end subroutine PMPIR_Scatterv_f08ts
end interface PMPI_Scatterv

interface PMPI_Iscatterv
    subroutine PMPIR_Iscatterv_f08ts(sendbuf, sendcounts, displs, sendtype, recvbuf, recvcount, &
                                 recvtype, root, comm, request, ierror)
        use :: mpi_f08_types, only : MPI_Datatype, MPI_Comm, MPI_Request
        implicit none
        type(*), dimension(..), intent(in), asynchronous :: sendbuf
        type(*), dimension(..), asynchronous :: recvbuf
        integer, intent(in) :: recvcount, root
        integer, intent(in) :: sendcounts(*), displs(*)
        type(MPI_Datatype), intent(in) :: sendtype, recvtype
        type(MPI_Comm), intent(in) :: comm
        type(MPI_Request), intent(out) :: request
        integer, optional, intent(out) :: ierror
    end subroutine PMPIR_Iscatterv_f08ts
end interface PMPI_Iscatterv

interface PMPI_Comm_compare
    subroutine PMPIR_Comm_compare_f08(comm1,comm2,result, ierror)
        use :: mpi_f08_types, only : MPI_Comm
        implicit none
        type(MPI_Comm), intent(in) :: comm1
        type(MPI_Comm), intent(in) :: comm2
        integer, intent(out) :: result
        integer, optional, intent(out) :: ierror
    end subroutine PMPIR_Comm_compare_f08
end interface PMPI_Comm_compare

interface PMPI_Comm_create
    subroutine PMPIR_Comm_create_f08(comm, group, newcomm, ierror)
        use :: mpi_f08_types, only : MPI_Comm, MPI_Group
        implicit none
        type(MPI_Comm), intent(in) :: comm
        type(MPI_Group), intent(in) :: group
        type(MPI_Comm), intent(out) :: newcomm
        integer, optional, intent(out) :: ierror
    end subroutine PMPIR_Comm_create_f08
end interface PMPI_Comm_create

interface PMPI_Comm_create_group
    subroutine PMPIR_Comm_create_group_f08(comm, group, tag, newcomm, ierror)
        use :: mpi_f08_types, only : MPI_Comm, MPI_Group
        implicit none
        type(MPI_Comm), intent(in) :: comm
        type(MPI_Group), intent(in) :: group
        integer, intent(in) :: tag
        type(MPI_Comm), intent(out) :: newcomm
        integer, optional, intent(out) :: ierror
    end subroutine PMPIR_Comm_create_group_f08
end interface PMPI_Comm_create_group

interface PMPI_Comm_create_keyval
    subroutine PMPIR_Comm_create_keyval_f08(comm_copy_attr_fn, comm_delete_attr_fn, comm_keyval, &
                                           extra_state, ierror)
        use :: mpi_f08_compile_constants, only : MPI_ADDRESS_KIND
        use :: mpi_f08_callbacks, only : MPI_Comm_copy_attr_function
        use :: mpi_f08_callbacks, only : MPI_Comm_delete_attr_function
        implicit none
        procedure(MPI_Comm_copy_attr_function) :: comm_copy_attr_fn
        procedure(MPI_Comm_delete_attr_function) :: comm_delete_attr_fn
        integer, intent(out) :: comm_keyval
        integer(MPI_ADDRESS_KIND), intent(in) :: extra_state
        integer, optional, intent(out) :: ierror
    end subroutine PMPIR_Comm_create_keyval_f08
end interface PMPI_Comm_create_keyval

interface PMPI_Comm_delete_attr
    subroutine PMPIR_Comm_delete_attr_f08(comm, comm_keyval, ierror)
        use :: mpi_f08_types, only : MPI_Comm
        implicit none
        type(MPI_Comm), intent(in) :: comm
        integer, intent(in) :: comm_keyval
        integer, optional, intent(out) :: ierror
    end subroutine PMPIR_Comm_delete_attr_f08
end interface PMPI_Comm_delete_attr

interface PMPI_Comm_dup
    subroutine PMPIR_Comm_dup_f08(comm, newcomm, ierror)
        use :: mpi_f08_types, only : MPI_Comm
        implicit none
        type(MPI_Comm), intent(in) :: comm
        type(MPI_Comm), intent(out) :: newcomm
        integer, optional, intent(out) :: ierror
    end subroutine PMPIR_Comm_dup_f08
end interface PMPI_Comm_dup

interface PMPI_Comm_dup_with_info
    subroutine PMPIR_Comm_dup_with_info_f08(comm, info, newcomm, ierror)
        use :: mpi_f08_types, only : MPI_Comm, MPI_Info
        implicit none
        type(MPI_Comm), intent(in) :: comm
        type(MPI_Info), intent(in) :: info
        type(MPI_Comm), intent(out) :: newcomm
        integer, optional, intent(out) :: ierror
    end subroutine PMPIR_Comm_dup_with_info_f08
end interface PMPI_Comm_dup_with_info

interface PMPI_Comm_idup
    subroutine PMPIR_Comm_idup_f08(comm, newcomm, request, ierror)
        use :: mpi_f08_types, only : MPI_Comm, MPI_Request
        implicit none
        type(MPI_Comm), intent(in) :: comm
        type(MPI_Comm), intent(out), asynchronous :: newcomm
        type(MPI_Request), intent(out) :: request
        integer, optional, intent(out) :: ierror
    end subroutine PMPIR_Comm_idup_f08
end interface PMPI_Comm_idup

interface PMPI_Comm_free
    subroutine PMPIR_Comm_free_f08(comm, ierror)
        use :: mpi_f08_types, only : MPI_Comm
        implicit none
        type(MPI_Comm), intent(inout) :: comm
        integer, optional, intent(out) :: ierror
    end subroutine PMPIR_Comm_free_f08
end interface PMPI_Comm_free

interface PMPI_Comm_free_keyval
    subroutine PMPIR_Comm_free_keyval_f08(comm_keyval, ierror)
        implicit none
        integer, intent(inout) :: comm_keyval
        integer, optional, intent(out) :: ierror
    end subroutine PMPIR_Comm_free_keyval_f08
end interface PMPI_Comm_free_keyval

interface PMPI_Comm_get_attr
    subroutine PMPIR_Comm_get_attr_f08(comm, comm_keyval, attribute_val, flag, ierror)
        use :: mpi_f08_types, only : MPI_Comm
        use :: mpi_f08_compile_constants, only : MPI_ADDRESS_KIND
        implicit none
        type(MPI_Comm), intent(in) :: comm
        integer, intent(in) :: comm_keyval
        integer(MPI_ADDRESS_KIND), intent(out) :: attribute_val
        logical, intent(out) :: flag
        integer, optional, intent(out) :: ierror
    end subroutine PMPIR_Comm_get_attr_f08
end interface PMPI_Comm_get_attr

interface PMPI_Comm_get_info
    subroutine PMPIR_Comm_get_info_f08(comm, info_used, ierror)
        use :: mpi_f08_types, only : MPI_Comm, MPI_Info
        implicit none
        type(MPI_Comm), intent(in) :: comm
        type(MPI_Info), intent(out) :: info_used
        integer, optional, intent(out) :: ierror
    end subroutine PMPIR_Comm_get_info_f08
end interface PMPI_Comm_get_info

interface PMPI_Comm_get_name
    subroutine PMPIR_Comm_get_name_f08(comm, comm_name, resultlen, ierror)
        use :: mpi_f08_types, only : MPI_Comm
        use :: mpi_f08_compile_constants, only : MPI_MAX_OBJECT_NAME
        implicit none
        type(MPI_Comm), intent(in) :: comm
        character(len=MPI_MAX_OBJECT_NAME), intent(out) :: comm_name
        integer, intent(out) :: resultlen
        integer, optional, intent(out) :: ierror
    end subroutine PMPIR_Comm_get_name_f08
end interface PMPI_Comm_get_name

interface PMPI_Comm_group
    subroutine PMPIR_Comm_group_f08(comm, group, ierror)
        use :: mpi_f08_types, only : MPI_Comm, MPI_Group
        implicit none
        type(MPI_Comm), intent(in) :: comm
        type(MPI_Group), intent(out) :: group
        integer, optional, intent(out) :: ierror
    end subroutine PMPIR_Comm_group_f08
end interface PMPI_Comm_group

interface PMPI_Comm_rank
    subroutine PMPIR_Comm_rank_f08(comm, rank, ierror)
        use :: mpi_f08_types, only : MPI_Comm
        implicit none
        type(MPI_Comm), intent(in) :: comm
        integer, intent(out) :: rank
        integer, optional, intent(out) :: ierror
    end subroutine PMPIR_Comm_rank_f08
end interface PMPI_Comm_rank

interface PMPI_Comm_remote_group
    subroutine PMPIR_Comm_remote_group_f08(comm, group, ierror)
        use :: mpi_f08_types, only : MPI_Comm, MPI_Group
        implicit none
        type(MPI_Comm), intent(in) :: comm
        type(MPI_Group), intent(out) :: group
        integer, optional, intent(out) :: ierror
    end subroutine PMPIR_Comm_remote_group_f08
end interface PMPI_Comm_remote_group

interface PMPI_Comm_remote_size
    subroutine PMPIR_Comm_remote_size_f08(comm, size, ierror)
        use :: mpi_f08_types, only : MPI_Comm
        implicit none
        type(MPI_Comm), intent(in) :: comm
        integer, intent(out) :: size
        integer, optional, intent(out) :: ierror
    end subroutine PMPIR_Comm_remote_size_f08
end interface PMPI_Comm_remote_size

interface PMPI_Comm_set_attr
    subroutine PMPIR_Comm_set_attr_f08(comm, comm_keyval, attribute_val, ierror)
        use :: mpi_f08_types, only : MPI_Comm
        use :: mpi_f08_compile_constants, only : MPI_ADDRESS_KIND
        implicit none
        type(MPI_Comm), intent(in) :: comm
        integer, intent(in) :: comm_keyval
        integer(MPI_ADDRESS_KIND), intent(in) :: attribute_val
        integer, optional, intent(out) :: ierror
    end subroutine PMPIR_Comm_set_attr_f08
end interface PMPI_Comm_set_attr

interface PMPI_Comm_set_info
    subroutine PMPIR_Comm_set_info_f08(comm, info, ierror)
        use :: mpi_f08_types, only : MPI_Comm, MPI_Info
        implicit none
        type(MPI_Comm), intent(in) :: comm
        type(MPI_Info), intent(in) :: info
        integer, optional, intent(out) :: ierror
    end subroutine PMPIR_Comm_set_info_f08
end interface PMPI_Comm_set_info

interface PMPI_Comm_set_name
    subroutine PMPIR_Comm_set_name_f08(comm, comm_name, ierror)
        use :: mpi_f08_types, only : MPI_Comm
        implicit none
        type(MPI_Comm), intent(in) :: comm
        character(len=*), intent(in) :: comm_name
        integer, optional, intent(out) :: ierror
    end subroutine PMPIR_Comm_set_name_f08
end interface PMPI_Comm_set_name

interface PMPI_Comm_size
    subroutine PMPIR_Comm_size_f08(comm, size, ierror)
        use :: mpi_f08_types, only : MPI_Comm
        implicit none
        type(MPI_Comm), intent(in) :: comm
        integer, intent(out) :: size
        integer, optional, intent(out) :: ierror
    end subroutine PMPIR_Comm_size_f08
end interface PMPI_Comm_size

interface PMPI_Comm_split
    subroutine PMPIR_Comm_split_f08(comm, color, key, newcomm, ierror)
        use :: mpi_f08_types, only : MPI_Comm
        implicit none
        type(MPI_Comm), intent(in) :: comm
        integer, intent(in) :: color, key
        type(MPI_Comm), intent(out) :: newcomm
        integer, optional, intent(out) :: ierror
    end subroutine PMPIR_Comm_split_f08
end interface PMPI_Comm_split

interface PMPI_Comm_test_inter
    subroutine PMPIR_Comm_test_inter_f08(comm, flag, ierror)
        use :: mpi_f08_types, only : MPI_Comm
        implicit none
        type(MPI_Comm), intent(in) :: comm
        logical, intent(out) :: flag
        integer, optional, intent(out) :: ierror
    end subroutine PMPIR_Comm_test_inter_f08
end interface PMPI_Comm_test_inter

interface PMPI_Group_compare
    subroutine PMPIR_Group_compare_f08(group1,group2,result, ierror)
        use :: mpi_f08_types, only : MPI_Group
        implicit none
        type(MPI_Group), intent(in) :: group1, group2
        integer, intent(out) :: result
        integer, optional, intent(out) :: ierror
    end subroutine PMPIR_Group_compare_f08
end interface PMPI_Group_compare

interface PMPI_Group_difference
    subroutine PMPIR_Group_difference_f08(group1,group2,newgroup, ierror)
        use :: mpi_f08_types, only : MPI_Group
        implicit none
        type(MPI_Group), intent(in) :: group1, group2
        type(MPI_Group), intent(out) :: newgroup
        integer, optional, intent(out) :: ierror
    end subroutine PMPIR_Group_difference_f08
end interface PMPI_Group_difference

interface PMPI_Group_excl
    subroutine PMPIR_Group_excl_f08(group, n,ranks, newgroup, ierror)
        use :: mpi_f08_types, only : MPI_Group
        implicit none
        type(MPI_Group), intent(in) :: group
        integer, intent(in) :: n, ranks(n)
        type(MPI_Group), intent(out) :: newgroup
        integer, optional, intent(out) :: ierror
    end subroutine PMPIR_Group_excl_f08
end interface PMPI_Group_excl

interface PMPI_Group_free
    subroutine PMPIR_Group_free_f08(group, ierror)
        use :: mpi_f08_types, only : MPI_Group
        implicit none
        type(MPI_Group), intent(inout) :: group
        integer, optional, intent(out) :: ierror
    end subroutine PMPIR_Group_free_f08
end interface PMPI_Group_free

interface PMPI_Group_incl
    subroutine PMPIR_Group_incl_f08(group, n,ranks, newgroup, ierror)
        use :: mpi_f08_types, only : MPI_Group
        implicit none
        integer, intent(in) :: n, ranks(n)
        type(MPI_Group), intent(in) :: group
        type(MPI_Group), intent(out) :: newgroup
        integer, optional, intent(out) :: ierror
    end subroutine PMPIR_Group_incl_f08
end interface PMPI_Group_incl

interface PMPI_Group_intersection
    subroutine PMPIR_Group_intersection_f08(group1,group2,newgroup, ierror)
        use :: mpi_f08_types, only : MPI_Group
        implicit none
        type(MPI_Group), intent(in) :: group1, group2
        type(MPI_Group), intent(out) :: newgroup
        integer, optional, intent(out) :: ierror
    end subroutine PMPIR_Group_intersection_f08
end interface PMPI_Group_intersection

interface PMPI_Group_range_excl
    subroutine PMPIR_Group_range_excl_f08(group, n,ranges, newgroup, ierror)
        use :: mpi_f08_types, only : MPI_Group
        implicit none
        type(MPI_Group), intent(in) :: group
        integer, intent(in) :: n, ranges(3,n)
        type(MPI_Group), intent(out) :: newgroup
        integer, optional, intent(out) :: ierror
    end subroutine PMPIR_Group_range_excl_f08
end interface PMPI_Group_range_excl

interface PMPI_Group_range_incl
    subroutine PMPIR_Group_range_incl_f08(group, n,ranges, newgroup, ierror)
        use :: mpi_f08_types, only : MPI_Group
        implicit none
        type(MPI_Group), intent(in) :: group
        integer, intent(in) :: n, ranges(3,n)
        type(MPI_Group), intent(out) :: newgroup
        integer, optional, intent(out) :: ierror
    end subroutine PMPIR_Group_range_incl_f08
end interface PMPI_Group_range_incl

interface PMPI_Group_rank
    subroutine PMPIR_Group_rank_f08(group, rank, ierror)
        use :: mpi_f08_types, only : MPI_Group
        implicit none
        type(MPI_Group), intent(in) :: group
        integer, intent(out) :: rank
        integer, optional, intent(out) :: ierror
    end subroutine PMPIR_Group_rank_f08
end interface PMPI_Group_rank

interface PMPI_Group_size
    subroutine PMPIR_Group_size_f08(group, size, ierror)
        use :: mpi_f08_types, only : MPI_Group
        implicit none
        type(MPI_Group), intent(in) :: group
        integer, intent(out) :: size
        integer, optional, intent(out) :: ierror
    end subroutine PMPIR_Group_size_f08
end interface PMPI_Group_size

interface PMPI_Group_translate_ranks
    subroutine PMPIR_Group_translate_ranks_f08(group1,n, ranks1,group2,ranks2,ierror)
        use :: mpi_f08_types, only : MPI_Group
        implicit none
        type(MPI_Group), intent(in) :: group1, group2
        integer, intent(in) :: n
        integer, intent(in) :: ranks1(n)
        integer, intent(out) :: ranks2(n)
        integer, optional, intent(out) :: ierror
    end subroutine PMPIR_Group_translate_ranks_f08
end interface PMPI_Group_translate_ranks

interface PMPI_Group_union
    subroutine PMPIR_Group_union_f08(group1,group2,newgroup, ierror)
        use :: mpi_f08_types, only : MPI_Group
        implicit none
        type(MPI_Group), intent(in) :: group1, group2
        type(MPI_Group), intent(out) :: newgroup
        integer, optional, intent(out) :: ierror
    end subroutine PMPIR_Group_union_f08
end interface PMPI_Group_union

interface PMPI_Intercomm_create
    subroutine PMPIR_Intercomm_create_f08(local_comm, local_leader, peer_comm, remote_leader, &
                                         tag, newintercomm, ierror)
        use :: mpi_f08_types, only : MPI_Comm
        implicit none
        type(MPI_Comm), intent(in) :: local_comm, peer_comm
        integer, intent(in) :: local_leader, remote_leader, tag
        type(MPI_Comm), intent(out) :: newintercomm
        integer, optional, intent(out) :: ierror
    end subroutine PMPIR_Intercomm_create_f08
end interface PMPI_Intercomm_create

interface PMPI_Intercomm_merge
    subroutine PMPIR_Intercomm_merge_f08(intercomm, high, newintracomm, ierror)
        use :: mpi_f08_types, only : MPI_Comm
        implicit none
        type(MPI_Comm), intent(in) :: intercomm
        logical, intent(in) :: high
        type(MPI_Comm), intent(out) :: newintracomm
        integer, optional, intent(out) :: ierror
    end subroutine PMPIR_Intercomm_merge_f08
end interface PMPI_Intercomm_merge

interface PMPI_Type_create_keyval
    subroutine PMPIR_Type_create_keyval_f08(type_copy_attr_fn, type_delete_attr_fn, type_keyval, &
                                           extra_state, ierror)
        use :: mpi_f08_compile_constants, only : MPI_ADDRESS_KIND
        use :: mpi_f08_callbacks, only : MPI_Type_copy_attr_function
        use :: mpi_f08_callbacks, only : MPI_Type_delete_attr_function
        implicit none
        procedure(MPI_Type_copy_attr_function) :: type_copy_attr_fn
        procedure(MPI_Type_delete_attr_function) :: type_delete_attr_fn
        integer, intent(out) :: type_keyval
        integer(MPI_ADDRESS_KIND), intent(in) :: extra_state
        integer, optional, intent(out) :: ierror
    end subroutine PMPIR_Type_create_keyval_f08
end interface PMPI_Type_create_keyval

interface PMPI_Type_delete_attr
    subroutine PMPIR_Type_delete_attr_f08(datatype, type_keyval, ierror)
        use :: mpi_f08_types, only : MPI_Datatype
        implicit none
        type(MPI_Datatype), intent(in) :: datatype
        integer, intent(in) :: type_keyval
        integer, optional, intent(out) :: ierror
    end subroutine PMPIR_Type_delete_attr_f08
end interface PMPI_Type_delete_attr

interface PMPI_Type_free_keyval
    subroutine PMPIR_Type_free_keyval_f08(type_keyval, ierror)
        implicit none
        integer, intent(inout) :: type_keyval
        integer, optional, intent(out) :: ierror
    end subroutine PMPIR_Type_free_keyval_f08
end interface PMPI_Type_free_keyval

interface PMPI_Type_get_attr
    subroutine PMPIR_Type_get_attr_f08(datatype, type_keyval, attribute_val, flag, ierror)
        use :: mpi_f08_types, only : MPI_Datatype
        use :: mpi_f08_compile_constants, only : MPI_ADDRESS_KIND
        implicit none
        type(MPI_Datatype), intent(in) :: datatype
        integer, intent(in) :: type_keyval
        integer(MPI_ADDRESS_KIND), intent(out) :: attribute_val
        logical, intent(out) :: flag
        integer, optional, intent(out) :: ierror
    end subroutine PMPIR_Type_get_attr_f08
end interface PMPI_Type_get_attr

interface PMPI_Type_get_name
    subroutine PMPIR_Type_get_name_f08(datatype, type_name, resultlen, ierror)
        use :: mpi_f08_types, only : MPI_Datatype
        use :: mpi_f08_compile_constants, only : MPI_MAX_OBJECT_NAME
        implicit none
        type(MPI_Datatype), intent(in) :: datatype
        character(len=MPI_MAX_OBJECT_NAME), intent(out) :: type_name
        integer, intent(out) :: resultlen
        integer, optional, intent(out) :: ierror
    end subroutine PMPIR_Type_get_name_f08
end interface PMPI_Type_get_name

interface PMPI_Type_set_attr
    subroutine PMPIR_Type_set_attr_f08(datatype, type_keyval, attribute_val, ierror)
        use :: mpi_f08_types, only : MPI_Datatype
        use :: mpi_f08_compile_constants, only : MPI_ADDRESS_KIND
        implicit none
        type(MPI_Datatype), intent(in) :: datatype
        integer, intent(in) :: type_keyval
        integer(MPI_ADDRESS_KIND), intent(in) :: attribute_val
        integer, optional, intent(out) :: ierror
    end subroutine PMPIR_Type_set_attr_f08
end interface PMPI_Type_set_attr

interface PMPI_Type_set_name
    subroutine PMPIR_Type_set_name_f08(datatype, type_name, ierror)
        use :: mpi_f08_types, only : MPI_Datatype
        implicit none
        type(MPI_Datatype), intent(in) :: datatype
        character(len=*), intent(in) :: type_name
        integer, optional, intent(out) :: ierror
    end subroutine PMPIR_Type_set_name_f08
end interface PMPI_Type_set_name

interface PMPI_Win_create_keyval
    subroutine PMPIR_Win_create_keyval_f08(win_copy_attr_fn, win_delete_attr_fn, win_keyval, &
                                          extra_state, ierror)
        use :: mpi_f08_compile_constants, only : MPI_ADDRESS_KIND
        use :: mpi_f08_callbacks, only : MPI_Win_copy_attr_function
        use :: mpi_f08_callbacks, only : MPI_Win_delete_attr_function
        implicit none
        procedure(MPI_Win_copy_attr_function) :: win_copy_attr_fn
        procedure(MPI_Win_delete_attr_function) :: win_delete_attr_fn
        integer, intent(out) :: win_keyval
        integer(MPI_ADDRESS_KIND), intent(in) :: extra_state
        integer, optional, intent(out) :: ierror
    end subroutine PMPIR_Win_create_keyval_f08
end interface PMPI_Win_create_keyval

interface PMPI_Win_delete_attr
    subroutine PMPIR_Win_delete_attr_f08(win, win_keyval, ierror)
        use :: mpi_f08_types, only : MPI_Win
        implicit none
        type(MPI_Win), intent(in) :: win
        integer, intent(in) :: win_keyval
        integer, optional, intent(out) :: ierror
    end subroutine PMPIR_Win_delete_attr_f08
end interface PMPI_Win_delete_attr

interface PMPI_Win_free_keyval
    subroutine PMPIR_Win_free_keyval_f08(win_keyval, ierror)
        implicit none
        integer, intent(inout) :: win_keyval
        integer, optional, intent(out) :: ierror
    end subroutine PMPIR_Win_free_keyval_f08
end interface PMPI_Win_free_keyval

interface PMPI_Win_get_attr
    subroutine PMPIR_Win_get_attr_f08(win, win_keyval, attribute_val, flag, ierror)
        use :: mpi_f08_types, only : MPI_Win
        use :: mpi_f08_compile_constants, only : MPI_ADDRESS_KIND
        implicit none
        type(MPI_Win), intent(in) :: win
        integer, intent(in) :: win_keyval
        integer(MPI_ADDRESS_KIND), intent(out) :: attribute_val
        logical, intent(out) :: flag
        integer, optional, intent(out) :: ierror
    end subroutine PMPIR_Win_get_attr_f08
end interface PMPI_Win_get_attr

interface PMPI_Win_get_name
    subroutine PMPIR_Win_get_name_f08(win, win_name, resultlen, ierror)
        use :: mpi_f08_types, only : MPI_Win
        use :: mpi_f08_compile_constants, only : MPI_MAX_OBJECT_NAME
        implicit none
        type(MPI_Win), intent(in) :: win
        character(len=MPI_MAX_OBJECT_NAME), intent(out) :: win_name
        integer, intent(out) :: resultlen
        integer, optional, intent(out) :: ierror
    end subroutine PMPIR_Win_get_name_f08
end interface PMPI_Win_get_name

interface PMPI_Win_set_attr
    subroutine PMPIR_Win_set_attr_f08(win, win_keyval, attribute_val, ierror)
        use :: mpi_f08_types, only : MPI_Win
        use :: mpi_f08_compile_constants, only : MPI_ADDRESS_KIND
        implicit none
        type(MPI_Win), intent(in) :: win
        integer, intent(in) :: win_keyval
        integer(MPI_ADDRESS_KIND), intent(in) :: attribute_val
        integer, optional, intent(out) :: ierror
    end subroutine PMPIR_Win_set_attr_f08
end interface PMPI_Win_set_attr

interface PMPI_Win_set_name
    subroutine PMPIR_Win_set_name_f08(win, win_name, ierror)
        use :: mpi_f08_types, only : MPI_Win
        implicit none
        type(MPI_Win), intent(in) :: win
        character(len=*), intent(in) :: win_name
        integer, optional, intent(out) :: ierror
    end subroutine PMPIR_Win_set_name_f08
end interface PMPI_Win_set_name

interface PMPI_Cartdim_get
    subroutine PMPIR_Cartdim_get_f08(comm, ndims, ierror)
        use :: mpi_f08_types, only : MPI_Comm
        implicit none
        type(MPI_Comm), intent(in) :: comm
        integer, intent(out) :: ndims
        integer, optional, intent(out) :: ierror
    end subroutine PMPIR_Cartdim_get_f08
end interface PMPI_Cartdim_get

interface PMPI_Cart_coords
    subroutine PMPIR_Cart_coords_f08(comm, rank, maxdims, coords, ierror)
        use :: mpi_f08_types, only : MPI_Comm
        implicit none
        type(MPI_Comm), intent(in) :: comm
        integer, intent(in) :: rank, maxdims
        integer, intent(out) :: coords(maxdims)
        integer, optional, intent(out) :: ierror
    end subroutine PMPIR_Cart_coords_f08
end interface PMPI_Cart_coords

interface PMPI_Cart_create
    subroutine PMPIR_Cart_create_f08(comm_old, ndims, dims, periods, reorder, comm_cart, ierror)
        use :: mpi_f08_types, only : MPI_Comm
        implicit none
        type(MPI_Comm), intent(in) :: comm_old
        integer, intent(in) :: ndims, dims(ndims)
        logical, intent(in) :: periods(ndims), reorder
        type(MPI_Comm), intent(out) :: comm_cart
        integer, optional, intent(out) :: ierror
    end subroutine PMPIR_Cart_create_f08
end interface PMPI_Cart_create

interface PMPI_Cart_get
    subroutine PMPIR_Cart_get_f08(comm, maxdims, dims, periods, coords, ierror)
        use :: mpi_f08_types, only : MPI_Comm
        implicit none
        type(MPI_Comm), intent(in) :: comm
        integer, intent(in) :: maxdims
        integer, intent(out) :: dims(maxdims), coords(maxdims)
        logical, intent(out) :: periods(maxdims)
        integer, optional, intent(out) :: ierror
    end subroutine PMPIR_Cart_get_f08
end interface PMPI_Cart_get

interface PMPI_Cart_map
    subroutine PMPIR_Cart_map_f08(comm, ndims, dims, periods, newrank, ierror)
        use :: mpi_f08_types, only : MPI_Comm
        implicit none
        type(MPI_Comm), intent(in) :: comm
        integer, intent(in) :: ndims, dims(ndims)
        logical, intent(in) :: periods(ndims)
        integer, intent(out) :: newrank
        integer, optional, intent(out) :: ierror
    end subroutine PMPIR_Cart_map_f08
end interface PMPI_Cart_map

interface PMPI_Cart_rank
    subroutine PMPIR_Cart_rank_f08(comm, coords, rank, ierror)
        use :: mpi_f08_types, only : MPI_Comm
        implicit none
        type(MPI_Comm), intent(in) :: comm
        integer, intent(in) :: coords(*)
        integer, intent(out) :: rank
        integer, optional, intent(out) :: ierror
    end subroutine PMPIR_Cart_rank_f08
end interface PMPI_Cart_rank

interface PMPI_Cart_shift
    subroutine PMPIR_Cart_shift_f08(comm, direction, disp, rank_source, rank_dest, ierror)
        use :: mpi_f08_types, only : MPI_Comm
        implicit none
        type(MPI_Comm), intent(in) :: comm
        integer, intent(in) :: direction, disp
        integer, intent(out) :: rank_source, rank_dest
        integer, optional, intent(out) :: ierror
    end subroutine PMPIR_Cart_shift_f08
end interface PMPI_Cart_shift

interface PMPI_Cart_sub
    subroutine PMPIR_Cart_sub_f08(comm, remain_dims, newcomm, ierror)
        use :: mpi_f08_types, only : MPI_Comm
        implicit none
        type(MPI_Comm), intent(in) :: comm
        logical, intent(in) :: remain_dims(*)
        type(MPI_Comm), intent(out) :: newcomm
        integer, optional, intent(out) :: ierror
    end subroutine PMPIR_Cart_sub_f08
end interface PMPI_Cart_sub

interface PMPI_Dims_create
    subroutine PMPIR_Dims_create_f08(nnodes, ndims, dims, ierror)
        implicit none
        integer, intent(in) :: nnodes, ndims
        integer, intent(inout) :: dims(ndims)
        integer, optional, intent(out) :: ierror
    end subroutine PMPIR_Dims_create_f08
end interface PMPI_Dims_create

interface PMPI_Dist_graph_create
    subroutine PMPIR_Dist_graph_create_f08(comm_old, n,sources, degrees, destinations, weights, &
                                          info, reorder, comm_dist_graph, ierror)
        use :: mpi_f08_types, only : MPI_Comm, MPI_Info
        implicit none
        type(MPI_Comm), intent(in) :: comm_old
        integer, intent(in) :: n, sources(n), degrees(n), destinations(*), weights(*)
        type(MPI_Info), intent(in) :: info
        logical, intent(in) :: reorder
        type(MPI_Comm), intent(out) :: comm_dist_graph
        integer, optional, intent(out) :: ierror
    end subroutine PMPIR_Dist_graph_create_f08
end interface PMPI_Dist_graph_create

interface PMPI_Dist_graph_create_adjacent
    subroutine PMPIR_Dist_graph_create_adjacent_f08(comm_old, indegree, sources, sourceweights, &
                                                   outdegree, destinations, destweights, info, reorder, &
                                                   comm_dist_graph, ierror)
        use :: mpi_f08_types, only : MPI_Comm, MPI_Info
        implicit none
        type(MPI_Comm), intent(in) :: comm_old
        integer, intent(in) :: indegree
        integer, intent(in) :: sources(indegree)
        integer, intent(in) :: sourceweights(indegree)
        integer, intent(in) :: outdegree
        integer, intent(in) :: destinations(outdegree)
        integer, intent(in) :: destweights(outdegree)
        type(MPI_Info), intent(in) :: info
        logical, intent(in) :: reorder
        type(MPI_Comm), intent(out) :: comm_dist_graph
        integer, optional, intent(out) :: ierror
    end subroutine PMPIR_Dist_graph_create_adjacent_f08
end interface PMPI_Dist_graph_create_adjacent

interface PMPI_Dist_graph_neighbors
    subroutine PMPIR_Dist_graph_neighbors_f08(comm, maxindegree, sources, sourceweights, &
                                             maxoutdegree, destinations, destweights, ierror)
        use :: mpi_f08_types, only : MPI_Comm
        implicit none
        type(MPI_Comm), intent(in) :: comm
        integer, intent(in) :: maxindegree, maxoutdegree
        integer, intent(out) :: sources(maxindegree), destinations(maxoutdegree)
        integer, intent(out) :: sourceweights(maxindegree), destweights(maxoutdegree)
        integer, optional, intent(out) :: ierror
    end subroutine PMPIR_Dist_graph_neighbors_f08
end interface PMPI_Dist_graph_neighbors

interface PMPI_Dist_graph_neighbors_count
    subroutine PMPIR_Dist_graph_neighbors_count_f08(comm, indegree, outdegree, weighted, ierror)
        use :: mpi_f08_types, only : MPI_Comm
        implicit none
        type(MPI_Comm), intent(in) :: comm
        integer, intent(out) :: indegree, outdegree
        logical, intent(out) :: weighted
        integer, optional, intent(out) :: ierror
    end subroutine PMPIR_Dist_graph_neighbors_count_f08
end interface PMPI_Dist_graph_neighbors_count

interface PMPI_Graphdims_get
    subroutine PMPIR_Graphdims_get_f08(comm, nnodes, nedges, ierror)
        use :: mpi_f08_types, only : MPI_Comm
        implicit none
        type(MPI_Comm), intent(in) :: comm
        integer, intent(out) :: nnodes, nedges
        integer, optional, intent(out) :: ierror
    end subroutine PMPIR_Graphdims_get_f08
end interface PMPI_Graphdims_get

interface PMPI_Graph_create
    subroutine PMPIR_Graph_create_f08(comm_old, nnodes, index, edges, reorder, comm_graph, &
                                     ierror)
        use :: mpi_f08_types, only : MPI_Comm
        implicit none
        type(MPI_Comm), intent(in) :: comm_old
        integer, intent(in) :: nnodes, index(nnodes), edges(*)
        logical, intent(in) :: reorder
        type(MPI_Comm), intent(out) :: comm_graph
        integer, optional, intent(out) :: ierror
    end subroutine PMPIR_Graph_create_f08
end interface PMPI_Graph_create

interface PMPI_Graph_get
    subroutine PMPIR_Graph_get_f08(comm, maxindex, maxedges, index, edges, ierror)
        use :: mpi_f08_types, only : MPI_Comm
        implicit none
        type(MPI_Comm), intent(in) :: comm
        integer, intent(in) :: maxindex, maxedges
        integer, intent(out) :: index(maxindex), edges(maxedges)
        integer, optional, intent(out) :: ierror
    end subroutine PMPIR_Graph_get_f08
end interface PMPI_Graph_get

interface PMPI_Graph_map
    subroutine PMPIR_Graph_map_f08(comm, nnodes, index, edges, newrank, ierror)
        use :: mpi_f08_types, only : MPI_Comm
        implicit none
        type(MPI_Comm), intent(in) :: comm
        integer, intent(in) :: nnodes, index(nnodes), edges(*)
        integer, intent(out) :: newrank
        integer, optional, intent(out) :: ierror
    end subroutine PMPIR_Graph_map_f08
end interface PMPI_Graph_map

interface PMPI_Graph_neighbors
    subroutine PMPIR_Graph_neighbors_f08(comm, rank, maxneighbors, neighbors, ierror)
        use :: mpi_f08_types, only : MPI_Comm
        implicit none
        type(MPI_Comm), intent(in) :: comm
        integer, intent(in) :: rank, maxneighbors
        integer, intent(out) :: neighbors(maxneighbors)
        integer, optional, intent(out) :: ierror
    end subroutine PMPIR_Graph_neighbors_f08
end interface PMPI_Graph_neighbors

interface PMPI_Graph_neighbors_count
    subroutine PMPIR_Graph_neighbors_count_f08(comm, rank, nneighbors, ierror)
        use :: mpi_f08_types, only : MPI_Comm
        implicit none
        type(MPI_Comm), intent(in) :: comm
        integer, intent(in) :: rank
        integer, intent(out) :: nneighbors
        integer, optional, intent(out) :: ierror
    end subroutine PMPIR_Graph_neighbors_count_f08
end interface PMPI_Graph_neighbors_count

interface PMPI_Topo_test
    subroutine PMPIR_Topo_test_f08(comm, status, ierror)
        use :: mpi_f08_types, only : MPI_Comm, MPI_Status
        implicit none
        type(MPI_Comm), intent(in) :: comm
        integer, intent(out) :: status
        integer, optional, intent(out) :: ierror
    end subroutine PMPIR_Topo_test_f08
end interface PMPI_Topo_test

interface PMPI_Abort
    subroutine PMPIR_Abort_f08(comm, errorcode, ierror)
        use :: mpi_f08_types, only : MPI_Comm
        implicit none
        type(MPI_Comm), intent(in) :: comm
        integer, intent(in) :: errorcode
        integer, optional, intent(out) :: ierror
    end subroutine PMPIR_Abort_f08
end interface PMPI_Abort

interface PMPI_Add_error_class
    subroutine PMPIR_Add_error_class_f08(errorclass, ierror)
        implicit none
        integer, intent(out) :: errorclass
        integer, optional, intent(out) :: ierror
    end subroutine PMPIR_Add_error_class_f08
end interface PMPI_Add_error_class

interface PMPI_Add_error_code
    subroutine PMPIR_Add_error_code_f08(errorclass, errorcode, ierror)
        implicit none
        integer, intent(in) :: errorclass
        integer, intent(out) :: errorcode
        integer, optional, intent(out) :: ierror
    end subroutine PMPIR_Add_error_code_f08
end interface PMPI_Add_error_code

interface PMPI_Add_error_string
    subroutine PMPIR_Add_error_string_f08(errorcode, string, ierror)
        implicit none
        integer, intent(in) :: errorcode
        character(len=*), intent(in) :: string
        integer, optional, intent(out) :: ierror
    end subroutine PMPIR_Add_error_string_f08
end interface PMPI_Add_error_string

interface PMPI_Alloc_mem
    subroutine PMPIR_Alloc_mem_f08(size, info, baseptr, ierror)
        use, intrinsic :: iso_c_binding, only : c_ptr
        use :: mpi_f08_types, only : MPI_Info
        use :: mpi_f08_compile_constants, only : MPI_ADDRESS_KIND
        implicit none
        integer(MPI_ADDRESS_KIND), intent(in) :: size
        type(MPI_Info), intent(in) :: info
        type(c_ptr), intent(out) :: baseptr
        integer, optional, intent(out) :: ierror
    end subroutine PMPIR_Alloc_mem_f08
end interface PMPI_Alloc_mem

interface PMPI_Comm_call_errhandler
    subroutine PMPIR_Comm_call_errhandler_f08(comm, errorcode, ierror)
        use :: mpi_f08_types, only : MPI_Comm
        implicit none
        type(MPI_Comm), intent(in) :: comm
        integer, intent(in) :: errorcode
        integer, optional, intent(out) :: ierror
    end subroutine PMPIR_Comm_call_errhandler_f08
end interface PMPI_Comm_call_errhandler

interface PMPI_Comm_create_errhandler
    subroutine PMPIR_Comm_create_errhandler_f08(comm_errhandler_fn, errhandler, ierror)
        use :: mpi_f08_types, only : MPI_Errhandler
        use :: mpi_f08_callbacks, only : MPI_Comm_errhandler_function
        implicit none
        procedure(MPI_Comm_errhandler_function) :: comm_errhandler_fn
        type(MPI_Errhandler), intent(out) :: errhandler
        integer, optional, intent(out) :: ierror
    end subroutine PMPIR_Comm_create_errhandler_f08
end interface PMPI_Comm_create_errhandler

interface PMPI_Comm_get_errhandler
    subroutine PMPIR_Comm_get_errhandler_f08(comm, errhandler, ierror)
        use :: mpi_f08_types, only : MPI_Comm, MPI_Errhandler
        implicit none
        type(MPI_Comm), intent(in) :: comm
        type(MPI_Errhandler), intent(out) :: errhandler
        integer, optional, intent(out) :: ierror
    end subroutine PMPIR_Comm_get_errhandler_f08
end interface PMPI_Comm_get_errhandler

interface PMPI_Comm_set_errhandler
    subroutine PMPIR_Comm_set_errhandler_f08(comm, errhandler, ierror)
        use :: mpi_f08_types, only : MPI_Comm, MPI_Errhandler
        implicit none
        type(MPI_Comm), intent(in) :: comm
        type(MPI_Errhandler), intent(in) :: errhandler
        integer, optional, intent(out) :: ierror
    end subroutine PMPIR_Comm_set_errhandler_f08
end interface PMPI_Comm_set_errhandler

interface PMPI_Errhandler_free
    subroutine PMPIR_Errhandler_free_f08(errhandler, ierror)
        use :: mpi_f08_types, only : MPI_Errhandler
        implicit none
        type(MPI_Errhandler), intent(inout) :: errhandler
        integer, optional, intent(out) :: ierror
    end subroutine PMPIR_Errhandler_free_f08
end interface PMPI_Errhandler_free

interface PMPI_Error_class
    subroutine PMPIR_Error_class_f08(errorcode, errorclass, ierror)
        implicit none
        integer, intent(in) :: errorcode
        integer, intent(out) :: errorclass
        integer, optional, intent(out) :: ierror
    end subroutine PMPIR_Error_class_f08
end interface PMPI_Error_class

interface PMPI_Error_string
    subroutine PMPIR_Error_string_f08(errorcode, string, resultlen, ierror)
        use :: mpi_f08_compile_constants, only : MPI_MAX_ERROR_STRING
        implicit none
        integer, intent(in) :: errorcode
        character(len=MPI_MAX_ERROR_STRING), intent(out) :: string
        integer, intent(out) :: resultlen
        integer, optional, intent(out) :: ierror
    end subroutine PMPIR_Error_string_f08
end interface PMPI_Error_string

interface PMPI_File_call_errhandler
    subroutine PMPIR_File_call_errhandler_f08(fh, errorcode, ierror)
        use :: mpi_f08_types, only : MPI_File
        implicit none
        type(MPI_File), intent(in) :: fh
        integer, intent(in) :: errorcode
        integer, optional, intent(out) :: ierror
    end subroutine PMPIR_File_call_errhandler_f08
end interface PMPI_File_call_errhandler

interface PMPI_File_create_errhandler
    subroutine PMPIR_File_create_errhandler_f08(file_errhandler_fn, errhandler, ierror)
        use :: mpi_f08_types, only : MPI_Errhandler
        use :: mpi_f08_callbacks, only : MPI_File_errhandler_function
        implicit none
        procedure(MPI_File_errhandler_function) :: file_errhandler_fn
        type(MPI_Errhandler), intent(out) :: errhandler
        integer, optional, intent(out) :: ierror
    end subroutine PMPIR_File_create_errhandler_f08
end interface PMPI_File_create_errhandler

interface PMPI_File_get_errhandler
    subroutine PMPIR_File_get_errhandler_f08(file, errhandler, ierror)
        use :: mpi_f08_types, only : MPI_File, MPI_Errhandler
        implicit none
        type(MPI_File), intent(in) :: file
        type(MPI_Errhandler), intent(out) :: errhandler
        integer, optional, intent(out) :: ierror
    end subroutine PMPIR_File_get_errhandler_f08
end interface PMPI_File_get_errhandler

interface PMPI_File_set_errhandler
    subroutine PMPIR_File_set_errhandler_f08(file, errhandler, ierror)
        use :: mpi_f08_types, only : MPI_File, MPI_Errhandler
        implicit none
        type(MPI_File), intent(in) :: file
        type(MPI_Errhandler), intent(in) :: errhandler
        integer, optional, intent(out) :: ierror
    end subroutine PMPIR_File_set_errhandler_f08
end interface PMPI_File_set_errhandler

interface PMPI_Finalize
    subroutine PMPIR_Finalize_f08(ierror)
        implicit none
        integer, optional, intent(out) :: ierror
    end subroutine PMPIR_Finalize_f08
end interface PMPI_Finalize

interface PMPI_Finalized
    subroutine PMPIR_Finalized_f08(flag, ierror)
        implicit none
        logical, intent(out) :: flag
        integer, optional, intent(out) :: ierror
    end subroutine PMPIR_Finalized_f08
end interface PMPI_Finalized

interface PMPI_Free_mem
    subroutine PMPIR_Free_mem_f08(base, ierror)
        implicit none
        type(*), dimension(..), intent(in), asynchronous :: base
        integer, optional, intent(out) :: ierror
    end subroutine PMPIR_Free_mem_f08
end interface PMPI_Free_mem

interface PMPI_Get_processor_name
    subroutine PMPIR_Get_processor_name_f08(name, resultlen, ierror)
        use :: mpi_f08_compile_constants, only : MPI_MAX_PROCESSOR_NAME
        implicit none
        character(len=MPI_MAX_PROCESSOR_NAME), intent(out) :: name
        integer, intent(out) :: resultlen
        integer, optional, intent(out) :: ierror
    end subroutine PMPIR_Get_processor_name_f08
end interface PMPI_Get_processor_name

interface PMPI_Get_version
    subroutine PMPIR_Get_version_f08(version, subversion, ierror)
        implicit none
        integer, intent(out) :: version, subversion
        integer, optional, intent(out) :: ierror
    end subroutine PMPIR_Get_version_f08
end interface PMPI_Get_version

interface PMPI_Init
    subroutine PMPIR_Init_f08(ierror)
        implicit none
        integer, optional, intent(out) :: ierror
    end subroutine PMPIR_Init_f08
end interface PMPI_Init

interface PMPI_Initialized
    subroutine PMPIR_Initialized_f08(flag, ierror)
        implicit none
        logical, intent(out) :: flag
        integer, optional, intent(out) :: ierror
    end subroutine PMPIR_Initialized_f08
end interface PMPI_Initialized

interface PMPI_Win_call_errhandler
    subroutine PMPIR_Win_call_errhandler_f08(win, errorcode, ierror)
        use :: mpi_f08_types, only : MPI_Win
        implicit none
        type(MPI_Win), intent(in) :: win
        integer, intent(in) :: errorcode
        integer, optional, intent(out) :: ierror
    end subroutine PMPIR_Win_call_errhandler_f08
end interface PMPI_Win_call_errhandler

interface PMPI_Win_create_errhandler
    subroutine PMPIR_Win_create_errhandler_f08(win_errhandler_fn, errhandler, ierror)
        use :: mpi_f08_types, only : MPI_Errhandler
        use :: mpi_f08_callbacks, only : MPI_Win_errhandler_function
        implicit none
        procedure(MPI_Win_errhandler_function) :: win_errhandler_fn
        type(MPI_Errhandler), intent(out) :: errhandler
        integer, optional, intent(out) :: ierror
    end subroutine PMPIR_Win_create_errhandler_f08
end interface PMPI_Win_create_errhandler

interface PMPI_Win_get_errhandler
    subroutine PMPIR_Win_get_errhandler_f08(win, errhandler, ierror)
        use :: mpi_f08_types, only : MPI_Win, MPI_Errhandler
        implicit none
        type(MPI_Win), intent(in) :: win
        type(MPI_Errhandler), intent(out) :: errhandler
        integer, optional, intent(out) :: ierror
    end subroutine PMPIR_Win_get_errhandler_f08
end interface PMPI_Win_get_errhandler

interface PMPI_Win_set_errhandler
    subroutine PMPIR_Win_set_errhandler_f08(win, errhandler, ierror)
        use :: mpi_f08_types, only : MPI_Win, MPI_Errhandler
        implicit none
        type(MPI_Win), intent(in) :: win
        type(MPI_Errhandler), intent(in) :: errhandler
        integer, optional, intent(out) :: ierror
    end subroutine PMPIR_Win_set_errhandler_f08
end interface PMPI_Win_set_errhandler

interface PMPI_Info_create
    subroutine PMPIR_Info_create_f08(info, ierror)
        use :: mpi_f08_types, only : MPI_Info
        implicit none
        type(MPI_Info), intent(out) :: info
        integer, optional, intent(out) :: ierror
    end subroutine PMPIR_Info_create_f08
end interface PMPI_Info_create

interface PMPI_Info_delete
    subroutine PMPIR_Info_delete_f08(info, key, ierror)
        use :: mpi_f08_types, only : MPI_Info
        implicit none
        type(MPI_Info), intent(in) :: info
        character(len=*), intent(in) :: key
        integer, optional, intent(out) :: ierror
    end subroutine PMPIR_Info_delete_f08
end interface PMPI_Info_delete

interface PMPI_Info_dup
    subroutine PMPIR_Info_dup_f08(info, newinfo, ierror)
        use :: mpi_f08_types, only : MPI_Info
        implicit none
        type(MPI_Info), intent(in) :: info
        type(MPI_Info), intent(out) :: newinfo
        integer, optional, intent(out) :: ierror
    end subroutine PMPIR_Info_dup_f08
end interface PMPI_Info_dup

interface PMPI_Info_free
    subroutine PMPIR_Info_free_f08(info, ierror)
        use :: mpi_f08_types, only : MPI_Info
        implicit none
        type(MPI_Info), intent(inout) :: info
        integer, optional, intent(out) :: ierror
    end subroutine PMPIR_Info_free_f08
end interface PMPI_Info_free

interface PMPI_Info_get
    subroutine PMPIR_Info_get_f08(info, key, valuelen, value, flag, ierror)
        use :: mpi_f08_types, only : MPI_Info
        implicit none
        type(MPI_Info), intent(in) :: info
        character(len=*), intent(in) :: key
        integer, intent(in) :: valuelen
        character(len=valuelen), intent(out) :: value
        logical, intent(out) :: flag
        integer, optional, intent(out) :: ierror
    end subroutine PMPIR_Info_get_f08
end interface PMPI_Info_get

interface PMPI_Info_get_nkeys
    subroutine PMPIR_Info_get_nkeys_f08(info, nkeys, ierror)
        use :: mpi_f08_types, only : MPI_Info
        implicit none
        type(MPI_Info), intent(in) :: info
        integer, intent(out) :: nkeys
        integer, optional, intent(out) :: ierror
    end subroutine PMPIR_Info_get_nkeys_f08
end interface PMPI_Info_get_nkeys

interface PMPI_Info_get_nthkey
    subroutine PMPIR_Info_get_nthkey_f08(info, n,key, ierror)
        use :: mpi_f08_types, only : MPI_Info
        implicit none
        type(MPI_Info), intent(in) :: info
        integer, intent(in) :: n
        character(len=*), intent(out) :: key
        integer, optional, intent(out) :: ierror
    end subroutine PMPIR_Info_get_nthkey_f08
end interface PMPI_Info_get_nthkey

interface PMPI_Info_get_valuelen
    subroutine PMPIR_Info_get_valuelen_f08(info, key, valuelen, flag, ierror)
        use :: mpi_f08_types, only : MPI_Info
        implicit none
        type(MPI_Info), intent(in) :: info
        character(len=*), intent(in) :: key
        integer, intent(out) :: valuelen
        logical, intent(out) :: flag
        integer, optional, intent(out) :: ierror
    end subroutine PMPIR_Info_get_valuelen_f08
end interface PMPI_Info_get_valuelen

interface PMPI_Info_set
    subroutine PMPIR_Info_set_f08(info, key, value, ierror)
        use :: mpi_f08_types, only : MPI_Info
        implicit none
        type(MPI_Info), intent(in) :: info
        character(len=*), intent(in) :: key, value
        integer, optional, intent(out) :: ierror
    end subroutine PMPIR_Info_set_f08
end interface PMPI_Info_set

interface PMPI_Close_port
    subroutine PMPIR_Close_port_f08(port_name, ierror)
        implicit none
        character(len=*), intent(in) :: port_name
        integer, optional, intent(out) :: ierror
    end subroutine PMPIR_Close_port_f08
end interface PMPI_Close_port

interface PMPI_Comm_accept
    subroutine PMPIR_Comm_accept_f08(port_name, info, root, comm, newcomm, ierror)
        use :: mpi_f08_types, only : MPI_Info, MPI_Comm
        implicit none
        character(len=*), intent(in) :: port_name
        type(MPI_Info), intent(in) :: info
        integer, intent(in) :: root
        type(MPI_Comm), intent(in) :: comm
        type(MPI_Comm), intent(out) :: newcomm
        integer, optional, intent(out) :: ierror
    end subroutine PMPIR_Comm_accept_f08
end interface PMPI_Comm_accept

interface PMPI_Comm_connect
    subroutine PMPIR_Comm_connect_f08(port_name, info, root, comm, newcomm, ierror)
        use :: mpi_f08_types, only : MPI_Info, MPI_Comm
        implicit none
        character(len=*), intent(in) :: port_name
        type(MPI_Info), intent(in) :: info
        integer, intent(in) :: root
        type(MPI_Comm), intent(in) :: comm
        type(MPI_Comm), intent(out) :: newcomm
        integer, optional, intent(out) :: ierror
    end subroutine PMPIR_Comm_connect_f08
end interface PMPI_Comm_connect

interface PMPI_Comm_disconnect
    subroutine PMPIR_Comm_disconnect_f08(comm, ierror)
        use :: mpi_f08_types, only : MPI_Comm
        implicit none
        type(MPI_Comm), intent(inout) :: comm
        integer, optional, intent(out) :: ierror
    end subroutine PMPIR_Comm_disconnect_f08
end interface PMPI_Comm_disconnect

interface PMPI_Comm_get_parent
    subroutine PMPIR_Comm_get_parent_f08(parent, ierror)
        use :: mpi_f08_types, only : MPI_Comm
        implicit none
        type(MPI_Comm), intent(out) :: parent
        integer, optional, intent(out) :: ierror
    end subroutine PMPIR_Comm_get_parent_f08
end interface PMPI_Comm_get_parent

interface PMPI_Comm_join
    subroutine PMPIR_Comm_join_f08(fd, intercomm, ierror)
        use :: mpi_f08_types, only : MPI_Comm
        implicit none
        integer, intent(in) :: fd
        type(MPI_Comm), intent(out) :: intercomm
        integer, optional, intent(out) :: ierror
    end subroutine PMPIR_Comm_join_f08
end interface PMPI_Comm_join

interface PMPI_Comm_spawn
    subroutine PMPIR_Comm_spawn_f08(command, argv, maxprocs, info, root, comm, intercomm, &
                                   array_of_errcodes, ierror)
        use :: mpi_f08_types, only : MPI_Info, MPI_Comm
        implicit none
        character(len=*), intent(in) :: command, argv(*)
        integer, intent(in) :: maxprocs, root
        type(MPI_Info), intent(in) :: info
        type(MPI_Comm), intent(in) :: comm
        type(MPI_Comm), intent(out) :: intercomm
        integer :: array_of_errcodes(*)
        integer, optional, intent(out) :: ierror
    end subroutine PMPIR_Comm_spawn_f08
end interface PMPI_Comm_spawn

interface PMPI_Comm_spawn_multiple
    subroutine PMPIR_Comm_spawn_multiple_f08(count, array_of_commands, array_of_argv, array_of_maxprocs, &
                                    array_of_info, root, comm, intercomm, array_of_errcodes, ierror)
        use :: mpi_f08_types, only : MPI_Info, MPI_Comm
        implicit none
        integer, intent(in) :: count
        character(len=*), intent(in) :: array_of_commands(*), array_of_argv(count,*)
        integer, intent(in) :: array_of_maxprocs(*)
        type(MPI_Info), intent(in) :: array_of_info(*)
        integer, intent(in) :: root
        type(MPI_Comm), intent(in) :: comm
        type(MPI_Comm), intent(out) :: intercomm
        integer :: array_of_errcodes(*)
        integer, optional, intent(out) :: ierror
    end subroutine PMPIR_Comm_spawn_multiple_f08
end interface PMPI_Comm_spawn_multiple

interface PMPI_Lookup_name
    subroutine PMPIR_Lookup_name_f08(service_name, info, port_name, ierror)
        use :: mpi_f08_types, only : MPI_Info
        use :: mpi_f08_compile_constants, only : MPI_MAX_PORT_NAME
        implicit none
        character(len=*), intent(in) :: service_name
        type(MPI_Info), intent(in) :: info
        character(len=MPI_MAX_PORT_NAME), intent(out) :: port_name
        integer, optional, intent(out) :: ierror
    end subroutine PMPIR_Lookup_name_f08
end interface PMPI_Lookup_name

interface PMPI_Open_port
    subroutine PMPIR_Open_port_f08(info, port_name, ierror)
        use :: mpi_f08_types, only : MPI_Info
        use :: mpi_f08_compile_constants, only : MPI_MAX_PORT_NAME
        implicit none
        type(MPI_Info), intent(in) :: info
        character(len=MPI_MAX_PORT_NAME), intent(out) :: port_name
        integer, optional, intent(out) :: ierror
    end subroutine PMPIR_Open_port_f08
end interface PMPI_Open_port

interface PMPI_Publish_name
    subroutine PMPIR_Publish_name_f08(service_name, info, port_name, ierror)
        use :: mpi_f08_types, only : MPI_Info
        implicit none
        type(MPI_Info), intent(in) :: info
        character(len=*), intent(in) :: service_name, port_name
        integer, optional, intent(out) :: ierror
    end subroutine PMPIR_Publish_name_f08
end interface PMPI_Publish_name

interface PMPI_Unpublish_name
    subroutine PMPIR_Unpublish_name_f08(service_name, info, port_name, ierror)
        use :: mpi_f08_types, only : MPI_Info
        implicit none
        character(len=*), intent(in) :: service_name, port_name
        type(MPI_Info), intent(in) :: info
        integer, optional, intent(out) :: ierror
    end subroutine PMPIR_Unpublish_name_f08
end interface PMPI_Unpublish_name

interface PMPI_Accumulate
    subroutine PMPIR_Accumulate_f08ts(origin_addr, origin_count, origin_datatype, target_rank, &
                                   target_disp, target_count, target_datatype, op, win, ierror)
        use :: mpi_f08_types, only : MPI_Datatype, MPI_Op, MPI_Win
        use :: mpi_f08_compile_constants, only : MPI_ADDRESS_KIND
        implicit none
        type(*), dimension(..), intent(in), asynchronous :: origin_addr
        integer, intent(in) :: origin_count, target_rank, target_count
        type(MPI_Datatype), intent(in) :: origin_datatype
        integer(MPI_ADDRESS_KIND), intent(in) :: target_disp
        type(MPI_Datatype), intent(in) :: target_datatype
        type(MPI_Op), intent(in) :: op
        type(MPI_Win), intent(in) :: win
        integer, optional, intent(out) :: ierror
    end subroutine PMPIR_Accumulate_f08ts
end interface PMPI_Accumulate

interface PMPI_Compare_and_swap
    subroutine PMPIR_Compare_and_swap_f08ts(origin_addr, compare_addr, result_addr, datatype, &
            target_rank, target_disp, win, ierror)
        use :: mpi_f08_types, only : MPI_Datatype, MPI_Win
        use :: mpi_f08_compile_constants, only : MPI_ADDRESS_KIND
        implicit none
        type(*), dimension(..), intent(in), asynchronous :: origin_addr
        type(*), dimension(..), intent(in), asynchronous :: compare_addr
        type(*), dimension(..), asynchronous :: result_addr
        type(MPI_Datatype), intent(in) :: datatype
        integer, intent(in) :: target_rank
        integer(kind=MPI_ADDRESS_KIND), intent(in) :: target_disp
        type(MPI_Win), intent(in) :: win
        integer, optional, intent(out) :: ierror
    end subroutine PMPIR_Compare_and_swap_f08ts
end interface PMPI_Compare_and_swap

interface PMPI_Fetch_and_op
    subroutine PMPIR_Fetch_and_op_f08ts(origin_addr, result_addr, datatype, target_rank, &
            target_disp, op, win, ierror)
        use :: mpi_f08_types, only : MPI_Datatype, MPI_Op, MPI_Win
        use :: mpi_f08_compile_constants, only : MPI_ADDRESS_KIND
        implicit none
        type(*), dimension(..), intent(in), asynchronous :: origin_addr
        type(*), dimension(..), asynchronous :: result_addr
        type(MPI_Datatype), intent(in) :: datatype
        integer, intent(in) :: target_rank
        integer(kind=MPI_ADDRESS_KIND), intent(in) :: target_disp
        type(MPI_Op), intent(in) :: op
        type(MPI_Win), intent(in) :: win
        integer, optional, intent(out) :: ierror
    end subroutine PMPIR_Fetch_and_op_f08ts
end interface PMPI_Fetch_and_op

interface PMPI_Get
    subroutine PMPIR_Get_f08ts(origin_addr, origin_count, origin_datatype, target_rank, &
                                    target_disp, target_count, target_datatype, win, ierror)
        use :: mpi_f08_types, only : MPI_Datatype, MPI_Win
        use :: mpi_f08_compile_constants, only : MPI_ADDRESS_KIND
        implicit none
        type(*), dimension(..), asynchronous :: origin_addr
        integer, intent(in) :: origin_count, target_rank, target_count
        type(MPI_Datatype), intent(in) :: origin_datatype
        integer(MPI_ADDRESS_KIND), intent(in) :: target_disp
        type(MPI_Datatype), intent(in) :: target_datatype
        type(MPI_Win), intent(in) :: win
        integer, optional, intent(out) :: ierror
    end subroutine PMPIR_Get_f08ts
end interface PMPI_Get

interface PMPI_Get_accumulate
    subroutine PMPIR_Get_accumulate_f08ts(origin_addr, origin_count, origin_datatype, result_addr, &
            result_count, result_datatype, target_rank, target_disp, &
            target_count, target_datatype, op, win, ierror)
        use :: mpi_f08_types, only : MPI_Datatype, MPI_Op, MPI_Win
        use :: mpi_f08_compile_constants, only : MPI_ADDRESS_KIND
        implicit none
        type(*), dimension(..), intent(in), asynchronous :: origin_addr
        type(*), dimension(..), asynchronous :: result_addr
        integer, intent(in) :: origin_count, result_count, target_rank, target_count
        type(MPI_Datatype), intent(in) :: origin_datatype, target_datatype, result_datatype
        integer(kind=MPI_ADDRESS_KIND), intent(in) :: target_disp
        type(MPI_Op), intent(in) :: op
        type(MPI_Win), intent(in) :: win
        integer, optional, intent(out) :: ierror
    end subroutine PMPIR_Get_accumulate_f08ts
end interface PMPI_Get_accumulate

interface PMPI_Put
    subroutine PMPIR_Put_f08ts(origin_addr, origin_count, origin_datatype, target_rank, &
                             target_disp, target_count, target_datatype, win, ierror)
        use :: mpi_f08_types, only : MPI_Datatype, MPI_Win
        use :: mpi_f08_compile_constants, only : MPI_ADDRESS_KIND
        implicit none
        type(*), dimension(..), intent(in), asynchronous :: origin_addr
        integer, intent(in) :: origin_count, target_rank, target_count
        type(MPI_Datatype), intent(in) :: origin_datatype
        integer(MPI_ADDRESS_KIND), intent(in) :: target_disp
        type(MPI_Datatype), intent(in) :: target_datatype
        type(MPI_Win), intent(in) :: win
        integer, optional, intent(out) :: ierror
    end subroutine PMPIR_Put_f08ts
end interface PMPI_Put

interface PMPI_Raccumulate
    subroutine PMPIR_Raccumulate_f08ts(origin_addr, origin_count, origin_datatype, target_rank, &
            target_disp, target_count, target_datatype, op, win, request, ierror)
        use :: mpi_f08_types, only : MPI_Datatype, MPI_Op, MPI_Win, MPI_Request
        use :: mpi_f08_compile_constants, only : MPI_ADDRESS_KIND
        implicit none
        type(*), dimension(..), intent(in), asynchronous :: origin_addr
        integer, intent(in) :: origin_count, target_rank, target_count
        type(MPI_Datatype), intent(in) :: origin_datatype, target_datatype
        integer(kind=MPI_ADDRESS_KIND), intent(in) :: target_disp
        type(MPI_Op), intent(in) :: op
        type(MPI_Win), intent(in) :: win
        type(MPI_Request), intent(out) :: request
        integer, optional, intent(out) :: ierror
    end subroutine PMPIR_Raccumulate_f08ts
end interface PMPI_Raccumulate

interface PMPI_Rget
    subroutine PMPIR_Rget_f08ts(origin_addr, origin_count, origin_datatype, target_rank, &
            target_disp, target_count, target_datatype, win, request, ierror)
        use :: mpi_f08_types, only : MPI_Datatype, MPI_Win, MPI_Request
        use :: mpi_f08_compile_constants, only : MPI_ADDRESS_KIND
        implicit none
        type(*), dimension(..), asynchronous :: origin_addr
        integer, intent(in) :: origin_count, target_rank, target_count
        type(MPI_Datatype), intent(in) :: origin_datatype, target_datatype
        integer(kind=MPI_ADDRESS_KIND), intent(in) :: target_disp
        type(MPI_Win), intent(in) :: win
        type(MPI_Request), intent(out) :: request
        integer, optional, intent(out) :: ierror
    end subroutine PMPIR_Rget_f08ts
end interface PMPI_Rget

interface PMPI_Rget_accumulate
    subroutine PMPIR_Rget_accumulate_f08ts(origin_addr, origin_count, origin_datatype, &
            result_addr, result_count, result_datatype, target_rank, &
            target_disp, target_count, target_datatype, op, win, request, ierror)
        use :: mpi_f08_types, only : MPI_Datatype, MPI_Op, MPI_Win, MPI_Request
        use :: mpi_f08_compile_constants, only : MPI_ADDRESS_KIND
        implicit none
        type(*), dimension(..), intent(in), asynchronous :: origin_addr
        type(*), dimension(..), asynchronous :: result_addr
        integer, intent(in) :: origin_count, result_count, target_rank, target_count
        type(MPI_Datatype), intent(in) :: origin_datatype, target_datatype, result_datatype
        integer(kind=MPI_ADDRESS_KIND), intent(in) :: target_disp
        type(MPI_Op), intent(in) :: op
        type(MPI_Win), intent(in) :: win
        type(MPI_Request), intent(out) :: request
        integer, optional, intent(out) :: ierror
    end subroutine PMPIR_Rget_accumulate_f08ts
end interface PMPI_Rget_accumulate

interface PMPI_Rput
    subroutine PMPIR_Rput_f08ts(origin_addr, origin_count, origin_datatype, target_rank, &
            target_disp, target_count, target_datatype, win, request, ierror)
        use :: mpi_f08_types, only : MPI_Datatype, MPI_Win, MPI_Request
        use :: mpi_f08_compile_constants, only : MPI_ADDRESS_KIND
        implicit none
        type(*), dimension(..), intent(in), asynchronous :: origin_addr
        integer, intent(in) :: origin_count, target_rank, target_count
        type(MPI_Datatype), intent(in) :: origin_datatype, target_datatype
        integer(kind=MPI_ADDRESS_KIND), intent(in) :: target_disp
        type(MPI_Win), intent(in) :: win
        type(MPI_Request), intent(out) :: request
        integer, optional, intent(out) :: ierror
    end subroutine PMPIR_Rput_f08ts
end interface PMPI_Rput

interface PMPI_Win_allocate
    subroutine PMPIR_Win_allocate_f08(size, disp_unit, info, comm, baseptr, win, ierror)
        use, intrinsic :: iso_c_binding, only : c_ptr
        use :: mpi_f08_types, only : MPI_Info, MPI_Comm, MPI_Win
        use :: mpi_f08_compile_constants, only : MPI_ADDRESS_KIND
        implicit none
        integer(kind=MPI_ADDRESS_KIND), intent(in) :: size
        integer, intent(in) :: disp_unit
        type(MPI_Info), intent(in) :: info
        type(MPI_Comm), intent(in) :: comm
        type(c_ptr), intent(out) :: baseptr
        type(MPI_Win), intent(out) :: win
        integer, optional, intent(out) :: ierror
    end subroutine PMPIR_Win_allocate_f08
end interface PMPI_Win_allocate

interface PMPI_Win_allocate_shared
    subroutine PMPIR_Win_allocate_shared_f08(size, disp_unit, info, comm, baseptr, win, ierror)
        use, intrinsic :: iso_c_binding, only : c_ptr
        use :: mpi_f08_types, only : MPI_Info, MPI_Comm, MPI_Win
        use :: mpi_f08_compile_constants, only : MPI_ADDRESS_KIND
        implicit none
        integer(kind=MPI_ADDRESS_KIND), intent(in) :: size
        integer, intent(in) :: disp_unit
        type(MPI_Info), intent(in) :: info
        type(MPI_Comm), intent(in) :: comm
        type(c_ptr), intent(out) :: baseptr
        type(MPI_Win), intent(out) :: win
        integer, optional, intent(out) :: ierror
    end subroutine PMPIR_Win_allocate_shared_f08
end interface PMPI_Win_allocate_shared

interface PMPI_Win_attach
    subroutine PMPIR_Win_attach_f08ts(win, base, size, ierror)
        use :: mpi_f08_types, only : MPI_Win
        use :: mpi_f08_compile_constants, only : MPI_ADDRESS_KIND
        implicit none
        type(MPI_Win), intent(in) :: win
        type(*), dimension(..), asynchronous :: base
        integer(kind=MPI_ADDRESS_KIND), intent(in) :: size
        integer, optional, intent(out) :: ierror
    end subroutine PMPIR_Win_attach_f08ts
end interface PMPI_Win_attach


interface PMPI_Win_complete
    subroutine PMPIR_Win_complete_f08(win, ierror)
        use :: mpi_f08_types, only : MPI_Win
        implicit none
        type(MPI_Win), intent(in) :: win
        integer, optional, intent(out) :: ierror
    end subroutine PMPIR_Win_complete_f08
end interface PMPI_Win_complete

interface PMPI_Win_create
    subroutine PMPIR_Win_create_f08ts(base, size, disp_unit, info, comm, win, ierror)
        use :: mpi_f08_types, only : MPI_Info, MPI_Comm, MPI_Win
        use :: mpi_f08_compile_constants, only : MPI_ADDRESS_KIND
        implicit none
        type(*), dimension(..), asynchronous :: base
        integer(MPI_ADDRESS_KIND), intent(in) :: size
        integer, intent(in) :: disp_unit
        type(MPI_Info), intent(in) :: info
        type(MPI_Comm), intent(in) :: comm
        type(MPI_Win), intent(out) :: win
        integer, optional, intent(out) :: ierror
    end subroutine PMPIR_Win_create_f08ts
end interface PMPI_Win_create

interface PMPI_Win_create_dynamic
    subroutine PMPIR_Win_create_dynamic_f08(info, comm, win, ierror)
        use :: mpi_f08_types, only : MPI_Info, MPI_Comm, MPI_Win
        implicit none
        type(MPI_Info), intent(in) :: info
        type(MPI_Comm), intent(in) :: comm
        type(MPI_Win), intent(out) :: win
        integer, optional, intent(out) :: ierror
    end subroutine PMPIR_Win_create_dynamic_f08
end interface PMPI_Win_create_dynamic

interface PMPI_Win_detach
    subroutine PMPIR_Win_detach_f08ts(win, base, ierror)
        use :: mpi_f08_types, only : MPI_Win
        implicit none
        type(MPI_Win), intent(in) :: win
        type(*), dimension(..), asynchronous :: base
        integer, optional, intent(out) :: ierror
    end subroutine PMPIR_Win_detach_f08ts
end interface PMPI_Win_detach

interface PMPI_Win_fence
    subroutine PMPIR_Win_fence_f08(assert, win, ierror)
        use :: mpi_f08_types, only : MPI_Win
        implicit none
        integer, intent(in) :: assert
        type(MPI_Win), intent(in) :: win
        integer, optional, intent(out) :: ierror
    end subroutine PMPIR_Win_fence_f08
end interface PMPI_Win_fence

interface PMPI_Win_flush
    subroutine PMPIR_Win_flush_f08(rank, win, ierror)
        use :: mpi_f08_types, only : MPI_Win
        implicit none
        integer, intent(in) :: rank
        type(MPI_Win), intent(in) :: win
        integer, optional, intent(out) :: ierror
    end subroutine PMPIR_Win_flush_f08
end interface PMPI_Win_flush

interface PMPI_Win_flush_all
    subroutine PMPIR_Win_flush_all_f08(win, ierror)
        use :: mpi_f08_types, only : MPI_Win
        implicit none
        type(MPI_Win), intent(in) :: win
        integer, optional, intent(out) :: ierror
    end subroutine PMPIR_Win_flush_all_f08
end interface PMPI_Win_flush_all

interface PMPI_Win_flush_local
    subroutine PMPIR_Win_flush_local_f08(rank, win, ierror)
        use :: mpi_f08_types, only : MPI_Win
        implicit none
        integer, intent(in) :: rank
        type(MPI_Win), intent(in) :: win
        integer, optional, intent(out) :: ierror
    end subroutine PMPIR_Win_flush_local_f08
end interface PMPI_Win_flush_local

interface PMPI_Win_flush_local_all
    subroutine PMPIR_Win_flush_local_all_f08(win, ierror)
        use :: mpi_f08_types, only : MPI_Win
        implicit none
        type(MPI_Win), intent(in) :: win
        integer, optional, intent(out) :: ierror
    end subroutine PMPIR_Win_flush_local_all_f08
end interface PMPI_Win_flush_local_all

interface PMPI_Win_free
    subroutine PMPIR_Win_free_f08(win, ierror)
        use :: mpi_f08_types, only : MPI_Win
        implicit none
        type(MPI_Win), intent(inout) :: win
        integer, optional, intent(out) :: ierror
    end subroutine PMPIR_Win_free_f08
end interface PMPI_Win_free

interface PMPI_Win_get_group
    subroutine PMPIR_Win_get_group_f08(win, group, ierror)
        use :: mpi_f08_types, only : MPI_Win, MPI_Group
        implicit none
        type(MPI_Win), intent(in) :: win
        type(MPI_Group), intent(out) :: group
        integer, optional, intent(out) :: ierror
    end subroutine PMPIR_Win_get_group_f08
end interface PMPI_Win_get_group

interface PMPI_Win_get_info
    subroutine PMPIR_Win_get_info_f08(win, info_used, ierror)
        use :: mpi_f08_types, only : MPI_Win, MPI_Info
        implicit none
        type(MPI_Win), intent(in) :: win
        type(MPI_Info), intent(out) :: info_used
        integer, optional, intent(out) :: ierror
    end subroutine PMPIR_Win_get_info_f08
end interface PMPI_Win_get_info

interface PMPI_Win_lock
    subroutine PMPIR_Win_lock_f08(lock_type, rank, assert, win, ierror)
        use :: mpi_f08_types, only : MPI_Win
        implicit none
        integer, intent(in) :: lock_type, rank, assert
        type(MPI_Win), intent(in) :: win
        integer, optional, intent(out) :: ierror
    end subroutine PMPIR_Win_lock_f08
end interface PMPI_Win_lock

interface PMPI_Win_lock_all
    subroutine PMPIR_Win_lock_all_f08(assert, win, ierror)
        use :: mpi_f08_types, only : MPI_Win
        implicit none
        integer, intent(in) :: assert
        type(MPI_Win), intent(in) :: win
        integer, optional, intent(out) :: ierror
    end subroutine PMPIR_Win_lock_all_f08
end interface PMPI_Win_lock_all

interface PMPI_Win_post
    subroutine PMPIR_Win_post_f08(group, assert, win, ierror)
        use :: mpi_f08_types, only : MPI_Group, MPI_Win
        implicit none
        type(MPI_Group), intent(in) :: group
        integer, intent(in) :: assert
        type(MPI_Win), intent(in) :: win
        integer, optional, intent(out) :: ierror
    end subroutine PMPIR_Win_post_f08
end interface PMPI_Win_post

interface PMPI_Win_set_info
    subroutine PMPIR_Win_set_info_f08(win, info, ierror)
        use :: mpi_f08_types, only : MPI_Win, MPI_info
        implicit none
        type(MPI_Win), intent(in) :: win
        type(MPI_Info), intent(in) :: info
        integer, optional, intent(out) :: ierror
    end subroutine PMPIR_Win_set_info_f08
end interface PMPI_Win_set_info

interface PMPI_Win_shared_query
    subroutine PMPIR_Win_shared_query_f08(win, rank, size, disp_unit, baseptr, ierror)
        use, intrinsic :: iso_c_binding, only : c_ptr
        use :: mpi_f08_types, only : MPI_Win
        use :: mpi_f08_compile_constants, only : MPI_ADDRESS_KIND
        implicit none
        type(MPI_Win), intent(in) :: win
        integer, intent(in) :: rank
        integer(kind=MPI_ADDRESS_KIND), intent(out) :: size
        integer, intent(out) :: disp_unit
        type(c_ptr), intent(out) :: baseptr
        integer, optional, intent(out) :: ierror
    end subroutine PMPIR_Win_shared_query_f08
end interface PMPI_Win_shared_query

interface PMPI_Win_start
    subroutine PMPIR_Win_start_f08(group, assert, win, ierror)
        use :: mpi_f08_types, only : MPI_Group, MPI_Win
        implicit none
        type(MPI_Group), intent(in) :: group
        integer, intent(in) :: assert
        type(MPI_Win), intent(in) :: win
        integer, optional, intent(out) :: ierror
    end subroutine PMPIR_Win_start_f08
end interface PMPI_Win_start

interface PMPI_Win_sync
    subroutine PMPIR_Win_sync_f08(win, ierror)
        use :: mpi_f08_types, only : MPI_Win
        implicit none
        type(MPI_Win), intent(in) :: win
        integer, optional, intent(out) :: ierror
    end subroutine PMPIR_Win_sync_f08
end interface PMPI_Win_sync

interface PMPI_Win_test
    subroutine PMPIR_Win_test_f08(win, flag, ierror)
        use :: mpi_f08_types, only : MPI_Win
        implicit none
        logical, intent(out) :: flag
        type(MPI_Win), intent(in) :: win
        integer, optional, intent(out) :: ierror
    end subroutine PMPIR_Win_test_f08
end interface PMPI_Win_test

interface PMPI_Win_unlock
    subroutine PMPIR_Win_unlock_f08(rank, win, ierror)
        use :: mpi_f08_types, only : MPI_Win
        implicit none
        integer, intent(in) :: rank
        type(MPI_Win), intent(in) :: win
        integer, optional, intent(out) :: ierror
    end subroutine PMPIR_Win_unlock_f08
end interface PMPI_Win_unlock

interface PMPI_Win_unlock_all
    subroutine PMPIR_Win_unlock_all_f08(win, ierror)
        use :: mpi_f08_types, only : MPI_Win
        implicit none
        type(MPI_Win), intent(in) :: win
        integer, optional, intent(out) :: ierror
    end subroutine PMPIR_Win_unlock_all_f08
end interface PMPI_Win_unlock_all

interface PMPI_Win_wait
    subroutine PMPIR_Win_wait_f08(win, ierror)
        use :: mpi_f08_types, only : MPI_Win
        implicit none
        type(MPI_Win), intent(in) :: win
        integer, optional, intent(out) :: ierror
    end subroutine PMPIR_Win_wait_f08
end interface PMPI_Win_wait

interface PMPI_Grequest_complete
    subroutine PMPIR_Grequest_complete_f08(request, ierror)
        use :: mpi_f08_types, only : MPI_Request
        implicit none
        type(MPI_Request), intent(in) :: request
        integer, optional, intent(out) :: ierror
    end subroutine PMPIR_Grequest_complete_f08
end interface PMPI_Grequest_complete

interface PMPI_Grequest_start
    subroutine PMPIR_Grequest_start_f08(query_fn, free_fn, cancel_fn, extra_state, request, &
                                       ierror)
        use :: mpi_f08_types, only : MPI_Request
        use :: mpi_f08_compile_constants, only : MPI_ADDRESS_KIND
        use :: mpi_f08_callbacks, only : MPI_Grequest_query_function
        use :: mpi_f08_callbacks, only : MPI_Grequest_free_function
        use :: mpi_f08_callbacks, only : MPI_Grequest_cancel_function
        implicit none
        procedure(MPI_Grequest_query_function) :: query_fn
        procedure(MPI_Grequest_free_function) :: free_fn
        procedure(MPI_Grequest_cancel_function) :: cancel_fn
        integer(MPI_ADDRESS_KIND), intent(in) :: extra_state
        type(MPI_Request), intent(out) :: request
        integer, optional, intent(out) :: ierror
    end subroutine PMPIR_Grequest_start_f08
end interface PMPI_Grequest_start

interface PMPI_Init_thread
    subroutine PMPIR_Init_thread_f08(required, provided, ierror)
        implicit none
        integer, intent(in) :: required
        integer, intent(out) :: provided
        integer, optional, intent(out) :: ierror
    end subroutine PMPIR_Init_thread_f08
end interface PMPI_Init_thread

interface PMPI_Is_thread_main
    subroutine PMPIR_Is_thread_main_f08(flag, ierror)
        implicit none
        logical, intent(out) :: flag
        integer, optional, intent(out) :: ierror
    end subroutine PMPIR_Is_thread_main_f08
end interface PMPI_Is_thread_main

interface PMPI_Query_thread
    subroutine PMPIR_Query_thread_f08(provided, ierror)
        implicit none
        integer, intent(out) :: provided
        integer, optional, intent(out) :: ierror
    end subroutine PMPIR_Query_thread_f08
end interface PMPI_Query_thread

interface PMPI_Status_set_cancelled
    subroutine PMPIR_Status_set_cancelled_f08(status, flag, ierror)
        use :: mpi_f08_types, only : MPI_Status
        implicit none
        type(MPI_Status), intent(inout) :: status
        logical, intent(out) :: flag
        integer, optional, intent(out) :: ierror
    end subroutine PMPIR_Status_set_cancelled_f08
end interface PMPI_Status_set_cancelled

interface PMPI_Status_set_elements
    subroutine PMPIR_Status_set_elements_f08(status, datatype, count, ierror)
        use :: mpi_f08_types, only : MPI_Status, MPI_Datatype
        implicit none
        type(MPI_Status), intent(inout) :: status
        type(MPI_Datatype), intent(in) :: datatype
        integer, intent(in) :: count
        integer, optional, intent(out) :: ierror
    end subroutine PMPIR_Status_set_elements_f08
end interface PMPI_Status_set_elements

interface PMPI_Status_set_elements_x
    subroutine PMPIR_Status_set_elements_x_f08(status, datatype, count, ierror)
        use :: mpi_f08_types, only : MPI_Status, MPI_Datatype
        use :: mpi_f08_compile_constants, only : MPI_COUNT_KIND
        implicit none
        type(MPI_Status), intent(inout) :: status
        type(MPI_Datatype), intent(in) :: datatype
        integer(MPI_COUNT_KIND), intent(in) :: count
        integer, optional, intent(out) :: ierror
    end subroutine PMPIR_Status_set_elements_x_f08
end interface PMPI_Status_set_elements_x

interface PMPI_File_close
    subroutine PMPIR_File_close_f08(fh, ierror)
        use :: mpi_f08_types, only : MPI_File
        implicit none
        type(MPI_File), intent(inout) :: fh
        integer, optional, intent(out) :: ierror
    end subroutine PMPIR_File_close_f08
end interface PMPI_File_close

interface PMPI_File_delete
    subroutine PMPIR_File_delete_f08(filename, info, ierror)
        use :: mpi_f08_types, only : MPI_Info
        implicit none
        character(len=*), intent(in) :: filename
        type(MPI_Info), intent(in) :: info
        integer, optional, intent(out) :: ierror
    end subroutine PMPIR_File_delete_f08
end interface PMPI_File_delete

interface PMPI_File_get_amode
    subroutine PMPIR_File_get_amode_f08(fh, amode, ierror)
        use :: mpi_f08_types, only : MPI_File
        implicit none
        type(MPI_File), intent(in) :: fh
        integer, intent(out) :: amode
        integer, optional, intent(out) :: ierror
    end subroutine PMPIR_File_get_amode_f08
end interface PMPI_File_get_amode

interface PMPI_File_get_atomicity
    subroutine PMPIR_File_get_atomicity_f08(fh, flag, ierror)
        use :: mpi_f08_types, only : MPI_File
        implicit none
        type(MPI_File), intent(in) :: fh
        logical, intent(out) :: flag
        integer, optional, intent(out) :: ierror
    end subroutine PMPIR_File_get_atomicity_f08
end interface PMPI_File_get_atomicity

interface PMPI_File_get_byte_offset
    subroutine PMPIR_File_get_byte_offset_f08(fh, offset, disp, ierror)
        use :: mpi_f08_types, only : MPI_File
        use :: mpi_f08_compile_constants, only : MPI_OFFSET_KIND
        implicit none
        type(MPI_File), intent(in) :: fh
        integer(MPI_OFFSET_KIND), intent(in) :: offset
        integer(MPI_OFFSET_KIND), intent(out) :: disp
        integer, optional, intent(out) :: ierror
    end subroutine PMPIR_File_get_byte_offset_f08
end interface PMPI_File_get_byte_offset

interface PMPI_File_get_group
    subroutine PMPIR_File_get_group_f08(fh, group, ierror)
        use :: mpi_f08_types, only : MPI_File, MPI_Group
        implicit none
        type(MPI_File), intent(in) :: fh
        type(MPI_Group), intent(out) :: group
        integer, optional, intent(out) :: ierror
    end subroutine PMPIR_File_get_group_f08
end interface PMPI_File_get_group

interface PMPI_File_get_info
    subroutine PMPIR_File_get_info_f08(fh, info_used, ierror)
        use :: mpi_f08_types, only : MPI_File, MPI_Info
        implicit none
        type(MPI_File), intent(in) :: fh
        type(MPI_Info), intent(out) :: info_used
        integer, optional, intent(out) :: ierror
    end subroutine PMPIR_File_get_info_f08
end interface PMPI_File_get_info

interface PMPI_File_get_position
    subroutine PMPIR_File_get_position_f08(fh, offset, ierror)
        use :: mpi_f08_types, only : MPI_File
        use :: mpi_f08_compile_constants, only : MPI_OFFSET_KIND
        implicit none
        type(MPI_File), intent(in) :: fh
        integer(MPI_OFFSET_KIND), intent(out) :: offset
        integer, optional, intent(out) :: ierror
    end subroutine PMPIR_File_get_position_f08
end interface PMPI_File_get_position

interface PMPI_File_get_position_shared
    subroutine PMPIR_File_get_position_shared_f08(fh, offset, ierror)
        use :: mpi_f08_types, only : MPI_File
        use :: mpi_f08_compile_constants, only : MPI_OFFSET_KIND
        implicit none
        type(MPI_File), intent(in) :: fh
        integer(MPI_OFFSET_KIND), intent(out) :: offset
        integer, optional, intent(out) :: ierror
    end subroutine PMPIR_File_get_position_shared_f08
end interface PMPI_File_get_position_shared

interface PMPI_File_get_size
    subroutine PMPIR_File_get_size_f08(fh, size, ierror)
        use :: mpi_f08_types, only : MPI_File
        use :: mpi_f08_compile_constants, only : MPI_OFFSET_KIND
        implicit none
        type(MPI_File), intent(in) :: fh
        integer(MPI_OFFSET_KIND), intent(out) :: size
        integer, optional, intent(out) :: ierror
    end subroutine PMPIR_File_get_size_f08
end interface PMPI_File_get_size

interface PMPI_File_get_type_extent
    subroutine PMPIR_File_get_type_extent_f08(fh, datatype, extent, ierror)
        use :: mpi_f08_types, only : MPI_File, MPI_Datatype
        use :: mpi_f08_compile_constants, only : MPI_ADDRESS_KIND
        implicit none
        type(MPI_File), intent(in) :: fh
        type(MPI_Datatype), intent(in) :: datatype
        integer(MPI_ADDRESS_KIND), intent(out) :: extent
        integer, optional, intent(out) :: ierror
    end subroutine PMPIR_File_get_type_extent_f08
end interface PMPI_File_get_type_extent

interface PMPI_File_get_view
    subroutine PMPIR_File_get_view_f08(fh, disp, etype, filetype, datarep, ierror)
        use :: mpi_f08_types, only : MPI_File, MPI_Datatype
        use :: mpi_f08_compile_constants, only : MPI_OFFSET_KIND
        implicit none
        type(MPI_File), intent(in) :: fh
        integer(MPI_OFFSET_KIND), intent(out) :: disp
        type(MPI_Datatype), intent(out) :: etype
        type(MPI_Datatype), intent(out) :: filetype
        character(len=*), intent(out) :: datarep
        integer, optional, intent(out) :: ierror
    end subroutine PMPIR_File_get_view_f08
end interface PMPI_File_get_view

interface PMPI_File_iread
    subroutine PMPIR_File_iread_f08ts(fh, buf, count, datatype, request, ierror)
        use :: mpi_f08_types, only : MPI_File, MPI_Datatype, MPI_Request
        implicit none
        type(MPI_File), intent(in) :: fh
        type(*), dimension(..), asynchronous :: buf
        integer, intent(in) :: count
        type(MPI_Datatype), intent(in) :: datatype
        type(MPI_Request), intent(out) :: request
        integer, optional, intent(out) :: ierror
    end subroutine PMPIR_File_iread_f08ts
end interface PMPI_File_iread

interface PMPI_File_iread_at
    subroutine PMPIR_File_iread_at_f08ts(fh, offset, buf, count, datatype, request, ierror)
        use :: mpi_f08_types, only : MPI_File, MPI_Datatype, MPI_Request
        use :: mpi_f08_compile_constants, only : MPI_OFFSET_KIND
        implicit none
        type(MPI_File), intent(in) :: fh
        integer(MPI_OFFSET_KIND), intent(in) :: offset
        type(*), dimension(..), asynchronous :: buf
        integer, intent(in) :: count
        type(MPI_Datatype), intent(in) :: datatype
        type(MPI_Request), intent(out) :: request
        integer, optional, intent(out) :: ierror
    end subroutine PMPIR_File_iread_at_f08ts
end interface PMPI_File_iread_at

interface PMPI_File_iread_shared
    subroutine PMPIR_File_iread_shared_f08ts(fh, buf, count, datatype, request, ierror)
        use :: mpi_f08_types, only : MPI_File, MPI_Datatype, MPI_Request
        implicit none
        type(MPI_File), intent(in) :: fh
        type(*), dimension(..), asynchronous :: buf
        integer, intent(in) :: count
        type(MPI_Datatype), intent(in) :: datatype
        type(MPI_Request), intent(out) :: request
        integer, optional, intent(out) :: ierror
    end subroutine PMPIR_File_iread_shared_f08ts
end interface PMPI_File_iread_shared

interface PMPI_File_iwrite
    subroutine PMPIR_File_iwrite_f08ts(fh, buf, count, datatype, request, ierror)
        use :: mpi_f08_types, only : MPI_File, MPI_Datatype, MPI_Request
        implicit none
        type(MPI_File), intent(in) :: fh
        type(*), dimension(..), intent(in), asynchronous :: buf
        integer, intent(in) :: count
        type(MPI_Datatype), intent(in) :: datatype
        type(MPI_Request), intent(out) :: request
        integer, optional, intent(out) :: ierror
    end subroutine PMPIR_File_iwrite_f08ts
end interface PMPI_File_iwrite

interface PMPI_File_iwrite_at
    subroutine PMPIR_File_iwrite_at_f08ts(fh, offset, buf, count, datatype, request, ierror)
        use :: mpi_f08_types, only : MPI_File, MPI_Datatype, MPI_Request
        use :: mpi_f08_compile_constants, only : MPI_OFFSET_KIND
        implicit none
        type(MPI_File), intent(in) :: fh
        integer(MPI_OFFSET_KIND), intent(in) :: offset
        type(*), dimension(..), intent(in), asynchronous :: buf
        integer, intent(in) :: count
        type(MPI_Datatype), intent(in) :: datatype
        type(MPI_Request), intent(out) :: request
        integer, optional, intent(out) :: ierror
    end subroutine PMPIR_File_iwrite_at_f08ts
end interface PMPI_File_iwrite_at

interface PMPI_File_iwrite_shared
    subroutine PMPIR_File_iwrite_shared_f08ts(fh, buf, count, datatype, request, ierror)
        use :: mpi_f08_types, only : MPI_File, MPI_Datatype, MPI_Request
        implicit none
        type(*), dimension(..), intent(in), asynchronous :: buf
        type(MPI_File), intent(in) :: fh
        integer, intent(in) :: count
        type(MPI_Datatype), intent(in) :: datatype
        type(MPI_Request), intent(out) :: request
        integer, optional, intent(out) :: ierror
    end subroutine PMPIR_File_iwrite_shared_f08ts
end interface PMPI_File_iwrite_shared

interface PMPI_File_open
    subroutine PMPIR_File_open_f08(comm, filename, amode, info, fh, ierror)
        use :: mpi_f08_types, only : MPI_Comm, MPI_Info, MPI_File
        implicit none
        type(MPI_Comm), intent(in) :: comm
        character(len=*), intent(in) :: filename
        integer, intent(in) :: amode
        type(MPI_Info), intent(in) :: info
        type(MPI_File), intent(out) :: fh
        integer, optional, intent(out) :: ierror
    end subroutine PMPIR_File_open_f08
end interface PMPI_File_open

interface PMPI_File_preallocate
    subroutine PMPIR_File_preallocate_f08(fh, size, ierror)
        use :: mpi_f08_types, only : MPI_File
        use :: mpi_f08_compile_constants, only : MPI_OFFSET_KIND
        implicit none
        type(MPI_File), intent(in) :: fh
        integer(MPI_OFFSET_KIND), intent(in) :: size
        integer, optional, intent(out) :: ierror
    end subroutine PMPIR_File_preallocate_f08
end interface PMPI_File_preallocate

interface PMPI_File_read
    subroutine PMPIR_File_read_f08ts(fh, buf, count, datatype, status, ierror)
        use :: mpi_f08_types, only : MPI_File, MPI_Datatype, MPI_Status
        implicit none
        type(MPI_File), intent(in) :: fh
        type(*), dimension(..) :: buf
        integer, intent(in) :: count
        type(MPI_Datatype), intent(in) :: datatype
        type(MPI_Status) :: status
        integer, optional, intent(out) :: ierror
    end subroutine PMPIR_File_read_f08ts
end interface PMPI_File_read

interface PMPI_File_read_all
    subroutine PMPIR_File_read_all_f08ts(fh, buf, count, datatype, status, ierror)
        use :: mpi_f08_types, only : MPI_File, MPI_Datatype, MPI_Status
        implicit none
        type(MPI_File), intent(in) :: fh
        type(*), dimension(..) :: buf
        integer, intent(in) :: count
        type(MPI_Datatype), intent(in) :: datatype
        type(MPI_Status) :: status
        integer, optional, intent(out) :: ierror
    end subroutine PMPIR_File_read_all_f08ts
end interface PMPI_File_read_all

interface PMPI_File_read_all_begin
    subroutine PMPIR_File_read_all_begin_f08ts(fh, buf, count, datatype, ierror)
        use :: mpi_f08_types, only : MPI_File, MPI_Datatype
        implicit none
        type(MPI_File), intent(in) :: fh
        type(*), dimension(..) :: buf
        integer, intent(in) :: count
        type(MPI_Datatype), intent(in) :: datatype
        integer, optional, intent(out) :: ierror
    end subroutine PMPIR_File_read_all_begin_f08ts
end interface PMPI_File_read_all_begin

interface PMPI_File_read_all_end
    subroutine PMPIR_File_read_all_end_f08ts(fh, buf, status, ierror)
        use :: mpi_f08_types, only : MPI_File, MPI_Status
        implicit none
        type(MPI_File), intent(in) :: fh
        type(*), dimension(..) :: buf
        type(MPI_Status) :: status
        integer, optional, intent(out) :: ierror
    end subroutine PMPIR_File_read_all_end_f08ts
end interface PMPI_File_read_all_end

interface PMPI_File_read_at
    subroutine PMPIR_File_read_at_f08ts(fh, offset, buf, count, datatype, status, ierror)
        use :: mpi_f08_types, only : MPI_File, MPI_Datatype, MPI_Status
        use :: mpi_f08_compile_constants, only : MPI_OFFSET_KIND
        implicit none
        type(MPI_File), intent(in) :: fh
        integer(MPI_OFFSET_KIND), intent(in) :: offset
        type(*), dimension(..) :: buf
        integer, intent(in) :: count
        type(MPI_Datatype), intent(in) :: datatype
        type(MPI_Status) :: status
        integer, optional, intent(out) :: ierror
    end subroutine PMPIR_File_read_at_f08ts
end interface PMPI_File_read_at

interface PMPI_File_read_at_all
    subroutine PMPIR_File_read_at_all_f08ts(fh, offset, buf, count, datatype, status, ierror)
        use :: mpi_f08_types, only : MPI_File, MPI_Datatype, MPI_Status
        use :: mpi_f08_compile_constants, only : MPI_OFFSET_KIND
        implicit none
        type(MPI_File), intent(in) :: fh
        integer(MPI_OFFSET_KIND), intent(in) :: offset
        type(*), dimension(..) :: buf
        integer, intent(in) :: count
        type(MPI_Datatype), intent(in) :: datatype
        type(MPI_Status) :: status
        integer, optional, intent(out) :: ierror
    end subroutine PMPIR_File_read_at_all_f08ts
end interface PMPI_File_read_at_all

interface PMPI_File_read_at_all_begin
    subroutine PMPIR_File_read_at_all_begin_f08ts(fh, offset, buf, count, datatype, ierror)
        use :: mpi_f08_types, only : MPI_File, MPI_Datatype
        use :: mpi_f08_compile_constants, only : MPI_OFFSET_KIND
        implicit none
        type(MPI_File), intent(in) :: fh
        integer(MPI_OFFSET_KIND), intent(in) :: offset
        type(*), dimension(..) :: buf
        integer, intent(in) :: count
        type(MPI_Datatype), intent(in) :: datatype
        integer, optional, intent(out) :: ierror
    end subroutine PMPIR_File_read_at_all_begin_f08ts
end interface PMPI_File_read_at_all_begin

interface PMPI_File_read_at_all_end
    subroutine PMPIR_File_read_at_all_end_f08ts(fh, buf, status, ierror)
        use :: mpi_f08_types, only : MPI_File, MPI_Status
        implicit none
        type(MPI_File), intent(in) :: fh
        type(*), dimension(..) :: buf
        type(MPI_Status) :: status
        integer, optional, intent(out) :: ierror
    end subroutine PMPIR_File_read_at_all_end_f08ts
end interface PMPI_File_read_at_all_end

interface PMPI_File_read_ordered
    subroutine PMPIR_File_read_ordered_f08ts(fh, buf, count, datatype, status, ierror)
        use :: mpi_f08_types, only : MPI_File, MPI_Datatype, MPI_Status
        implicit none
        type(MPI_File), intent(in) :: fh
        type(*), dimension(..) :: buf
        integer, intent(in) :: count
        type(MPI_Datatype), intent(in) :: datatype
        type(MPI_Status) :: status
        integer, optional, intent(out) :: ierror
    end subroutine PMPIR_File_read_ordered_f08ts
end interface PMPI_File_read_ordered

interface PMPI_File_read_ordered_begin
    subroutine PMPIR_File_read_ordered_begin_f08ts(fh, buf, count, datatype, ierror)
        use :: mpi_f08_types, only : MPI_File, MPI_Datatype
        implicit none
        type(MPI_File), intent(in) :: fh
        type(*), dimension(..) :: buf
        integer, intent(in) :: count
        type(MPI_Datatype), intent(in) :: datatype
        integer, optional, intent(out) :: ierror
    end subroutine PMPIR_File_read_ordered_begin_f08ts
end interface PMPI_File_read_ordered_begin

interface PMPI_File_read_ordered_end
    subroutine PMPIR_File_read_ordered_end_f08ts(fh, buf, status, ierror)
        use :: mpi_f08_types, only : MPI_File, MPI_Status
        implicit none
        type(MPI_File), intent(in) :: fh
        type(*), dimension(..) :: buf
        type(MPI_Status) :: status
        integer, optional, intent(out) :: ierror
    end subroutine PMPIR_File_read_ordered_end_f08ts
end interface PMPI_File_read_ordered_end

interface PMPI_File_read_shared
    subroutine PMPIR_File_read_shared_f08ts(fh, buf, count, datatype, status, ierror)
        use :: mpi_f08_types, only : MPI_File, MPI_Datatype, MPI_Status
        implicit none
        type(MPI_File), intent(in) :: fh
        type(*), dimension(..) :: buf
        integer, intent(in) :: count
        type(MPI_Datatype), intent(in) :: datatype
        type(MPI_Status) :: status
        integer, optional, intent(out) :: ierror
    end subroutine PMPIR_File_read_shared_f08ts
end interface PMPI_File_read_shared

interface PMPI_File_seek
    subroutine PMPIR_File_seek_f08(fh, offset, whence, ierror)
        use :: mpi_f08_types, only : MPI_File
        use :: mpi_f08_compile_constants, only : MPI_OFFSET_KIND
        implicit none
        type(MPI_File), intent(in) :: fh
        integer(MPI_OFFSET_KIND), intent(in) :: offset
        integer, intent(in) :: whence
        integer, optional, intent(out) :: ierror
    end subroutine PMPIR_File_seek_f08
end interface PMPI_File_seek

interface PMPI_File_seek_shared
    subroutine PMPIR_File_seek_shared_f08(fh, offset, whence, ierror)
        use :: mpi_f08_types, only : MPI_File
        use :: mpi_f08_compile_constants, only : MPI_OFFSET_KIND
        implicit none
        type(MPI_File), intent(in) :: fh
        integer(MPI_OFFSET_KIND), intent(in) :: offset
        integer, intent(in) :: whence
        integer, optional, intent(out) :: ierror
    end subroutine PMPIR_File_seek_shared_f08
end interface PMPI_File_seek_shared

interface PMPI_File_set_atomicity
    subroutine PMPIR_File_set_atomicity_f08(fh, flag, ierror)
        use :: mpi_f08_types, only : MPI_File
        implicit none
        type(MPI_File), intent(in) :: fh
        logical, intent(in) :: flag
        integer, optional, intent(out) :: ierror
    end subroutine PMPIR_File_set_atomicity_f08
end interface PMPI_File_set_atomicity

interface PMPI_File_set_info
    subroutine PMPIR_File_set_info_f08(fh, info, ierror)
        use :: mpi_f08_types, only : MPI_File, MPI_Info
        implicit none
        type(MPI_File), intent(in) :: fh
        type(MPI_Info), intent(in) :: info
        integer, optional, intent(out) :: ierror
    end subroutine PMPIR_File_set_info_f08
end interface PMPI_File_set_info

interface PMPI_File_set_size
    subroutine PMPIR_File_set_size_f08(fh, size, ierror)
        use :: mpi_f08_types, only : MPI_File
        use :: mpi_f08_compile_constants, only : MPI_OFFSET_KIND
        implicit none
        type(MPI_File), intent(in) :: fh
        integer(MPI_OFFSET_KIND), intent(in) :: size
        integer, optional, intent(out) :: ierror
    end subroutine PMPIR_File_set_size_f08
end interface PMPI_File_set_size

interface PMPI_File_set_view
    subroutine PMPIR_File_set_view_f08(fh, disp, etype, filetype, datarep, info, ierror)
        use :: mpi_f08_types, only : MPI_File, MPI_Datatype, MPI_Info
        use :: mpi_f08_compile_constants, only : MPI_OFFSET_KIND
        implicit none
        type(MPI_File), intent(in) :: fh
        integer(MPI_OFFSET_KIND), intent(in) :: disp
        type(MPI_Datatype), intent(in) :: etype
        type(MPI_Datatype), intent(in) :: filetype
        character(len=*), intent(in) :: datarep
        type(MPI_Info), intent(in) :: info
        integer, optional, intent(out) :: ierror
    end subroutine PMPIR_File_set_view_f08
end interface PMPI_File_set_view

interface PMPI_File_sync
    subroutine PMPIR_File_sync_f08(fh, ierror)
        use :: mpi_f08_types, only : MPI_File
        implicit none
        type(MPI_File), intent(in) :: fh
        integer, optional, intent(out) :: ierror
    end subroutine PMPIR_File_sync_f08
end interface PMPI_File_sync

interface PMPI_File_write
    subroutine PMPIR_File_write_f08ts(fh, buf, count, datatype, status, ierror)
        use :: mpi_f08_types, only : MPI_File, MPI_Datatype, MPI_Status
        implicit none
        type(MPI_File), intent(in) :: fh
        type(*), dimension(..), intent(in) :: buf
        integer, intent(in) :: count
        type(MPI_Datatype), intent(in) :: datatype
        type(MPI_Status) :: status
        integer, optional, intent(out) :: ierror
    end subroutine PMPIR_File_write_f08ts
end interface PMPI_File_write

interface PMPI_File_write_all
    subroutine PMPIR_File_write_all_f08ts(fh, buf, count, datatype, status, ierror)
        use :: mpi_f08_types, only : MPI_File, MPI_Datatype, MPI_Status
        implicit none
        type(MPI_File), intent(in) :: fh
        type(*), dimension(..), intent(in) :: buf
        integer, intent(in) :: count
        type(MPI_Datatype), intent(in) :: datatype
        type(MPI_Status) :: status
        integer, optional, intent(out) :: ierror
    end subroutine PMPIR_File_write_all_f08ts
end interface PMPI_File_write_all

interface PMPI_File_write_all_begin
    subroutine PMPIR_File_write_all_begin_f08ts(fh, buf, count, datatype, ierror)
        use :: mpi_f08_types, only : MPI_File, MPI_Datatype
        implicit none
        type(MPI_File), intent(in) :: fh
        type(*), dimension(..), intent(in) :: buf
        integer, intent(in) :: count
        type(MPI_Datatype), intent(in) :: datatype
        integer, optional, intent(out) :: ierror
    end subroutine PMPIR_File_write_all_begin_f08ts
end interface PMPI_File_write_all_begin

interface PMPI_File_write_all_end
    subroutine PMPIR_File_write_all_end_f08ts(fh, buf, status, ierror)
        use :: mpi_f08_types, only : MPI_File, MPI_Status
        implicit none
        type(MPI_File), intent(in) :: fh
        type(*), dimension(..), intent(in) :: buf
        type(MPI_Status) :: status
        integer, optional, intent(out) :: ierror
    end subroutine PMPIR_File_write_all_end_f08ts
end interface PMPI_File_write_all_end

interface PMPI_File_write_at
    subroutine PMPIR_File_write_at_f08ts(fh, offset, buf, count, datatype, status, ierror)
        use :: mpi_f08_types, only : MPI_File, MPI_Datatype, MPI_Status
        use :: mpi_f08_compile_constants, only : MPI_OFFSET_KIND
        implicit none
        type(MPI_File), intent(in) :: fh
        integer(MPI_OFFSET_KIND), intent(in) :: offset
        type(*), dimension(..), intent(in) :: buf
        integer, intent(in) :: count
        type(MPI_Datatype), intent(in) :: datatype
        type(MPI_Status) :: status
        integer, optional, intent(out) :: ierror
    end subroutine PMPIR_File_write_at_f08ts
end interface PMPI_File_write_at

interface PMPI_File_write_at_all
    subroutine PMPIR_File_write_at_all_f08ts(fh, offset, buf, count, datatype, status, ierror)
        use :: mpi_f08_types, only : MPI_File, MPI_Datatype, MPI_Status
        use :: mpi_f08_compile_constants, only : MPI_OFFSET_KIND
        implicit none
        type(MPI_File), intent(in) :: fh
        integer(MPI_OFFSET_KIND), intent(in) :: offset
        type(*), dimension(..) :: buf
        integer, intent(in) :: count
        type(MPI_Datatype), intent(in) :: datatype
        type(MPI_Status) :: status
        integer, optional, intent(out) :: ierror
    end subroutine PMPIR_File_write_at_all_f08ts
end interface PMPI_File_write_at_all

interface PMPI_File_write_at_all_begin
    subroutine PMPIR_File_write_at_all_begin_f08ts(fh, offset, buf, count, datatype, ierror)
        use :: mpi_f08_types, only : MPI_File, MPI_Datatype
        use :: mpi_f08_compile_constants, only : MPI_OFFSET_KIND
        implicit none
        type(MPI_File), intent(in) :: fh
        integer(MPI_OFFSET_KIND), intent(in) :: offset
        type(*), dimension(..), intent(in) :: buf
        integer, intent(in) :: count
        type(MPI_Datatype), intent(in) :: datatype
        integer, optional, intent(out) :: ierror
    end subroutine PMPIR_File_write_at_all_begin_f08ts
end interface PMPI_File_write_at_all_begin

interface PMPI_File_write_at_all_end
    subroutine PMPIR_File_write_at_all_end_f08ts(fh, buf, status, ierror)
        use :: mpi_f08_types, only : MPI_File, MPI_Status
        implicit none
        type(MPI_File), intent(in) :: fh
        type(*), dimension(..), intent(in) :: buf
        type(MPI_Status) :: status
        integer, optional, intent(out) :: ierror
    end subroutine PMPIR_File_write_at_all_end_f08ts
end interface PMPI_File_write_at_all_end

interface PMPI_File_write_ordered
    subroutine PMPIR_File_write_ordered_f08ts(fh, buf, count, datatype, status, ierror)
        use :: mpi_f08_types, only : MPI_File, MPI_Datatype, MPI_Status
        implicit none
        type(MPI_File), intent(in) :: fh
        type(*), dimension(..), intent(in) :: buf
        integer, intent(in) :: count
        type(MPI_Datatype), intent(in) :: datatype
        type(MPI_Status) :: status
        integer, optional, intent(out) :: ierror
    end subroutine PMPIR_File_write_ordered_f08ts
end interface PMPI_File_write_ordered

interface PMPI_File_write_ordered_begin
    subroutine PMPIR_File_write_ordered_begin_f08ts(fh, buf, count, datatype, ierror)
        use :: mpi_f08_types, only : MPI_File, MPI_Datatype
        implicit none
        type(MPI_File), intent(in) :: fh
        type(*), dimension(..), intent(in) :: buf
        integer, intent(in) :: count
        type(MPI_Datatype), intent(in) :: datatype
        integer, optional, intent(out) :: ierror
    end subroutine PMPIR_File_write_ordered_begin_f08ts
end interface PMPI_File_write_ordered_begin

interface PMPI_File_write_ordered_end
    subroutine PMPIR_File_write_ordered_end_f08ts(fh, buf, status, ierror)
        use :: mpi_f08_types, only : MPI_File, MPI_Status
        implicit none
        type(MPI_File), intent(in) :: fh
        type(*), dimension(..), intent(in) :: buf
        type(MPI_Status) :: status
        integer, optional, intent(out) :: ierror
    end subroutine PMPIR_File_write_ordered_end_f08ts
end interface PMPI_File_write_ordered_end

interface PMPI_File_write_shared
    subroutine PMPIR_File_write_shared_f08ts(fh, buf, count, datatype, status, ierror)
        use :: mpi_f08_types, only : MPI_File, MPI_Datatype, MPI_Status
        implicit none
        type(MPI_File), intent(in) :: fh
        type(*), dimension(..), intent(in) :: buf
        integer, intent(in) :: count
        type(MPI_Datatype), intent(in) :: datatype
        type(MPI_Status) :: status
        integer, optional, intent(out) :: ierror
    end subroutine PMPIR_File_write_shared_f08ts
end interface PMPI_File_write_shared

interface PMPI_Register_datarep
    subroutine PMPIR_Register_datarep_f08(datarep, read_conversion_fn, write_conversion_fn, &
                                                 dtype_file_extent_fn, extra_state, ierror)
        use :: mpi_f08_compile_constants, only : MPI_ADDRESS_KIND
        use :: mpi_f08_callbacks, only : MPI_Datarep_conversion_function
        use :: mpi_f08_callbacks, only : MPI_Datarep_extent_function
        implicit none
        character(len=*), intent(in) :: datarep
        procedure(MPI_Datarep_conversion_function) :: read_conversion_fn
        procedure(MPI_Datarep_conversion_function) :: write_conversion_fn
        procedure(MPI_Datarep_extent_function) :: dtype_file_extent_fn
        integer(MPI_ADDRESS_KIND), intent(in) :: extra_state
        integer, optional, intent(out) :: ierror
    end subroutine PMPIR_Register_datarep_f08
end interface PMPI_Register_datarep


interface PMPI_Type_create_f90_complex
    subroutine PMPIR_Type_create_f90_complex_f08(p, r, newtype, ierror)
        use :: mpi_f08_types, only : MPI_Datatype
        implicit none
        integer, intent(in) :: p, r
        type(MPI_Datatype), intent(out) :: newtype
        integer, optional, intent(out) :: ierror
    end subroutine PMPIR_Type_create_f90_complex_f08
end interface PMPI_Type_create_f90_complex

interface PMPI_Type_create_f90_integer
    subroutine PMPIR_Type_create_f90_integer_f08(r, newtype, ierror)
        use :: mpi_f08_types, only : MPI_Datatype
        implicit none
        integer, intent(in) :: r
        type(MPI_Datatype), intent(out) :: newtype
        integer, optional, intent(out) :: ierror
    end subroutine PMPIR_Type_create_f90_integer_f08
end interface PMPI_Type_create_f90_integer

interface PMPI_Type_create_f90_real
    subroutine PMPIR_Type_create_f90_real_f08(p, r, newtype, ierror)
        use :: mpi_f08_types, only : MPI_Datatype
        implicit none
        integer, intent(in) :: p, r
        type(MPI_Datatype), intent(out) :: newtype
        integer, optional, intent(out) :: ierror
    end subroutine PMPIR_Type_create_f90_real_f08
end interface PMPI_Type_create_f90_real

interface PMPI_Type_match_size
    subroutine PMPIR_Type_match_size_f08(typeclass, size, datatype, ierror)
        use :: mpi_f08_types, only : MPI_Datatype
        implicit none
        integer, intent(in) :: typeclass, size
        type(MPI_Datatype), intent(out) :: datatype
        integer, optional, intent(out) :: ierror
    end subroutine PMPIR_Type_match_size_f08
end interface PMPI_Type_match_size

interface PMPI_Pcontrol
    subroutine PMPIR_Pcontrol_f08(level)
        implicit none
        integer, intent(in) :: level
    end subroutine PMPIR_Pcontrol_f08
end interface PMPI_Pcontrol

interface PMPI_Comm_split_type
    subroutine PMPIR_Comm_split_type_f08(comm, split_type, key, info, newcomm, ierror)
        use :: mpi_f08_types, only : MPI_Comm, MPI_Info
        implicit none
        type(MPI_Comm), intent(in) :: comm
        integer, intent(in) :: split_type
        integer, intent(in) :: key
        type(MPI_Info), intent(in) :: info
        type(MPI_Comm), intent(out) :: newcomm
        integer, optional, intent(out) :: ierror
    end subroutine PMPIR_Comm_split_type_f08
end interface PMPI_Comm_split_type

interface PMPI_F_sync_reg
    subroutine PMPIR_F_sync_reg_f08ts(buf)
        implicit none
        type(*), dimension(..) :: buf
    end subroutine PMPIR_F_sync_reg_f08ts
end interface PMPI_F_sync_reg

interface PMPI_Get_library_version
    subroutine PMPIR_Get_library_version_f08(version, resultlen, ierror)
        use :: mpi_f08_compile_constants, only : MPI_MAX_LIBRARY_VERSION_STRING
        implicit none
        character(len=MPI_MAX_LIBRARY_VERSION_STRING), intent(out) :: version
        integer, intent(out) :: resultlen
        integer, optional, intent(out) :: ierror
    end subroutine PMPIR_Get_library_version_f08
end interface PMPI_Get_library_version

interface PMPI_Mprobe
    subroutine PMPIR_Mprobe_f08(source, tag, comm, message, status, ierror)
        use :: mpi_f08_types, only : MPI_Comm, MPI_Message, MPI_Status
        implicit none
        integer, intent(in) :: source, tag
        type(MPI_Comm), intent(in) :: comm
        type(MPI_Message), intent(out) :: message
        type(MPI_Status) :: status
        integer, optional, intent(out) :: ierror
    end subroutine PMPIR_Mprobe_f08
end interface PMPI_Mprobe

interface PMPI_Improbe
    subroutine PMPIR_Improbe_f08(source, tag, comm, flag, message, status, ierror)
        use :: mpi_f08_types, only : MPI_Comm, MPI_Message, MPI_Status
        implicit none
        integer, intent(in) :: source, tag
        type(MPI_Comm), intent(in) :: comm
        logical, intent(out) :: flag
        type(MPI_Message), intent(out) :: message
        type(MPI_Status) :: status
        integer, optional, intent(out) :: ierror
    end subroutine PMPIR_Improbe_f08
end interface PMPI_Improbe

interface PMPI_Imrecv
    subroutine PMPIR_Imrecv_f08ts(buf, count, datatype, message, request, ierror)
        use :: mpi_f08_types, only : MPI_Datatype, MPI_Message, MPI_Request
        implicit none
        type(*), dimension(..), asynchronous :: buf
        integer, intent(in) :: count
        type(MPI_Datatype), intent(in) :: datatype
        type(MPI_Message), intent(inout) :: message
        type(MPI_Request), intent(out) :: request
        integer, optional, intent(out) :: ierror
    end subroutine PMPIR_Imrecv_f08ts
end interface PMPI_Imrecv

interface PMPI_Mrecv
    subroutine PMPIR_Mrecv_f08ts(buf, count, datatype, message, status, ierror)
        use :: mpi_f08_types, only : MPI_Datatype, MPI_Message, MPI_Status
        implicit none
        type(*), dimension(..) :: buf
        integer, intent(in) :: count
        type(MPI_Datatype), intent(in) :: datatype
        type(MPI_Message), intent(inout) :: message
        type(MPI_Status) :: status
        integer, optional, intent(out) :: ierror
    end subroutine PMPIR_Mrecv_f08ts
end interface PMPI_Mrecv

interface PMPI_Neighbor_allgather
    subroutine PMPIR_Neighbor_allgather_f08ts(sendbuf, sendcount, sendtype, recvbuf, recvcount, recvtype, &
                 comm, ierror)
        use :: mpi_f08_types, only : MPI_Datatype, MPI_Comm
        implicit none
        type(*), dimension(..), intent(in) :: sendbuf
        type(*), dimension(..) :: recvbuf
        integer, intent(in) :: sendcount, recvcount
        type(MPI_Datatype), intent(in) :: sendtype, recvtype
        type(MPI_Comm), intent(in) :: comm
        integer, optional, intent(out) :: ierror
    end subroutine PMPIR_Neighbor_allgather_f08ts
end interface PMPI_Neighbor_allgather

interface PMPI_Ineighbor_allgather
    subroutine PMPIR_Ineighbor_allgather_f08ts(sendbuf, sendcount, sendtype, recvbuf, recvcount, recvtype, &
                 comm, request, ierror)
        use :: mpi_f08_types, only : MPI_Datatype, MPI_Comm, MPI_Request
        implicit none
        type(*), dimension(..), intent(in), asynchronous :: sendbuf
        type(*), dimension(..), asynchronous :: recvbuf
        integer, intent(in) :: sendcount, recvcount
        type(MPI_Datatype), intent(in) :: sendtype, recvtype
        type(MPI_Comm), intent(in) :: comm
        type(MPI_Request), intent(out) :: request
        integer, optional, intent(out) :: ierror
    end subroutine PMPIR_Ineighbor_allgather_f08ts
end interface PMPI_Ineighbor_allgather

interface PMPI_Neighbor_allgatherv
    subroutine PMPIR_Neighbor_allgatherv_f08ts(sendbuf, sendcount, sendtype, recvbuf, recvcounts, displs, &
                 recvtype, comm, ierror)
        use :: mpi_f08_types, only : MPI_Datatype, MPI_Comm
        implicit none
        type(*), dimension(..), intent(in) :: sendbuf
        type(*), dimension(..) :: recvbuf
        integer, intent(in) :: sendcount
        integer, intent(in) :: recvcounts(*), displs(*)
        type(MPI_Datatype), intent(in) :: sendtype, recvtype
        type(MPI_Comm), intent(in) :: comm
        integer, optional, intent(out) :: ierror
    end subroutine PMPIR_Neighbor_allgatherv_f08ts
end interface PMPI_Neighbor_allgatherv

interface PMPI_Ineighbor_allgatherv
    subroutine PMPIR_Ineighbor_allgatherv_f08ts(sendbuf, sendcount, sendtype, recvbuf, recvcounts, displs, &
                 recvtype, comm, request, ierror)
        use :: mpi_f08_types, only : MPI_Datatype, MPI_Comm, MPI_Request
        implicit none
        type(*), dimension(..), intent(in), asynchronous :: sendbuf
        type(*), dimension(..), asynchronous :: recvbuf
        integer, intent(in) :: sendcount
        integer, intent(in) :: recvcounts(*), displs(*)
        type(MPI_Datatype), intent(in) :: sendtype, recvtype
        type(MPI_Comm), intent(in) :: comm
        type(MPI_Request), intent(out) :: request
        integer, optional, intent(out) :: ierror
    end subroutine PMPIR_Ineighbor_allgatherv_f08ts
end interface PMPI_Ineighbor_allgatherv

interface PMPI_Neighbor_alltoall
    subroutine PMPIR_Neighbor_alltoall_f08ts(sendbuf, sendcount, sendtype, recvbuf, recvcount, recvtype, &
                 comm, ierror)
        use :: mpi_f08_types, only : MPI_Datatype, MPI_Comm
        implicit none
        type(*), dimension(..), intent(in) :: sendbuf
        type(*), dimension(..) :: recvbuf
        integer, intent(in) :: sendcount, recvcount
        type(MPI_Datatype), intent(in) :: sendtype, recvtype
        type(MPI_Comm), intent(in) :: comm
        integer, optional, intent(out) :: ierror
    end subroutine PMPIR_Neighbor_alltoall_f08ts
end interface PMPI_Neighbor_alltoall

interface PMPI_Ineighbor_alltoall
    subroutine PMPIR_Ineighbor_alltoall_f08ts(sendbuf, sendcount, sendtype, recvbuf, recvcount, recvtype, &
                 comm, request, ierror)
        use :: mpi_f08_types, only : MPI_Datatype, MPI_Comm, MPI_Request
        implicit none
        type(*), dimension(..), intent(in), asynchronous :: sendbuf
        type(*), dimension(..), asynchronous :: recvbuf
        integer, intent(in) :: sendcount, recvcount
        type(MPI_Datatype), intent(in) :: sendtype, recvtype
        type(MPI_Comm), intent(in) :: comm
        type(MPI_Request), intent(out) :: request
        integer, optional, intent(out) :: ierror
    end subroutine PMPIR_Ineighbor_alltoall_f08ts
end interface PMPI_Ineighbor_alltoall

interface PMPI_Neighbor_alltoallv
    subroutine PMPIR_Neighbor_alltoallv_f08ts(sendbuf, sendcounts, sdispls, sendtype, recvbuf, recvcounts, &
                 rdispls, recvtype, comm, ierror)
        use :: mpi_f08_types, only : MPI_Datatype, MPI_Comm
        implicit none
        type(*), dimension(..), intent(in) :: sendbuf
        type(*), dimension(..) :: recvbuf
        integer, intent(in) :: sendcounts(*), sdispls(*), recvcounts(*), rdispls(*)
        type(MPI_Datatype), intent(in) :: sendtype, recvtype
        type(MPI_Comm), intent(in) :: comm
        integer, optional, intent(out) :: ierror
    end subroutine PMPIR_Neighbor_alltoallv_f08ts
end interface PMPI_Neighbor_alltoallv

interface PMPI_Ineighbor_alltoallv
    subroutine PMPIR_Ineighbor_alltoallv_f08ts(sendbuf, sendcounts, sdispls, sendtype, recvbuf, recvcounts, &
                 rdispls, recvtype, comm, request, ierror)
        use :: mpi_f08_types, only : MPI_Datatype, MPI_Comm, MPI_Request
        implicit none
        type(*), dimension(..), intent(in), asynchronous :: sendbuf
        type(*), dimension(..), asynchronous :: recvbuf
        integer, intent(in) :: sendcounts(*), sdispls(*), recvcounts(*), rdispls(*)
        type(MPI_Datatype), intent(in) :: sendtype, recvtype
        type(MPI_Comm), intent(in) :: comm
        type(MPI_Request), intent(in) :: request
        integer, optional, intent(out) :: ierror
    end subroutine PMPIR_Ineighbor_alltoallv_f08ts
end interface PMPI_Ineighbor_alltoallv

interface PMPI_Neighbor_alltoallw
    subroutine PMPIR_Neighbor_alltoallw_f08ts(sendbuf, sendcounts, sdispls, sendtypes, recvbuf, recvcounts, &
                 rdispls, recvtypes, comm, ierror)
        use :: mpi_f08_types, only : MPI_Datatype, MPI_Comm
        use :: mpi_f08_compile_constants, only : MPI_ADDRESS_KIND
        implicit none
        type(*), dimension(..), intent(in) :: sendbuf
        type(*), dimension(..) :: recvbuf
        integer, intent(in) :: sendcounts(*), recvcounts(*)
        integer(MPI_ADDRESS_KIND), intent(in) :: sdispls(*), rdispls(*)
        type(MPI_Datatype), intent(in) :: sendtypes(*), recvtypes(*)
        type(MPI_Comm), intent(in) :: comm
        integer, optional, intent(out) :: ierror
    end subroutine PMPIR_Neighbor_alltoallw_f08ts
end interface PMPI_Neighbor_alltoallw

interface PMPI_Ineighbor_alltoallw
    subroutine PMPIR_Ineighbor_alltoallw_f08ts(sendbuf, sendcounts, sdispls, sendtypes, recvbuf, recvcounts, &
                 rdispls, recvtypes, comm, request, ierror)
        use :: mpi_f08_types, only : MPI_Datatype, MPI_Comm, MPI_Request
        use :: mpi_f08_compile_constants, only : MPI_ADDRESS_KIND
        implicit none
        type(*), dimension(..), intent(in), asynchronous :: sendbuf
        type(*), dimension(..), asynchronous :: recvbuf
        integer, intent(in) :: sendcounts(*), recvcounts(*)
        integer(MPI_ADDRESS_KIND), intent(in) :: sdispls(*), rdispls(*)
        type(MPI_Datatype), intent(in) :: sendtypes(*), recvtypes(*)
        type(MPI_Comm), intent(in) :: comm
        type(MPI_Request), intent(in) :: request
        integer, optional, intent(out) :: ierror
    end subroutine PMPIR_Ineighbor_alltoallw_f08ts
end interface PMPI_Ineighbor_alltoallw

interface PMPI_Wtick
    function PMPIR_Wtick_f08() result(res)
        implicit none
        double precision :: res
    end function PMPIR_Wtick_f08
end interface PMPI_Wtick

interface PMPI_Wtime
    function PMPIR_Wtime_f08() result(res)
        implicit none
        double precision :: res
    end function PMPIR_Wtime_f08
end interface PMPI_Wtime

interface PMPI_Aint_add
    function PMPIR_Aint_add_f08(base, disp) result(res)
        use :: mpi_f08_compile_constants, only : MPI_ADDRESS_KIND
        implicit none
        integer(MPI_ADDRESS_KIND), intent(in) :: base, disp
        integer(MPI_ADDRESS_KIND) :: res
    end function PMPIR_Aint_add_f08
end interface PMPI_Aint_add

interface PMPI_Aint_diff
    function PMPIR_Aint_diff_f08(addr1, addr2) result(res)
        use :: mpi_f08_compile_constants, only : MPI_ADDRESS_KIND
        implicit none
        integer(MPI_ADDRESS_KIND), intent(in) :: addr1, addr2
        integer(MPI_ADDRESS_KIND) :: res
    end function PMPIR_Aint_diff_f08
end interface PMPI_Aint_diff

interface PMPI_File_iread_all
    subroutine PMPIR_File_iread_all_f08ts(fh, buf, count, datatype, request, ierror)
        use :: mpi_f08_types, only : MPI_File, MPI_Datatype, MPI_Request
        implicit none
        type(MPI_File), intent(in) :: fh
        type(*), dimension(..) :: buf
        integer, intent(in) :: count
        type(MPI_Datatype), intent(in) :: datatype
        type(MPI_Request), intent(out) :: request
        integer, optional, intent(out) :: ierror
    end subroutine PMPIR_File_iread_all_f08ts
end interface PMPI_File_iread_all

interface PMPI_File_iwrite_all
    subroutine PMPIR_File_iwrite_all_f08ts(fh, buf, count, datatype, request, ierror)
        use :: mpi_f08_types, only : MPI_File, MPI_Datatype, MPI_Request
        implicit none
        type(MPI_File), intent(in) :: fh
        type(*), dimension(..), intent(in) :: buf
        integer, intent(in) :: count
        type(MPI_Datatype), intent(in) :: datatype
        type(MPI_Request), intent(out) :: request
        integer, optional, intent(out) :: ierror
    end subroutine PMPIR_File_iwrite_all_f08ts
end interface PMPI_File_iwrite_all

interface PMPI_File_iread_at_all
    subroutine PMPIR_File_iread_at_all_f08ts(fh, offset, buf, count, datatype, request, ierror)
        use :: mpi_f08_types, only : MPI_File, MPI_Datatype, MPI_Request
        use :: mpi_f08_compile_constants, only : MPI_OFFSET_KIND
        implicit none
        type(MPI_File), intent(in) :: fh
        integer(MPI_OFFSET_KIND), intent(in) :: offset
        type(*), dimension(..) :: buf
        integer, intent(in) :: count
        type(MPI_Datatype), intent(in) :: datatype
        type(MPI_Request), intent(out) :: request
        integer, optional, intent(out) :: ierror
    end subroutine PMPIR_File_iread_at_all_f08ts
end interface PMPI_File_iread_at_all

interface PMPI_File_iwrite_at_all
    subroutine PMPIR_File_iwrite_at_all_f08ts(fh, offset, buf, count, datatype, request, ierror)
        use :: mpi_f08_types, only : MPI_File, MPI_Datatype, MPI_Request
        use :: mpi_f08_compile_constants, only : MPI_OFFSET_KIND
        implicit none
        type(MPI_File), intent(in) :: fh
        integer(MPI_OFFSET_KIND), intent(in) :: offset
        type(*), dimension(..) :: buf
        integer, intent(in) :: count
        type(MPI_Datatype), intent(in) :: datatype
        type(MPI_Request), intent(out) :: request
        integer, optional, intent(out) :: ierror
    end subroutine PMPIR_File_iwrite_at_all_f08ts
end interface PMPI_File_iwrite_at_all

end module pmpi_f08
