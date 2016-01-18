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
extern FORT_DLL_SPEC void FORT_CALL MPI_WIN_GET_NAME( MPI_Fint *, char * FORT_MIXED_LEN_DECL, MPI_Fint *, MPI_Fint * FORT_END_LEN_DECL );
extern FORT_DLL_SPEC void FORT_CALL mpi_win_get_name__( MPI_Fint *, char * FORT_MIXED_LEN_DECL, MPI_Fint *, MPI_Fint * FORT_END_LEN_DECL );
extern FORT_DLL_SPEC void FORT_CALL mpi_win_get_name( MPI_Fint *, char * FORT_MIXED_LEN_DECL, MPI_Fint *, MPI_Fint * FORT_END_LEN_DECL );
extern FORT_DLL_SPEC void FORT_CALL mpi_win_get_name_( MPI_Fint *, char * FORT_MIXED_LEN_DECL, MPI_Fint *, MPI_Fint * FORT_END_LEN_DECL );

#if defined(F77_NAME_UPPER)
#pragma weak MPI_WIN_GET_NAME = PMPI_WIN_GET_NAME
#pragma weak mpi_win_get_name__ = PMPI_WIN_GET_NAME
#pragma weak mpi_win_get_name_ = PMPI_WIN_GET_NAME
#pragma weak mpi_win_get_name = PMPI_WIN_GET_NAME
#elif defined(F77_NAME_LOWER_2USCORE)
#pragma weak MPI_WIN_GET_NAME = pmpi_win_get_name__
#pragma weak mpi_win_get_name__ = pmpi_win_get_name__
#pragma weak mpi_win_get_name_ = pmpi_win_get_name__
#pragma weak mpi_win_get_name = pmpi_win_get_name__
#elif defined(F77_NAME_LOWER_USCORE)
#pragma weak MPI_WIN_GET_NAME = pmpi_win_get_name_
#pragma weak mpi_win_get_name__ = pmpi_win_get_name_
#pragma weak mpi_win_get_name_ = pmpi_win_get_name_
#pragma weak mpi_win_get_name = pmpi_win_get_name_
#else
#pragma weak MPI_WIN_GET_NAME = pmpi_win_get_name
#pragma weak mpi_win_get_name__ = pmpi_win_get_name
#pragma weak mpi_win_get_name_ = pmpi_win_get_name
#pragma weak mpi_win_get_name = pmpi_win_get_name
#endif



#elif defined(HAVE_PRAGMA_WEAK)

#if defined(F77_NAME_UPPER)
extern FORT_DLL_SPEC void FORT_CALL MPI_WIN_GET_NAME( MPI_Fint *, char * FORT_MIXED_LEN_DECL, MPI_Fint *, MPI_Fint * FORT_END_LEN_DECL );

#pragma weak MPI_WIN_GET_NAME = PMPI_WIN_GET_NAME
#elif defined(F77_NAME_LOWER_2USCORE)
extern FORT_DLL_SPEC void FORT_CALL mpi_win_get_name__( MPI_Fint *, char * FORT_MIXED_LEN_DECL, MPI_Fint *, MPI_Fint * FORT_END_LEN_DECL );

#pragma weak mpi_win_get_name__ = pmpi_win_get_name__
#elif !defined(F77_NAME_LOWER_USCORE)
extern FORT_DLL_SPEC void FORT_CALL mpi_win_get_name( MPI_Fint *, char * FORT_MIXED_LEN_DECL, MPI_Fint *, MPI_Fint * FORT_END_LEN_DECL );

#pragma weak mpi_win_get_name = pmpi_win_get_name
#else
extern FORT_DLL_SPEC void FORT_CALL mpi_win_get_name_( MPI_Fint *, char * FORT_MIXED_LEN_DECL, MPI_Fint *, MPI_Fint * FORT_END_LEN_DECL );

#pragma weak mpi_win_get_name_ = pmpi_win_get_name_
#endif

#elif defined(HAVE_PRAGMA_HP_SEC_DEF)
#if defined(F77_NAME_UPPER)
#pragma _HP_SECONDARY_DEF PMPI_WIN_GET_NAME  MPI_WIN_GET_NAME
#elif defined(F77_NAME_LOWER_2USCORE)
#pragma _HP_SECONDARY_DEF pmpi_win_get_name__  mpi_win_get_name__
#elif !defined(F77_NAME_LOWER_USCORE)
#pragma _HP_SECONDARY_DEF pmpi_win_get_name  mpi_win_get_name
#else
#pragma _HP_SECONDARY_DEF pmpi_win_get_name_  mpi_win_get_name_
#endif

