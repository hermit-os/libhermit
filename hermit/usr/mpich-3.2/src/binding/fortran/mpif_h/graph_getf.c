/* -*- Mode: C; c-basic-offset:4 ; -*- */
/*  
 *  (C) 2001 by Argonne National Laboratory.
 *      See COPYRIGHT in top-level directory.
 *
 * This file is automatically generated by buildiface 
 * DO NOT EDIT
 */
#include "mpi_fortimpl.h"


/* Begin MPI profiling block */
#if defined(USE_WEAK_SYMBOLS) && !defined(USE_ONLY_MPI_NAMES) 
#if defined(HAVE_MULTIPLE_PRAGMA_WEAK)
extern FORT_DLL_SPEC void FORT_CALL MPI_GRAPH_GET( MPI_Fint *, MPI_Fint *, MPI_Fint *, MPI_Fint [], MPI_Fint [], MPI_Fint * );
extern FORT_DLL_SPEC void FORT_CALL mpi_graph_get__( MPI_Fint *, MPI_Fint *, MPI_Fint *, MPI_Fint [], MPI_Fint [], MPI_Fint * );
extern FORT_DLL_SPEC void FORT_CALL mpi_graph_get( MPI_Fint *, MPI_Fint *, MPI_Fint *, MPI_Fint [], MPI_Fint [], MPI_Fint * );
extern FORT_DLL_SPEC void FORT_CALL mpi_graph_get_( MPI_Fint *, MPI_Fint *, MPI_Fint *, MPI_Fint [], MPI_Fint [], MPI_Fint * );

#if defined(F77_NAME_UPPER)
#pragma weak MPI_GRAPH_GET = PMPI_GRAPH_GET
#pragma weak mpi_graph_get__ = PMPI_GRAPH_GET
#pragma weak mpi_graph_get_ = PMPI_GRAPH_GET
#pragma weak mpi_graph_get = PMPI_GRAPH_GET
#elif defined(F77_NAME_LOWER_2USCORE)
#pragma weak MPI_GRAPH_GET = pmpi_graph_get__
#pragma weak mpi_graph_get__ = pmpi_graph_get__
#pragma weak mpi_graph_get_ = pmpi_graph_get__
#pragma weak mpi_graph_get = pmpi_graph_get__
#elif defined(F77_NAME_LOWER_USCORE)
#pragma weak MPI_GRAPH_GET = pmpi_graph_get_
#pragma weak mpi_graph_get__ = pmpi_graph_get_
#pragma weak mpi_graph_get_ = pmpi_graph_get_
#pragma weak mpi_graph_get = pmpi_graph_get_
#else
#pragma weak MPI_GRAPH_GET = pmpi_graph_get
#pragma weak mpi_graph_get__ = pmpi_graph_get
#pragma weak mpi_graph_get_ = pmpi_graph_get
#pragma weak mpi_graph_get = pmpi_graph_get
#endif



#elif defined(HAVE_PRAGMA_WEAK)

#if defined(F77_NAME_UPPER)
extern FORT_DLL_SPEC void FORT_CALL MPI_GRAPH_GET( MPI_Fint *, MPI_Fint *, MPI_Fint *, MPI_Fint [], MPI_Fint [], MPI_Fint * );

#pragma weak MPI_GRAPH_GET = PMPI_GRAPH_GET
#elif defined(F77_NAME_LOWER_2USCORE)
extern FORT_DLL_SPEC void FORT_CALL mpi_graph_get__( MPI_Fint *, MPI_Fint *, MPI_Fint *, MPI_Fint [], MPI_Fint [], MPI_Fint * );

#pragma weak mpi_graph_get__ = pmpi_graph_get__
#elif !defined(F77_NAME_LOWER_USCORE)
extern FORT_DLL_SPEC void FORT_CALL mpi_graph_get( MPI_Fint *, MPI_Fint *, MPI_Fint *, MPI_Fint [], MPI_Fint [], MPI_Fint * );

#pragma weak mpi_graph_get = pmpi_graph_get
#else
extern FORT_DLL_SPEC void FORT_CALL mpi_graph_get_( MPI_Fint *, MPI_Fint *, MPI_Fint *, MPI_Fint [], MPI_Fint [], MPI_Fint * );

