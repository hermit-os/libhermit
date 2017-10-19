/* This is an implementation of the threads API of POSIX 1003.1-2001.
 *
 * --------------------------------------------------------------------------
 *
 *      Pthreads-embedded (PTE) - POSIX Threads Library for embedded systems
 *      Copyright(C) 2008 Jason Schmidlapp
 *
 *      Contact Email: jschmidlapp@users.sourceforge.net
 *
 *
#include <sched.h>

    /*
     * Generic handle type - intended to extend uniqueness beyond
     * that available with a simple pointer. It should scale for either
     * IA-32 or IA-64.
     */
    typedef struct
      {
        void * p;                   /* Pointer to actual object */
        unsigned int x;             /* Extra information - reuse count etc */
      } pte_handle_t;

    typedef pte_handle_t pthread_t;
    typedef struct pthread_attr_t_ * pthread_attr_t;
    typedef struct pthread_once_t_ pthread_once_t;
    typedef struct pthread_key_t_ * pthread_key_t;
    typedef struct pthread_mutex_t_ * pthread_mutex_t;
    typedef struct pthread_mutexattr_t_ * pthread_mutexattr_t;
    typedef struct pthread_cond_t_ * pthread_cond_t;
    typedef struct pthread_condattr_t_ * pthread_condattr_t;
    typedef struct pthread_rwlock_t_ * pthread_rwlock_t;
    typedef struct pthread_rwlockattr_t_ * pthread_rwlockattr_t;
    typedef struct pthread_spinlock_t_ * pthread_spinlock_t;
    typedef struct pthread_barrier_t_ * pthread_barrier_t;
    typedef struct pthread_barrierattr_t_ * pthread_barrierattr_t;

    /*
     * ====================
     * ====================
     * POSIX Threads
     * ====================
     * ====================
     */

    enum
    {
      /*
       * pthread_attr_{get,set}detachstate
       */
      PTHREAD_CREATE_JOINABLE       = 0,  /* Default */
      PTHREAD_CREATE_DETACHED       = 1,

      /*
       * pthread_attr_{get,set}inheritsched
       */
      PTHREAD_INHERIT_SCHED         = 0,
      PTHREAD_EXPLICIT_SCHED        = 1,  /* Default */

      /*
       * pthread_{get,set}scope
       */
      PTHREAD_SCOPE_PROCESS         = 0,
      PTHREAD_SCOPE_SYSTEM          = 1,  /* Default */
      PTHREAD_SCOPE_PROCESS_VFPU    = 2,  /* PSP specific */

      /*
       * pthread_setcancelstate paramters
       */
      PTHREAD_CANCEL_ENABLE         = 0,  /* Default */
      PTHREAD_CANCEL_DISABLE        = 1,

      /*
       * pthread_setcanceltype parameters
       */
      PTHREAD_CANCEL_ASYNCHRONOUS   = 0,
      PTHREAD_CANCEL_DEFERRED       = 1,  /* Default */

      /*
       * pthread_mutexattr_{get,set}pshared
       * pthread_condattr_{get,set}pshared
       */
      PTHREAD_PROCESS_PRIVATE       = 0,
      PTHREAD_PROCESS_SHARED        = 1,

      /*
       * pthread_barrier_wait
       */
      PTHREAD_BARRIER_SERIAL_THREAD = -1
    };

    /*
     * ====================
     * ====================
     * Cancelation
     * ====================
     * ====================
     */
#define PTHREAD_CANCELED       ((void *) -1)


    /*
     * ====================
     * ====================
     * Once Key
     * ====================
     * ====================
     */
#define PTHREAD_ONCE_INIT       { PTE_FALSE, 0, 0, 0}

    struct pthread_once_t_
      {
        int          state;
        void *       semaphore;
        int 		   numSemaphoreUsers;
        int          done;        /* indicates if user function has been executed */
//  void *       lock;
//  int          reserved1;
//  int          reserved2;
      };


    /*
     * ====================
     * ====================
     * Object initialisers
     * ====================
     * ====================
     */