#elif defined(HAVE_PRAGMA_CRI_DUP)
#if defined(F77_NAME_UPPER)
#pragma _CRI duplicate MPI_WIN_GET_NAME as PMPI_WIN_GET_NAME
#elif defined(F77_NAME_LOWER_2USCORE)
#pragma _CRI duplicate mpi_win_get_name__ as pmpi_win_get_name__
#elif !defined(F77_NAME_LOWER_USCORE)
#pragma _CRI duplicate mpi_win_get_name as pmpi_win_get_name
#else
#pragma _CRI duplicate mpi_win_get_name_ as pmpi_win_get_name_
#endif

#elif defined(HAVE_WEAK_ATTRIBUTE)
#if defined(F77_NAME_UPPER)
extern FORT_DLL_SPEC void FORT_CALL MPI_WIN_GET_NAME( MPI_Fint *, char * FORT_MIXED_LEN_DECL, MPI_Fint *, MPI_Fint * FORT_END_LEN_DECL ) __attribute__((weak,alias("PMPI_WIN_GET_NAME")));
extern FORT_DLL_SPEC void FORT_CALL mpi_win_get_name__( MPI_Fint *, char * FORT_MIXED_LEN_DECL, MPI_Fint *, MPI_Fint * FORT_END_LEN_DECL ) __attribute__((weak,alias("PMPI_WIN_GET_NAME")));
extern FORT_DLL_SPEC void FORT_CALL mpi_win_get_name_( MPI_Fint *, char * FORT_MIXED_LEN_DECL, MPI_Fint *, MPI_Fint * FORT_END_LEN_DECL ) __attribute__((weak,alias("PMPI_WIN_GET_NAME")));
extern FORT_DLL_SPEC void FORT_CALL mpi_win_get_name( MPI_Fint *, char * FORT_MIXED_LEN_DECL, MPI_Fint *, MPI_Fint * FORT_END_LEN_DECL ) __attribute__((weak,alias("PMPI_WIN_GET_NAME")));

#elif defined(F77_NAME_LOWER_2USCORE)
extern FORT_DLL_SPEC void FORT_CALL MPI_WIN_GET_NAME( MPI_Fint *, char * FORT_MIXED_LEN_DECL, MPI_Fint *, MPI_Fint * FORT_END_LEN_DECL ) __attribute__((weak,alias("pmpi_win_get_name__")));
extern FORT_DLL_SPEC void FORT_CALL mpi_win_get_name__( MPI_Fint *, char * FORT_MIXED_LEN_DECL, MPI_Fint *, MPI_Fint * FORT_END_LEN_DECL ) __attribute__((weak,alias("pmpi_win_get_name__")));
extern FORT_DLL_SPEC void FORT_CALL mpi_win_get_name_( MPI_Fint *, char * FORT_MIXED_LEN_DECL, MPI_Fint *, MPI_Fint * FORT_END_LEN_DECL ) __attribute__((weak,alias("pmpi_win_get_name__")));
extern FORT_DLL_SPEC void FORT_CALL mpi_win_get_name( MPI_Fint *, char * FORT_MIXED_LEN_DECL, MPI_Fint *, MPI_Fint * FORT_END_LEN_DECL ) __attribute__((weak,alias("pmpi_win_get_name__")));

#elif defined(F77_NAME_LOWER_USCORE)
extern FORT_DLL_SPEC void FORT_CALL MPI_WIN_GET_NAME( MPI_Fint *, char * FORT_MIXED_LEN_DECL, MPI_Fint *, MPI_Fint * FORT_END_LEN_DECL ) __attribute__((weak,alias("pmpi_win_get_name_")));
extern FORT_DLL_SPEC void FORT_CALL mpi_win_get_name__( MPI_Fint *, char * FORT_MIXED_LEN_DECL, MPI_Fint *, MPI_Fint * FORT_END_LEN_DECL ) __attribute__((weak,alias("pmpi_win_get_name_")));
extern FORT_DLL_SPEC void FORT_CALL mpi_win_get_name_( MPI_Fint *, char * FORT_MIXED_LEN_DECL, MPI_Fint *, MPI_Fint * FORT_END_LEN_DECL ) __attribute__((weak,alias("pmpi_win_get_name_")));
extern FORT_DLL_SPEC void FORT_CALL mpi_win_get_name( MPI_Fint *, char * FORT_MIXED_LEN_DECL, MPI_Fint *, MPI_Fint * FORT_END_LEN_DECL ) __attribute__((weak,alias("pmpi_win_get_name_")));