#pragma weak mpi_graph_get_ = pmpi_graph_get_
#endif

#elif defined(HAVE_PRAGMA_HP_SEC_DEF)
#if defined(F77_NAME_UPPER)
#pragma _HP_SECONDARY_DEF PMPI_GRAPH_GET  MPI_GRAPH_GET
#elif defined(F77_NAME_LOWER_2USCORE)
#pragma _HP_SECONDARY_DEF pmpi_graph_get__  mpi_graph_get__
#elif !defined(F77_NAME_LOWER_USCORE)
#pragma _HP_SECONDARY_DEF pmpi_graph_get  mpi_graph_get
#else
#pragma _HP_SECONDARY_DEF pmpi_graph_get_  mpi_graph_get_
#endif

#elif defined(HAVE_PRAGMA_CRI_DUP)
#if defined(F77_NAME_UPPER)
#pragma _CRI duplicate MPI_GRAPH_GET as PMPI_GRAPH_GET
#elif defined(F77_NAME_LOWER_2USCORE)
#pragma _CRI duplicate mpi_graph_get__ as pmpi_graph_get__
#elif !defined(F77_NAME_LOWER_USCORE)
#pragma _CRI duplicate mpi_graph_get as pmpi_graph_get
#else
#pragma _CRI duplicate mpi_graph_get_ as pmpi_graph_get_
#endif

#elif defined(HAVE_WEAK_ATTRIBUTE)
#if defined(F77_NAME_UPPER)
extern FORT_DLL_SPEC void FORT_CALL MPI_GRAPH_GET( MPI_Fint *, MPI_Fint *, MPI_Fint *, MPI_Fint [], MPI_Fint [], MPI_Fint * ) __attribute__((weak,alias("PMPI_GRAPH_GET")));
extern FORT_DLL_SPEC void FORT_CALL mpi_graph_get__( MPI_Fint *, MPI_Fint *, MPI_Fint *, MPI_Fint [], MPI_Fint [], MPI_Fint * ) __attribute__((weak,alias("PMPI_GRAPH_GET")));
extern FORT_DLL_SPEC void FORT_CALL mpi_graph_get_( MPI_Fint *, MPI_Fint *, MPI_Fint *, MPI_Fint [], MPI_Fint [], MPI_Fint * ) __attribute__((weak,alias("PMPI_GRAPH_GET")));
extern FORT_DLL_SPEC void FORT_CALL mpi_graph_get( MPI_Fint *, MPI_Fint *, MPI_Fint *, MPI_Fint [], MPI_Fint [], MPI_Fint * ) __attribute__((weak,alias("PMPI_GRAPH_GET")));

#elif defined(F77_NAME_LOWER_2USCORE)
extern FORT_DLL_SPEC void FORT_CALL MPI_GRAPH_GET( MPI_Fint *, MPI_Fint *, MPI_Fint *, MPI_Fint [], MPI_Fint [], MPI_Fint * ) __attribute__((weak,alias("pmpi_graph_get__")));
extern FORT_DLL_SPEC void FORT_CALL mpi_graph_get__( MPI_Fint *, MPI_Fint *, MPI_Fint *, MPI_Fint [], MPI_Fint [], MPI_Fint * ) __attribute__((weak,alias("pmpi_graph_get__")));
extern FORT_DLL_SPEC void FORT_CALL mpi_graph_get_( MPI_Fint *, MPI_Fint *, MPI_Fint *, MPI_Fint [], MPI_Fint [], MPI_Fint * ) __attribute__((weak,alias("pmpi_graph_get__")));
extern FORT_DLL_SPEC void FORT_CALL mpi_graph_get( MPI_Fint *, MPI_Fint *, MPI_Fint *, MPI_Fint [], MPI_Fint [], MPI_Fint * ) __attribute__((weak,alias("pmpi_graph_get__")));