#define PTHREAD_MUTEX_INITIALIZER ((pthread_mutex_t) -1)
#define PTHREAD_RECURSIVE_MUTEX_INITIALIZER ((pthread_mutex_t) -2)
#define PTHREAD_ERRORCHECK_MUTEX_INITIALIZER ((pthread_mutex_t) -3)

    /*
     * Compatibility with LinuxThreads
     */
#define PTHREAD_RECURSIVE_MUTEX_INITIALIZER_NP PTHREAD_RECURSIVE_MUTEX_INITIALIZER
#define PTHREAD_ERRORCHECK_MUTEX_INITIALIZER_NP PTHREAD_ERRORCHECK_MUTEX_INITIALIZER

#define PTHREAD_COND_INITIALIZER ((pthread_cond_t) -1)

#define PTHREAD_RWLOCK_INITIALIZER ((pthread_rwlock_t) -1)

#define PTHREAD_SPINLOCK_INITIALIZER ((pthread_spinlock_t) -1)


    /*
     * Mutex types.
     */
    enum
    {
      /* Compatibility with LinuxThreads */
      PTHREAD_MUTEX_FAST_NP,
      PTHREAD_MUTEX_RECURSIVE_NP,
      PTHREAD_MUTEX_ERRORCHECK_NP,
      PTHREAD_MUTEX_TIMED_NP = PTHREAD_MUTEX_FAST_NP,
      PTHREAD_MUTEX_ADAPTIVE_NP = PTHREAD_MUTEX_FAST_NP,
      /* For compatibility with POSIX */
      PTHREAD_MUTEX_NORMAL = PTHREAD_MUTEX_FAST_NP,
      PTHREAD_MUTEX_RECURSIVE = PTHREAD_MUTEX_RECURSIVE_NP,
      PTHREAD_MUTEX_ERRORCHECK = PTHREAD_MUTEX_ERRORCHECK_NP,
      PTHREAD_MUTEX_DEFAULT = PTHREAD_MUTEX_NORMAL
    };


    typedef struct pte_cleanup_t pte_cleanup_t;

    typedef void (*  pte_cleanup_callback_t)(void *);

    struct pte_cleanup_t
      {
        pte_cleanup_callback_t routine;
        void *arg;
        struct pte_cleanup_t *prev;
      };

#ifdef PTE_CLEANUP_C

    /*
     * C implementation of PThreads cancel cleanup
     */

#define pthread_cleanup_push( _rout, _arg ) \
        { \
            pte_cleanup_t     _cleanup; \
            \
            pte_push_cleanup( &_cleanup, (pte_cleanup_callback_t) (_rout), (_arg) ); \
 
#define pthread_cleanup_pop( _execute ) \
            (void) pte_pop_cleanup( _execute ); \
        }

#else /* PTE_CLEANUP_C */

#ifdef PTE_CLEANUP_CXX

    /*
    * C++ version of cancel cleanup.
    * - John E. Bossom.
    */

    class PThreadCleanup
      {
        /*
        * PThreadCleanup
        *
        * Purpose
        *      This class is a C++ helper class that is
        *      used to implement pthread_cleanup_push/
        *      pthread_cleanup_pop.
        *      The destructor of this class automatically
        *      pops the pushed cleanup routine regardless
        *      of how the code exits the scope
        *      (i.e. such as by an exception)
        */
        pte_cleanup_callback_t cleanUpRout;
        void    *       obj;
        int             executeIt;

      public:
        PThreadCleanup() :
            cleanUpRout( 0 ),
            obj( 0 ),
            executeIt( 0 )
            /*
            * No cleanup performed
            */
        {
        }

        PThreadCleanup(
          pte_cleanup_callback_t routine,
          void    *       arg ) :
            cleanUpRout( routine ),
            obj( arg ),
            executeIt( 1 )
            /*
            * Registers a cleanup routine for 'arg'
            */
        {
        }

        ~PThreadCleanup()
        {
          if ( executeIt )
            {
              (void) (*cleanUpRout)( obj );
            }
        }

        void execute( int exec )
        {
          executeIt = exec;
        }
      };

    /*
    * C++ implementation of PThreads cancel cleanup;
    * This implementation takes advantage of a helper
    * class who's destructor automatically calls the
    * cleanup routine if we exit our scope weirdly
    */