#else
extern FORT_DLL_SPEC void FORT_CALL MPI_WIN_GET_NAME( MPI_Fint *, char * FORT_MIXED_LEN_DECL, MPI_Fint *, MPI_Fint * FORT_END_LEN_DECL ) __attribute__((weak,alias("pmpi_win_get_name")));
extern FORT_DLL_SPEC void FORT_CALL mpi_win_get_name__( MPI_Fint *, char * FORT_MIXED_LEN_DECL, MPI_Fint *, MPI_Fint * FORT_END_LEN_DECL ) __attribute__((weak,alias("pmpi_win_get_name")));
extern FORT_DLL_SPEC void FORT_CALL mpi_win_get_name_( MPI_Fint *, char * FORT_MIXED_LEN_DECL, MPI_Fint *, MPI_Fint * FORT_END_LEN_DECL ) __attribute__((weak,alias("pmpi_win_get_name")));
extern FORT_DLL_SPEC void FORT_CALL mpi_win_get_name( MPI_Fint *, char * FORT_MIXED_LEN_DECL, MPI_Fint *, MPI_Fint * FORT_END_LEN_DECL ) __attribute__((weak,alias("pmpi_win_get_name")));

#endif
#endif /* HAVE_PRAGMA_WEAK */
#endif /* USE_WEAK_SYMBOLS */
/* End MPI profiling block */


/* These definitions are used only for generating the Fortran wrappers */
#if defined(USE_WEAK_SYMBOLS) && defined(USE_ONLY_MPI_NAMES)
#if defined(HAVE_MULTIPLE_PRAGMA_WEAK)
extern FORT_DLL_SPEC void FORT_CALL MPI_WIN_GET_NAME( MPI_Fint *, char * FORT_MIXED_LEN_DECL, MPI_Fint *, MPI_Fint * FORT_END_LEN_DECL );
extern FORT_DLL_SPEC void FORT_CALL mpi_win_get_name__( MPI_Fint *, char * FORT_MIXED_LEN_DECL, MPI_Fint *, MPI_Fint * FORT_END_LEN_DECL );
extern FORT_DLL_SPEC void FORT_CALL mpi_win_get_name( MPI_Fint *, char * FORT_MIXED_LEN_DECL, MPI_Fint *, MPI_Fint * FORT_END_LEN_DECL );
extern FORT_DLL_SPEC void FORT_CALL mpi_win_get_name_( MPI_Fint *, char * FORT_MIXED_LEN_DECL, MPI_Fint *, MPI_Fint * FORT_END_LEN_DECL );

#if defined(F77_NAME_UPPER)
#pragma weak mpi_win_get_name__ = MPI_WIN_GET_NAME
#pragma weak mpi_win_get_name_ = MPI_WIN_GET_NAME
#pragma weak mpi_win_get_name = MPI_WIN_GET_NAME
#elif defined(F77_NAME_LOWER_2USCORE)
#pragma weak MPI_WIN_GET_NAME = mpi_win_get_name__
#pragma weak mpi_win_get_name_ = mpi_win_get_name__
#pragma weak mpi_win_get_name = mpi_win_get_name__
#elif defined(F77_NAME_LOWER_USCORE)
#pragma weak MPI_WIN_GET_NAME = mpi_win_get_name_
#pragma weak mpi_win_get_name__ = mpi_win_get_name_
#pragma weak mpi_win_get_name = mpi_win_get_name_
#else
#pragma weak MPI_WIN_GET_NAME = mpi_win_get_name
#pragma weak mpi_win_get_name__ = mpi_win_get_name
#pragma weak mpi_win_get_name_ = mpi_win_get_name
#endif
#elif defined(HAVE_WEAK_ATTRIBUTE)
#if defined(F77_NAME_UPPER)
extern FORT_DLL_SPEC void FORT_CALL MPI_WIN_GET_NAME( MPI_Fint *, char * FORT_MIXED_LEN_DECL, MPI_Fint *, MPI_Fint * FORT_END_LEN_DECL );
extern FORT_DLL_SPEC void FORT_CALL mpi_win_get_name__( MPI_Fint *, char * FORT_MIXED_LEN_DECL, MPI_Fint *, MPI_Fint * FORT_END_LEN_DECL ) __attribute__((weak,alias("MPI_WIN_GET_NAME")));
extern FORT_DLL_SPEC void FORT_CALL mpi_win_get_name_( MPI_Fint *, char * FORT_MIXED_LEN_DECL, MPI_Fint *, MPI_Fint * FORT_END_LEN_DECL ) __attribute__((weak,alias("MPI_WIN_GET_NAME")));
extern FORT_DLL_SPEC void FORT_CALL mpi_win_get_name( MPI_Fint *, char * FORT_MIXED_LEN_DECL, MPI_Fint *, MPI_Fint * FORT_END_LEN_DECL ) __attribute__((weak,alias("MPI_WIN_GET_NAME")));

