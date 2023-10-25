#include <sys/time.h>

double elapsed_time(struct timeval* start_time, struct timeval* end_time){
    //TODO: return the difference between end_time and start_time.
    double elapsed_seconds = (double)(end_time->tv_sec - start_time->tv_sec);
    
    return 0.0;
}