#elif defined(F77_NAME_LOWER_USCORE)
extern FORT_DLL_SPEC void FORT_CALL MPI_GRAPH_GET( MPI_Fint *, MPI_Fint *, MPI_Fint *, MPI_Fint [], MPI_Fint [], MPI_Fint * ) __attribute__((weak,alias("pmpi_graph_get_")));
extern FORT_DLL_SPEC void FORT_CALL mpi_graph_get__( MPI_Fint *, MPI_Fint *, MPI_Fint *, MPI_Fint [], MPI_Fint [], MPI_Fint * ) __attribute__((weak,alias("pmpi_graph_get_")));
extern FORT_DLL_SPEC void FORT_CALL mpi_graph_get_( MPI_Fint *, MPI_Fint *, MPI_Fint *, MPI_Fint [], MPI_Fint [], MPI_Fint * ) __attribute__((weak,alias("pmpi_graph_get_")));
extern FORT_DLL_SPEC void FORT_CALL mpi_graph_get( MPI_Fint *, MPI_Fint *, MPI_Fint *, MPI_Fint [], MPI_Fint [], MPI_Fint * ) __attribute__((weak,alias("pmpi_graph_get_")));

#else
extern FORT_DLL_SPEC void FORT_CALL MPI_GRAPH_GET( MPI_Fint *, MPI_Fint *, MPI_Fint *, MPI_Fint [], MPI_Fint [], MPI_Fint * ) __attribute__((weak,alias("pmpi_graph_get")));
extern FORT_DLL_SPEC void FORT_CALL mpi_graph_get__( MPI_Fint *, MPI_Fint *, MPI_Fint *, MPI_Fint [], MPI_Fint [], MPI_Fint * ) __attribute__((weak,alias("pmpi_graph_get")));
extern FORT_DLL_SPEC void FORT_CALL mpi_graph_get_( MPI_Fint *, MPI_Fint *, MPI_Fint *, MPI_Fint [], MPI_Fint [], MPI_Fint * ) __attribute__((weak,alias("pmpi_graph_get")));
extern FORT_DLL_SPEC void FORT_CALL mpi_graph_get( MPI_Fint *, MPI_Fint *, MPI_Fint *, MPI_Fint [], MPI_Fint [], MPI_Fint * ) __attribute__((weak,alias("pmpi_graph_get")));

#endif
#endif /* HAVE_PRAGMA_WEAK */
#endif /* USE_WEAK_SYMBOLS */
/* End MPI profiling block */


/* These definitions are used only for generating the Fortran wrappers */
#if defined(USE_WEAK_SYMBOLS) && defined(USE_ONLY_MPI_NAMES)
#if defined(HAVE_MULTIPLE_PRAGMA_WEAK)
extern FORT_DLL_SPEC void FORT_CALL MPI_GRAPH_GET( MPI_Fint *, MPI_Fint *, MPI_Fint *, MPI_Fint [], MPI_Fint [], MPI_Fint * );
extern FORT_DLL_SPEC void FORT_CALL mpi_graph_get__( MPI_Fint *, MPI_Fint *, MPI_Fint *, MPI_Fint [], MPI_Fint [], MPI_Fint * );
extern FORT_DLL_SPEC void FORT_CALL mpi_graph_get( MPI_Fint *, MPI_Fint *, MPI_Fint *, MPI_Fint [], MPI_Fint [], MPI_Fint * );
extern FORT_DLL_SPEC void FORT_CALL mpi_graph_get_( MPI_Fint *, MPI_Fint *, MPI_Fint *, MPI_Fint [], MPI_Fint [], MPI_Fint * );