#define pthread_cleanup_push( _rout, _arg ) \
        { \
            PThreadCleanup  cleanup((pte_cleanup_callback_t)(_rout), \
                                    (void *) (_arg) );

#define pthread_cleanup_pop( _execute ) \
            cleanup.execute( _execute ); \
        }

#else

#error ERROR [__FILE__, line __LINE__]: Cleanup type undefined.

#endif /* PTE_CLEANUP_CXX */

#endif /* PTE_CLEANUP_C */

    /*
     * ===============
     * ===============
     * Methods
     * ===============
     * ===============
     */

    int  pthread_init (void);
    void  pthread_terminate (void);

    /*
     * PThread Attribute Functions
     */
    int  pthread_attr_init (pthread_attr_t * attr);

    int  pthread_attr_destroy (pthread_attr_t * attr);

    int  pthread_attr_getdetachstate (const pthread_attr_t * attr,
                                      int *detachstate);

    int  pthread_attr_getstackaddr (const pthread_attr_t * attr,
                                    void **stackaddr);

    int  pthread_attr_getstacksize (const pthread_attr_t * attr,
                                    size_t * stacksize);

    int  pthread_attr_setdetachstate (pthread_attr_t * attr,
                                      int detachstate);

    int  pthread_attr_setstackaddr (pthread_attr_t * attr,
                                    void *stackaddr);

    int  pthread_attr_setstacksize (pthread_attr_t * attr,
                                    size_t stacksize);

    int  pthread_attr_getschedparam (const pthread_attr_t *attr,
                                     struct sched_param *param);

    int  pthread_attr_setschedparam (pthread_attr_t *attr,
                                     const struct sched_param *param);

    int  pthread_attr_setschedpolicy (pthread_attr_t *,
                                      int);

    int  pthread_attr_getschedpolicy (pthread_attr_t *,
                                      int *);

    int  pthread_attr_setinheritsched(pthread_attr_t * attr,
                                      int inheritsched);

    int  pthread_attr_getinheritsched(pthread_attr_t * attr,
                                      int * inheritsched);

    int  pthread_attr_setscope (pthread_attr_t *,
                                int);

    int  pthread_attr_getscope (const pthread_attr_t *,
                                int *);

    /*
     * PThread Functions
     */
    int  pthread_create (pthread_t * tid,
                         const pthread_attr_t * attr,
                         void *(*start) (void *),
                         void *arg);

    int  pthread_detach (pthread_t tid);

    int  pthread_equal (pthread_t t1,
                        pthread_t t2);

    void  pthread_exit (void *value_ptr);

    int  pthread_join (pthread_t thread,
                       void **value_ptr);

    pthread_t  pthread_self (void);

    int  pthread_cancel (pthread_t thread);

    int  pthread_setcancelstate (int state,
                                 int *oldstate);

    int  pthread_setcanceltype (int type,
                                int *oldtype);

    void  pthread_testcancel (void);

    int  pthread_once (pthread_once_t * once_control,
                       void (*init_routine) (void));

#if PTE_LEVEL >= PTE_LEVEL_MAX
    pte_cleanup_t *  pte_pop_cleanup (int execute);

    void  pte_push_cleanup (pte_cleanup_t * cleanup,
                            void (*routine) (void *),
                            void *arg);
