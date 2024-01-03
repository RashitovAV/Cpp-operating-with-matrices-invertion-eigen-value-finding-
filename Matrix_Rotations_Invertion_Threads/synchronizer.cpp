#include "synchronizer.h"
#include <pthread.h>
#include <sys/time.h>
#include <sys/resource.h>
void synchronize(int p)
{
    static pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
    static pthread_cond_t condvar_in = PTHREAD_COND_INITIALIZER;
    static pthread_cond_t condvar_out = PTHREAD_COND_INITIALIZER;
    static int thin = 0;
    static int thout = 0;
    pthread_mutex_lock(&mutex);
    thin++;
    if (thin >= p) {
        thout = 0;
        pthread_cond_broadcast(&condvar_in);
    }
    else {
        while (thin < p) {
            pthread_cond_wait(&condvar_in, &mutex);
        }
    }

    thout++;
    if (thout >= p) {
        thin = 0;
        pthread_cond_broadcast(&condvar_out);
    }
    else {
        while (thout < p) {
            pthread_cond_wait(&condvar_out, &mutex);
        }
    }
    pthread_mutex_unlock(&mutex);
}
double get_full_time()
{
    struct timeval tm;

    gettimeofday(&tm, 0);

    return tm.tv_sec + tm.tv_usec / 1000000.0;
}