#if defined(F77_NAME_UPPER)
#pragma weak mpi_graph_get__ = MPI_GRAPH_GET
#pragma weak mpi_graph_get_ = MPI_GRAPH_GET
#pragma weak mpi_graph_get = MPI_GRAPH_GET
#elif defined(F77_NAME_LOWER_2USCORE)
#pragma weak MPI_GRAPH_GET = mpi_graph_get__
#pragma weak mpi_graph_get_ = mpi_graph_get__
#pragma weak mpi_graph_get = mpi_graph_get__
#elif defined(F77_NAME_LOWER_USCORE)
#pragma weak MPI_GRAPH_GET = mpi_graph_get_
#pragma weak mpi_graph_get__ = mpi_graph_get_
#pragma weak mpi_graph_get = mpi_graph_get_
#else
#pragma weak MPI_GRAPH_GET = mpi_graph_get
#pragma weak mpi_graph_get__ = mpi_graph_get
#pragma weak mpi_graph_get_ = mpi_graph_get
#endif
#elif defined(HAVE_WEAK_ATTRIBUTE)
#if defined(F77_NAME_UPPER)
extern FORT_DLL_SPEC void FORT_CALL MPI_GRAPH_GET( MPI_Fint *, MPI_Fint *, MPI_Fint *, MPI_Fint [], MPI_Fint [], MPI_Fint * );
extern FORT_DLL_SPEC void FORT_CALL mpi_graph_get__( MPI_Fint *, MPI_Fint *, MPI_Fint *, MPI_Fint [], MPI_Fint [], MPI_Fint * ) __attribute__((weak,alias("MPI_GRAPH_GET")));
extern FORT_DLL_SPEC void FORT_CALL mpi_graph_get_( MPI_Fint *, MPI_Fint *, MPI_Fint *, MPI_Fint [], MPI_Fint [], MPI_Fint * ) __attribute__((weak,alias("MPI_GRAPH_GET")));
extern FORT_DLL_SPEC void FORT_CALL mpi_graph_get( MPI_Fint *, MPI_Fint *, MPI_Fint *, MPI_Fint [], MPI_Fint [], MPI_Fint * ) __attribute__((weak,alias("MPI_GRAPH_GET")));

#elif defined(F77_NAME_LOWER_2USCORE)
extern FORT_DLL_SPEC void FORT_CALL MPI_GRAPH_GET( MPI_Fint *, MPI_Fint *, MPI_Fint *, MPI_Fint [], MPI_Fint [], MPI_Fint * ) __attribute__((weak,alias("mpi_graph_get__")));
extern FORT_DLL_SPEC void FORT_CALL mpi_graph_get__( MPI_Fint *, MPI_Fint *, MPI_Fint *, MPI_Fint [], MPI_Fint [], MPI_Fint * );
extern FORT_DLL_SPEC void FORT_CALL mpi_graph_get_( MPI_Fint *, MPI_Fint *, MPI_Fint *, MPI_Fint [], MPI_Fint [], MPI_Fint * ) __attribute__((weak,alias("mpi_graph_get__")));
extern FORT_DLL_SPEC void FORT_CALL mpi_graph_get( MPI_Fint *, MPI_Fint *, MPI_Fint *, MPI_Fint [], MPI_Fint [], MPI_Fint * ) __attribute__((weak,alias("mpi_graph_get__")));

#elif defined(F77_NAME_LOWER_USCORE)
extern FORT_DLL_SPEC void FORT_CALL MPI_GRAPH_GET( MPI_Fint *, MPI_Fint *, MPI_Fint *, MPI_Fint [], MPI_Fint [], MPI_Fint * ) __attribute__((weak,alias("mpi_graph_get_")));
extern FORT_DLL_SPEC void FORT_CALL mpi_graph_get__( MPI_Fint *, MPI_Fint *, MPI_Fint *, MPI_Fint [], MPI_Fint [], MPI_Fint * ) __attribute__((weak,alias("mpi_graph_get_")));
extern FORT_DLL_SPEC void FORT_CALL mpi_graph_get_( MPI_Fint *, MPI_Fint *, MPI_Fint *, MPI_Fint [], MPI_Fint [], MPI_Fint * );
extern FORT_DLL_SPEC void FORT_CALL mpi_graph_get( MPI_Fint *, MPI_Fint *, MPI_Fint *, MPI_Fint [], MPI_Fint [], MPI_Fint * ) __attribute__((weak,alias("mpi_graph_get_")));

#else
extern FORT_DLL_SPEC void FORT_CALL MPI_GRAPH_GET( MPI_Fint *, MPI_Fint *, MPI_Fint *, MPI_Fint [], MPI_Fint [], MPI_Fint * ) __attribute__((weak,alias("mpi_graph_get")));
extern FORT_DLL_SPEC void FORT_CALL mpi_graph_get__( MPI_Fint *, MPI_Fint *, MPI_Fint *, MPI_Fint [], MPI_Fint [], MPI_Fint * ) __attribute__((weak,alias("mpi_graph_get")));
extern FORT_DLL_SPEC void FORT_CALL mpi_graph_get_( MPI_Fint *, MPI_Fint *, MPI_Fint *, MPI_Fint [], MPI_Fint [], MPI_Fint * ) __attribute__((weak,alias("mpi_graph_get")));
extern FORT_DLL_SPEC void FORT_CALL mpi_graph_get( MPI_Fint *, MPI_Fint *, MPI_Fint *, MPI_Fint [], MPI_Fint [], MPI_Fint * );