#endif /* PTE_LEVEL >= PTE_LEVEL_MAX */

    /*
     * Thread Specific Data Functions
     */
    int  pthread_key_create (pthread_key_t * key,
                             void (*destructor) (void *));

    int  pthread_key_delete (pthread_key_t key);

    int  pthread_setspecific (pthread_key_t key,
                              const void *value);

    void *  pthread_getspecific (pthread_key_t key);


    /*
     * Mutex Attribute Functions
     */
    int  pthread_mutexattr_init (pthread_mutexattr_t * attr);

    int  pthread_mutexattr_destroy (pthread_mutexattr_t * attr);

    int  pthread_mutexattr_getpshared (const pthread_mutexattr_t
                                       * attr,
                                       int *pshared);

    int  pthread_mutexattr_setpshared (pthread_mutexattr_t * attr,
                                       int pshared);

    int  pthread_mutexattr_settype (pthread_mutexattr_t * attr, int kind);
    int  pthread_mutexattr_gettype (pthread_mutexattr_t * attr, int *kind);

    /*
     * Barrier Attribute Functions
     */
    int  pthread_barrierattr_init (pthread_barrierattr_t * attr);

    int  pthread_barrierattr_destroy (pthread_barrierattr_t * attr);

    int  pthread_barrierattr_getpshared (const pthread_barrierattr_t
                                         * attr,
                                         int *pshared);

    int  pthread_barrierattr_setpshared (pthread_barrierattr_t * attr,
                                         int pshared);

    /*
     * Mutex Functions
     */
    int  pthread_mutex_init (pthread_mutex_t * mutex,
                             const pthread_mutexattr_t * attr);

    int  pthread_mutex_destroy (pthread_mutex_t * mutex);

    int  pthread_mutex_lock (pthread_mutex_t * mutex);

    int  pthread_mutex_timedlock(pthread_mutex_t *mutex,
                                 const struct timespec *abstime);

    int  pthread_mutex_trylock (pthread_mutex_t * mutex);

    int  pthread_mutex_unlock (pthread_mutex_t * mutex);

    /*
     * Spinlock Functions
     */
    int  pthread_spin_init (pthread_spinlock_t * lock, int pshared);

    int  pthread_spin_destroy (pthread_spinlock_t * lock);

    int  pthread_spin_lock (pthread_spinlock_t * lock);

    int  pthread_spin_trylock (pthread_spinlock_t * lock);

    int  pthread_spin_unlock (pthread_spinlock_t * lock);

    /*
     * Barrier Functions
     */
    int  pthread_barrier_init (pthread_barrier_t * barrier,
                               const pthread_barrierattr_t * attr,
                               unsigned int count);

    int  pthread_barrier_destroy (pthread_barrier_t * barrier);

    int  pthread_barrier_wait (pthread_barrier_t * barrier);

    /*
     * Condition Variable Attribute Functions
     */
    int  pthread_condattr_init (pthread_condattr_t * attr);

    int  pthread_condattr_destroy (pthread_condattr_t * attr);

    int  pthread_condattr_getpshared (const pthread_condattr_t * attr,
                                      int *pshared);

    int  pthread_condattr_setpshared (pthread_condattr_t * attr,
                                      int pshared);

    /*
     * Condition Variable Functions
     */
    int  pthread_cond_init (pthread_cond_t * cond,
                            const pthread_condattr_t * attr);

    int  pthread_cond_destroy (pthread_cond_t * cond);

    int  pthread_cond_wait (pthread_cond_t * cond,
                            pthread_mutex_t * mutex);

    int  pthread_cond_timedwait (pthread_cond_t * cond,
                                 pthread_mutex_t * mutex,
                                 const struct timespec *abstime);

    int  pthread_cond_signal (pthread_cond_t * cond);

    int  pthread_cond_broadcast (pthread_cond_t * cond);

    /*
     * Scheduling
     */
    int  pthread_setschedparam (pthread_t thread,
                                int policy,
                                const struct sched_param *param);

    int  pthread_getschedparam (pthread_t thread,
                                int *policy,
                                struct sched_param *param);

    int  pthread_setconcurrency (int);

    int  pthread_getconcurrency (void);

    /*
     * Read-Write Lock Functions
     */
    int  pthread_rwlock_init(pthread_rwlock_t *lock,
                             const pthread_rwlockattr_t *attr);

    int  pthread_rwlock_destroy(pthread_rwlock_t *lock);

    int  pthread_rwlock_tryrdlock(pthread_rwlock_t *);

    int  pthread_rwlock_trywrlock(pthread_rwlock_t *);

    int  pthread_rwlock_rdlock(pthread_rwlock_t *lock);

    int  pthread_rwlock_timedrdlock(pthread_rwlock_t *lock,
                                    const struct timespec *abstime);

    int  pthread_rwlock_wrlock(pthread_rwlock_t *lock);

    int  pthread_rwlock_timedwrlock(pthread_rwlock_t *lock,
                                    const struct timespec *abstime);

    int  pthread_rwlock_unlock(pthread_rwlock_t *lock);

    int  pthread_rwlockattr_init (pthread_rwlockattr_t * attr);

    int  pthread_rwlockattr_destroy (pthread_rwlockattr_t * attr);

    int  pthread_rwlockattr_getpshared (const pthread_rwlockattr_t * attr,
                                        int *pshared);

    int  pthread_rwlockattr_setpshared (pthread_rwlockattr_t * attr,
                                        int pshared);