#elif defined(F77_NAME_LOWER_2USCORE)
extern FORT_DLL_SPEC void FORT_CALL MPI_WIN_GET_NAME( MPI_Fint *, char * FORT_MIXED_LEN_DECL, MPI_Fint *, MPI_Fint * FORT_END_LEN_DECL ) __attribute__((weak,alias("mpi_win_get_name__")));
extern FORT_DLL_SPEC void FORT_CALL mpi_win_get_name__( MPI_Fint *, char * FORT_MIXED_LEN_DECL, MPI_Fint *, MPI_Fint * FORT_END_LEN_DECL );
extern FORT_DLL_SPEC void FORT_CALL mpi_win_get_name_( MPI_Fint *, char * FORT_MIXED_LEN_DECL, MPI_Fint *, MPI_Fint * FORT_END_LEN_DECL ) __attribute__((weak,alias("mpi_win_get_name__")));
extern FORT_DLL_SPEC void FORT_CALL mpi_win_get_name( MPI_Fint *, char * FORT_MIXED_LEN_DECL, MPI_Fint *, MPI_Fint * FORT_END_LEN_DECL ) __attribute__((weak,alias("mpi_win_get_name__")));

#elif defined(F77_NAME_LOWER_USCORE)
extern FORT_DLL_SPEC void FORT_CALL MPI_WIN_GET_NAME( MPI_Fint *, char * FORT_MIXED_LEN_DECL, MPI_Fint *, MPI_Fint * FORT_END_LEN_DECL ) __attribute__((weak,alias("mpi_win_get_name_")));
extern FORT_DLL_SPEC void FORT_CALL mpi_win_get_name__( MPI_Fint *, char * FORT_MIXED_LEN_DECL, MPI_Fint *, MPI_Fint * FORT_END_LEN_DECL ) __attribute__((weak,alias("mpi_win_get_name_")));
extern FORT_DLL_SPEC void FORT_CALL mpi_win_get_name_( MPI_Fint *, char * FORT_MIXED_LEN_DECL, MPI_Fint *, MPI_Fint * FORT_END_LEN_DECL );
extern FORT_DLL_SPEC void FORT_CALL mpi_win_get_name( MPI_Fint *, char * FORT_MIXED_LEN_DECL, MPI_Fint *, MPI_Fint * FORT_END_LEN_DECL ) __attribute__((weak,alias("mpi_win_get_name_")));

#else
extern FORT_DLL_SPEC void FORT_CALL MPI_WIN_GET_NAME( MPI_Fint *, char * FORT_MIXED_LEN_DECL, MPI_Fint *, MPI_Fint * FORT_END_LEN_DECL ) __attribute__((weak,alias("mpi_win_get_name")));
extern FORT_DLL_SPEC void FORT_CALL mpi_win_get_name__( MPI_Fint *, char * FORT_MIXED_LEN_DECL, MPI_Fint *, MPI_Fint * FORT_END_LEN_DECL ) __attribute__((weak,alias("mpi_win_get_name")));
extern FORT_DLL_SPEC void FORT_CALL mpi_win_get_name_( MPI_Fint *, char * FORT_MIXED_LEN_DECL, MPI_Fint *, MPI_Fint * FORT_END_LEN_DECL ) __attribute__((weak,alias("mpi_win_get_name")));
extern FORT_DLL_SPEC void FORT_CALL mpi_win_get_name( MPI_Fint *, char * FORT_MIXED_LEN_DECL, MPI_Fint *, MPI_Fint * FORT_END_LEN_DECL );