#endif
#endif

#endif

/* Map the name to the correct form */
#ifndef MPICH_MPI_FROM_PMPI
#if defined(USE_WEAK_SYMBOLS)
#if defined(HAVE_MULTIPLE_PRAGMA_WEAK)
/* Define the weak versions of the PMPI routine*/
#ifndef F77_NAME_UPPER
extern FORT_DLL_SPEC void FORT_CALL PMPI_GRAPH_GET( MPI_Fint *, MPI_Fint *, MPI_Fint *, MPI_Fint [], MPI_Fint [], MPI_Fint * );
#endif
#ifndef F77_NAME_LOWER_2USCORE
extern FORT_DLL_SPEC void FORT_CALL pmpi_graph_get__( MPI_Fint *, MPI_Fint *, MPI_Fint *, MPI_Fint [], MPI_Fint [], MPI_Fint * );
#endif
#ifndef F77_NAME_LOWER_USCORE
extern FORT_DLL_SPEC void FORT_CALL pmpi_graph_get_( MPI_Fint *, MPI_Fint *, MPI_Fint *, MPI_Fint [], MPI_Fint [], MPI_Fint * );
#endif
#ifndef F77_NAME_LOWER
extern FORT_DLL_SPEC void FORT_CALL pmpi_graph_get( MPI_Fint *, MPI_Fint *, MPI_Fint *, MPI_Fint [], MPI_Fint [], MPI_Fint * );

#endif

#if defined(F77_NAME_UPPER)
#pragma weak pmpi_graph_get__ = PMPI_GRAPH_GET
#pragma weak pmpi_graph_get_ = PMPI_GRAPH_GET
#pragma weak pmpi_graph_get = PMPI_GRAPH_GET
#elif defined(F77_NAME_LOWER_2USCORE)
#pragma weak PMPI_GRAPH_GET = pmpi_graph_get__
#pragma weak pmpi_graph_get_ = pmpi_graph_get__
#pragma weak pmpi_graph_get = pmpi_graph_get__
#elif defined(F77_NAME_LOWER_USCORE)
#pragma weak PMPI_GRAPH_GET = pmpi_graph_get_
#pragma weak pmpi_graph_get__ = pmpi_graph_get_
#pragma weak pmpi_graph_get = pmpi_graph_get_
#else
#pragma weak PMPI_GRAPH_GET = pmpi_graph_get
#pragma weak pmpi_graph_get__ = pmpi_graph_get
#pragma weak pmpi_graph_get_ = pmpi_graph_get
#endif /* Test on name mapping */

#elif defined(HAVE_WEAK_ATTRIBUTE)
#if defined(F77_NAME_UPPER)
extern FORT_DLL_SPEC void FORT_CALL pmpi_graph_get__( MPI_Fint *, MPI_Fint *, MPI_Fint *, MPI_Fint [], MPI_Fint [], MPI_Fint * ) __attribute__((weak,alias("PMPI_GRAPH_GET")));
extern FORT_DLL_SPEC void FORT_CALL pmpi_graph_get_( MPI_Fint *, MPI_Fint *, MPI_Fint *, MPI_Fint [], MPI_Fint [], MPI_Fint * ) __attribute__((weak,alias("PMPI_GRAPH_GET")));
extern FORT_DLL_SPEC void FORT_CALL pmpi_graph_get( MPI_Fint *, MPI_Fint *, MPI_Fint *, MPI_Fint [], MPI_Fint [], MPI_Fint * ) __attribute__((weak,alias("PMPI_GRAPH_GET")));