#if (PTE_LEVEL >= PTE_LEVEL_MAX - 1) || defined(__hermit__)

    /*
     * Signal Functions. Should be defined in <signal.h> but we might
     * already have signal.h that don't define these.
     */
    int  pthread_kill(pthread_t thread, int sig);
#endif

#if PTE_LEVEL >= PTE_LEVEL_MAX - 1
    /*
     * Non-portable functions
     */

    /*
     * Compatibility with Linux.
     */
    int  pthread_mutexattr_setkind_np(pthread_mutexattr_t * attr,
                                      int kind);
    int  pthread_mutexattr_getkind_np(pthread_mutexattr_t * attr,
                                      int *kind);

    /*
     * Possibly supported by other POSIX threads implementations
     */
    int  pthread_delay_np (struct timespec * interval);
    int  pthread_num_processors_np(void);

    /*
     * Register a system time change with the library.
     * Causes the library to perform various functions
     * in response to the change. Should be called whenever
     * the application's top level window receives a
     * WM_TIMECHANGE message. It can be passed directly to
     * pthread_create() as a new thread if desired.
     */
    void *  pthread_timechange_handler_np(void *);

#endif /*PTE_LEVEL >= PTE_LEVEL_MAX - 1 */

#if PTE_LEVEL >= PTE_LEVEL_MAX



#endif /* PTE_LEVEL >= PTE_LEVEL_MAX */

    /*
     * Some compiler environments don't define some things.
     */
#  define _ftime ftime
#  define _timeb timeb

#ifdef __cplusplus

    /*
     * Internal exceptions
     */
    class pte_exception {};
    class pte_exception_cancel : public pte_exception {};
    class pte_exception_exit   : public pte_exception {};

    /* Operator to be compatible to libstd++ */
    inline bool operator<(pte_handle_t const& l, pte_handle_t const& r)
    {
        return ((size_t) l.p) < ((size_t) r.p);
    }

    /* Operator to be compatible to libstd++ */
    inline bool operator==(pte_handle_t const& l, pte_handle_t const& r)
    {
        return ((size_t) l.p) == ((size_t) r.p);
    }
#endif


#ifdef PTE_CXX_EXCEPTIONS

    /*
     * Redefine the C++ catch keyword to ensure that applications
     * propagate our internal exceptions up to the library's internal handlers.
     */
#define catch( E ) \
        catch( pte_exception & ) { throw; } \
        catch( E )

#endif /* ! PTE_CXX_EXCEPTIONS */

#undef PTE_LEVEL
#undef PTE_LEVEL_MAX

#endif /* PTHREAD_H */