#endif
#endif

#endif

/* Map the name to the correct form */
#ifndef MPICH_MPI_FROM_PMPI
#if defined(USE_WEAK_SYMBOLS)
#if defined(HAVE_MULTIPLE_PRAGMA_WEAK)
/* Define the weak versions of the PMPI routine*/
#ifndef F77_NAME_UPPER
extern FORT_DLL_SPEC void FORT_CALL PMPI_WIN_GET_NAME( MPI_Fint *, char * FORT_MIXED_LEN_DECL, MPI_Fint *, MPI_Fint * FORT_END_LEN_DECL );
#endif
#ifndef F77_NAME_LOWER_2USCORE
extern FORT_DLL_SPEC void FORT_CALL pmpi_win_get_name__( MPI_Fint *, char * FORT_MIXED_LEN_DECL, MPI_Fint *, MPI_Fint * FORT_END_LEN_DECL );
#endif
#ifndef F77_NAME_LOWER_USCORE
extern FORT_DLL_SPEC void FORT_CALL pmpi_win_get_name_( MPI_Fint *, char * FORT_MIXED_LEN_DECL, MPI_Fint *, MPI_Fint * FORT_END_LEN_DECL );
#endif
#ifndef F77_NAME_LOWER
extern FORT_DLL_SPEC void FORT_CALL pmpi_win_get_name( MPI_Fint *, char * FORT_MIXED_LEN_DECL, MPI_Fint *, MPI_Fint * FORT_END_LEN_DECL );

#endif

#if defined(F77_NAME_UPPER)
#pragma weak pmpi_win_get_name__ = PMPI_WIN_GET_NAME
#pragma weak pmpi_win_get_name_ = PMPI_WIN_GET_NAME
#pragma weak pmpi_win_get_name = PMPI_WIN_GET_NAME
#elif defined(F77_NAME_LOWER_2USCORE)
#pragma weak PMPI_WIN_GET_NAME = pmpi_win_get_name__
#pragma weak pmpi_win_get_name_ = pmpi_win_get_name__
#pragma weak pmpi_win_get_name = pmpi_win_get_name__
#elif defined(F77_NAME_LOWER_USCORE)
#pragma weak PMPI_WIN_GET_NAME = pmpi_win_get_name_
#pragma weak pmpi_win_get_name__ = pmpi_win_get_name_
#pragma weak pmpi_win_get_name = pmpi_win_get_name_
#else
#pragma weak PMPI_WIN_GET_NAME = pmpi_win_get_name
#pragma weak pmpi_win_get_name__ = pmpi_win_get_name
#pragma weak pmpi_win_get_name_ = pmpi_win_get_name
#endif /* Test on name mapping */

#elif defined(HAVE_WEAK_ATTRIBUTE)
#if defined(F77_NAME_UPPER)
extern FORT_DLL_SPEC void FORT_CALL pmpi_win_get_name__( MPI_Fint *, char * FORT_MIXED_LEN_DECL, MPI_Fint *, MPI_Fint * FORT_END_LEN_DECL ) __attribute__((weak,alias("PMPI_WIN_GET_NAME")));
extern FORT_DLL_SPEC void FORT_CALL pmpi_win_get_name_( MPI_Fint *, char * FORT_MIXED_LEN_DECL, MPI_Fint *, MPI_Fint * FORT_END_LEN_DECL ) __attribute__((weak,alias("PMPI_WIN_GET_NAME")));
extern FORT_DLL_SPEC void FORT_CALL pmpi_win_get_name( MPI_Fint *, char * FORT_MIXED_LEN_DECL, MPI_Fint *, MPI_Fint * FORT_END_LEN_DECL ) __attribute__((weak,alias("PMPI_WIN_GET_NAME")));

#elif defined(F77_NAME_LOWER_2USCORE)
extern FORT_DLL_SPEC void FORT_CALL PMPI_WIN_GET_NAME( MPI_Fint *, char * FORT_MIXED_LEN_DECL, MPI_Fint *, MPI_Fint * FORT_END_LEN_DECL ) __attribute__((weak,alias("pmpi_win_get_name__")));
extern FORT_DLL_SPEC void FORT_CALL pmpi_win_get_name_( MPI_Fint *, char * FORT_MIXED_LEN_DECL, MPI_Fint *, MPI_Fint * FORT_END_LEN_DECL ) __attribute__((weak,alias("pmpi_win_get_name__")));
extern FORT_DLL_SPEC void FORT_CALL pmpi_win_get_name( MPI_Fint *, char * FORT_MIXED_LEN_DECL, MPI_Fint *, MPI_Fint * FORT_END_LEN_DECL ) __attribute__((weak,alias("pmpi_win_get_name__")));