#elif defined(F77_NAME_LOWER_2USCORE)
extern FORT_DLL_SPEC void FORT_CALL PMPI_GRAPH_GET( MPI_Fint *, MPI_Fint *, MPI_Fint *, MPI_Fint [], MPI_Fint [], MPI_Fint * ) __attribute__((weak,alias("pmpi_graph_get__")));
extern FORT_DLL_SPEC void FORT_CALL pmpi_graph_get_( MPI_Fint *, MPI_Fint *, MPI_Fint *, MPI_Fint [], MPI_Fint [], MPI_Fint * ) __attribute__((weak,alias("pmpi_graph_get__")));
extern FORT_DLL_SPEC void FORT_CALL pmpi_graph_get( MPI_Fint *, MPI_Fint *, MPI_Fint *, MPI_Fint [], MPI_Fint [], MPI_Fint * ) __attribute__((weak,alias("pmpi_graph_get__")));

#elif defined(F77_NAME_LOWER_USCORE)
extern FORT_DLL_SPEC void FORT_CALL PMPI_GRAPH_GET( MPI_Fint *, MPI_Fint *, MPI_Fint *, MPI_Fint [], MPI_Fint [], MPI_Fint * ) __attribute__((weak,alias("pmpi_graph_get_")));
extern FORT_DLL_SPEC void FORT_CALL pmpi_graph_get__( MPI_Fint *, MPI_Fint *, MPI_Fint *, MPI_Fint [], MPI_Fint [], MPI_Fint * ) __attribute__((weak,alias("pmpi_graph_get_")));
extern FORT_DLL_SPEC void FORT_CALL pmpi_graph_get( MPI_Fint *, MPI_Fint *, MPI_Fint *, MPI_Fint [], MPI_Fint [], MPI_Fint * ) __attribute__((weak,alias("pmpi_graph_get_")));

#else
extern FORT_DLL_SPEC void FORT_CALL PMPI_GRAPH_GET( MPI_Fint *, MPI_Fint *, MPI_Fint *, MPI_Fint [], MPI_Fint [], MPI_Fint * ) __attribute__((weak,alias("pmpi_graph_get")));
extern FORT_DLL_SPEC void FORT_CALL pmpi_graph_get__( MPI_Fint *, MPI_Fint *, MPI_Fint *, MPI_Fint [], MPI_Fint [], MPI_Fint * ) __attribute__((weak,alias("pmpi_graph_get")));
extern FORT_DLL_SPEC void FORT_CALL pmpi_graph_get_( MPI_Fint *, MPI_Fint *, MPI_Fint *, MPI_Fint [], MPI_Fint [], MPI_Fint * ) __attribute__((weak,alias("pmpi_graph_get")));

#endif /* Test on name mapping */
#endif /* HAVE_MULTIPLE_PRAGMA_WEAK */
#endif /* USE_WEAK_SYMBOLS */

#ifdef F77_NAME_UPPER
#define mpi_graph_get_ PMPI_GRAPH_GET
#elif defined(F77_NAME_LOWER_2USCORE)
#define mpi_graph_get_ pmpi_graph_get__
#elif !defined(F77_NAME_LOWER_USCORE)
#define mpi_graph_get_ pmpi_graph_get
#else
#define mpi_graph_get_ pmpi_graph_get_
#endif /* Test on name mapping */

#ifdef F77_USE_PMPI
/* This defines the routine that we call, which must be the PMPI version
   since we're renaming the Fortran entry as the pmpi version.  The MPI name
   must be undefined first to prevent any conflicts with previous renamings. */
#undef MPI_Graph_get
#define MPI_Graph_get PMPI_Graph_get 
#endif

#else

#ifdef F77_NAME_UPPER
#define mpi_graph_get_ MPI_GRAPH_GET
#elif defined(F77_NAME_LOWER_2USCORE)
#define mpi_graph_get_ mpi_graph_get__
#elif !defined(F77_NAME_LOWER_USCORE)
#define mpi_graph_get_ mpi_graph_get
/* Else leave name alone */
#endif


#endif /* MPICH_MPI_FROM_PMPI */

/* Prototypes for the Fortran interfaces */
#include "fproto.h"
FORT_DLL_SPEC void FORT_CALL mpi_graph_get_ ( MPI_Fint *v1, MPI_Fint *v2, MPI_Fint *v3, MPI_Fint v4[], MPI_Fint v5[], MPI_Fint *ierr ){
    *ierr = MPI_Graph_get( (MPI_Comm)(*v1), (int)*v2, (int)*v3, v4, v5 );
}
