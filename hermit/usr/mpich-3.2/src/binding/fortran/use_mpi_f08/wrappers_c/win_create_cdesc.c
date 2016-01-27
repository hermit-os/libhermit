/* -*- Mode: C; c-basic-offset:4 ; -*- */
/*
 *  (C) 2014 by Argonne National Laboratory.
 *      See COPYRIGHT in top-level directory.
 *
 * This file is automatically generated by buildiface
 * DO NOT EDIT
 */

#include "cdesc.h"

int MPIR_Win_create_cdesc(CFI_cdesc_t* x0, MPI_Aint x1, int x2, MPI_Info x3, MPI_Comm x4, MPI_Win * x5)
{
    int err = MPI_SUCCESS;
    void *buf0 = x0->base_addr;

    if (buf0 == &MPIR_F08_MPI_BOTTOM) {
        buf0 = MPI_BOTTOM;
    }

    err = MPI_Win_create(buf0, x1, x2, x3, x4, x5);

    return err;
}