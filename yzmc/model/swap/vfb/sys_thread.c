/*---------------------------------------------------------------------
 * File:  sys_thread.c
 *
 * Description:
 * This file provides implementation of multi-tasking/threading
 * capabilities allowing classes/subsystems to run in different
 * threads on a multi-tasking/threading OS/RTOS.
 *
 * your copyright statement can go here (from te_copyright.body)
 *-------------------------------------------------------------------*/

#include "swap_sys_types.h"

static u1_t threadnumber[ NUM_OF_TOTAL_THREADS ];

/*
 * Initialize those structures that need to be set up once at system
 * bring-up time.
 */
void Escher_InitializeThreading( void )
{
  u1_t i;
  for ( i = 0; i < NUM_OF_TOTAL_THREADS; i++ ) {
    threadnumber[ i ] = i;
  }
}

/*
 * Obtain a resource lock so that this thread has mutually exclusive
 * access.
 */
void Escher_mutex_lock( const u1_t flavor )
{
}

/*
 * Release a resource lock that was obtained with the lock method.
 */
void Escher_mutex_unlock( const u1_t flavor )
{
}

/*
 * Go into a non-busy wait state waiting on someone to wake us
 * up with the nonbusy_wake method.
 */
void Escher_nonbusy_wait( const u1_t thread )
{
}

/*
 * Wake up a thread that went to sleep waiting for something to happen.
 */
void Escher_nonbusy_wake( const u1_t thread )
{
}

/*
 * Create and spin off a task/thread to run the input routine.
 */
void Escher_thread_create( void *(routine)(void *), const u1_t i )
{
}

/*
 * Cleanup the structures initialized in Escher_InitializeThreading.
 */
void Escher_thread_shutdown( void )
{
}
