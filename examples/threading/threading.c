#include "threading.h"
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <errno.h>

// Optional: use these functions to add debug or error prints to your application
#define DEBUG_LOG(msg,...)
//#define DEBUG_LOG(msg,...) printf("threading: " msg "\n" , ##__VA_ARGS__)
#define ERROR_LOG(msg,...) printf("threading ERROR: " msg "\n" , ##__VA_ARGS__)

void* threadfunc(void* thread_param)
{
    // TODO: wait, obtain mutex, wait, release mutex as described by thread_data structure
    // hint: use a cast like the one below to obtain thread arguments from your parameter
    struct thread_data* thread_func_args = (struct thread_data *) thread_param;
    thread_func_args->thread_complete_success = true;
    
    usleep(thread_func_args->thread_wait_to_obtain_ms*1000);
    

    if(pthread_mutex_lock(thread_func_args->thread_mutex))
    {
    	perror("pthread_mutex_lock");
    	thread_func_args->thread_complete_success = false;
    }
    usleep(thread_func_args->thread_wait_to_release_ms*1000);
    if(pthread_mutex_unlock(thread_func_args->thread_mutex))
    {
    	perror("pthread_mutex_unlock");
    	thread_func_args->thread_complete_success = false;
    }    
    
    return thread_func_args;
}


bool start_thread_obtaining_mutex(pthread_t *thread, pthread_mutex_t *mutex,int wait_to_obtain_ms, int wait_to_release_ms)
{
    /**
     * TODO: allocate memory for thread_data, setup mutex and wait arguments, pass thread_data to created thread
     * using threadfunc() as entry point.
     *
     * return true if successful.
     *
     * See implementation details in threading.h file comment block
     */
     bool LocalRet = false;
     
     
     struct thread_data* PassedDataToThread = malloc(sizeof(struct thread_data));
     if (PassedDataToThread == NULL) 
     {
        return false; // Memory allocation failed
     }
     PassedDataToThread->thread_mutex = mutex;
     PassedDataToThread->thread_wait_to_obtain_ms = wait_to_obtain_ms;
     PassedDataToThread->thread_wait_to_release_ms = wait_to_release_ms;


     if (pthread_create(thread,NULL,threadfunc,(void *)PassedDataToThread))
     {
	errno = LocalRet;
	perror("pthread_create");
	return false;
     }
     else
     {
     	return true;
     }
}

