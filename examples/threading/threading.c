#include "threading.h"
#include <bits/pthreadtypes.h>
#include <pthread.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <errno.h>

// Optional: use these functions to add debug or error prints to your application
#define DEBUG_LOG(msg,...)
//#define DEBUG_LOG(msg,...) printf("threading: " msg "\n" , ##__VA_ARGS__)
#define ERROR_LOG(msg,...) printf("threading ERROR: " msg "\n" , ##__VA_ARGS__)


void* threadfunc(void* context)
{
    // TODO: wait, obtain mutex, wait, release mutex as described by thread_data structure
    // hint: use a cast like the one below to obtain thread arguments from your parameter
    //struct thread_data* thread_func_args = (struct thread_data *) thread_param;

    if (!context) {
        return NULL;
    }

    struct thread_data* self = (struct thread_data*)context;
    self->thread_complete_success = false;

    usleep(self->wait_to_obtain_ms * 1000);
    if (pthread_mutex_lock(self->mutex)) {
        perror("Unable ot lock mutex");
        return self;
    }

    usleep(self->wait_to_release_ms * 1000);
    if (pthread_mutex_unlock(self->mutex)) {
        perror("Unable to unlock mutex");
        return self;
    }

    self->thread_complete_success = true;

    return self;
}


bool start_thread_obtaining_mutex(pthread_t *thread, pthread_mutex_t *mutex,int wait_to_obtain_ms, int wait_to_release_ms)
{
    if (!thread || !mutex) {
        printf("Error: invalid inputs");
        return false;
    }

    struct thread_data* data = calloc(1, sizeof(struct thread_data));
    if (data == NULL) {
        perror("Unable to allocate memory for the thread");
        return false;
    }

    data->wait_to_obtain_ms = wait_to_obtain_ms;
    data->wait_to_release_ms = wait_to_release_ms;
    data->mutex = mutex;
    data->thread_complete_success = false;
    
    const int resThread = pthread_create(thread, NULL, threadfunc, data);
    if (resThread) {
        errno = resThread;
        perror("Unable to create the thread");
        free(data);
        return false;
    }

    return true;
}