#elif defined(F77_NAME_LOWER_USCORE)
extern FORT_DLL_SPEC void FORT_CALL PMPI_WIN_GET_NAME( MPI_Fint *, char * FORT_MIXED_LEN_DECL, MPI_Fint *, MPI_Fint * FORT_END_LEN_DECL ) __attribute__((weak,alias("pmpi_win_get_name_")));
extern FORT_DLL_SPEC void FORT_CALL pmpi_win_get_name__( MPI_Fint *, char * FORT_MIXED_LEN_DECL, MPI_Fint *, MPI_Fint * FORT_END_LEN_DECL ) __attribute__((weak,alias("pmpi_win_get_name_")));
extern FORT_DLL_SPEC void FORT_CALL pmpi_win_get_name( MPI_Fint *, char * FORT_MIXED_LEN_DECL, MPI_Fint *, MPI_Fint * FORT_END_LEN_DECL ) __attribute__((weak,alias("pmpi_win_get_name_")));

#else
extern FORT_DLL_SPEC void FORT_CALL PMPI_WIN_GET_NAME( MPI_Fint *, char * FORT_MIXED_LEN_DECL, MPI_Fint *, MPI_Fint * FORT_END_LEN_DECL ) __attribute__((weak,alias("pmpi_win_get_name")));
extern FORT_DLL_SPEC void FORT_CALL pmpi_win_get_name__( MPI_Fint *, char * FORT_MIXED_LEN_DECL, MPI_Fint *, MPI_Fint * FORT_END_LEN_DECL ) __attribute__((weak,alias("pmpi_win_get_name")));
extern FORT_DLL_SPEC void FORT_CALL pmpi_win_get_name_( MPI_Fint *, char * FORT_MIXED_LEN_DECL, MPI_Fint *, MPI_Fint * FORT_END_LEN_DECL ) __attribute__((weak,alias("pmpi_win_get_name")));

#endif /* Test on name mapping */
#endif /* HAVE_MULTIPLE_PRAGMA_WEAK */
#endif /* USE_WEAK_SYMBOLS */

#ifdef F77_NAME_UPPER
#define mpi_win_get_name_ PMPI_WIN_GET_NAME
#elif defined(F77_NAME_LOWER_2USCORE)
#define mpi_win_get_name_ pmpi_win_get_name__
#elif !defined(F77_NAME_LOWER_USCORE)
#define mpi_win_get_name_ pmpi_win_get_name
#else
#define mpi_win_get_name_ pmpi_win_get_name_
#endif /* Test on name mapping */

#ifdef F77_USE_PMPI
/* This defines the routine that we call, which must be the PMPI version
   since we're renaming the Fortran entry as the pmpi version.  The MPI name
   must be undefined first to prevent any conflicts with previous renamings. */
#undef MPI_Win_get_name
#define MPI_Win_get_name PMPI_Win_get_name 
#endif

#else

#ifdef F77_NAME_UPPER
#define mpi_win_get_name_ MPI_WIN_GET_NAME
#elif defined(F77_NAME_LOWER_2USCORE)
#define mpi_win_get_name_ mpi_win_get_name__
#elif !defined(F77_NAME_LOWER_USCORE)
#define mpi_win_get_name_ mpi_win_get_name
/* Else leave name alone */
#endif


#endif /* MPICH_MPI_FROM_PMPI */

/* Prototypes for the Fortran interfaces */
#include "fproto.h"
FORT_DLL_SPEC void FORT_CALL mpi_win_get_name_ ( MPI_Fint *v1, char *v2 FORT_MIXED_LEN(d2), MPI_Fint *v3, MPI_Fint *ierr FORT_END_LEN(d2) ){
    char *p2;
    p2 = (char *)MPIU_Malloc( d2 + 1 );
    *ierr = MPI_Win_get_name( (MPI_Win)*v1, p2, v3 );

    if (!*ierr) {char *p = v2, *pc=p2;
        while (*pc) {*p++ = *pc++;}
        while ((p-v2) < d2) { *p++ = ' '; }
    }
    MPIU_Free( p2 );
}
