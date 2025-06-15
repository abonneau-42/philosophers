#include <stdio.h>
#include <unistd.h>
#include <sys/time.h>

#define N_ITERATIONS 25000
#define SLEEP_USEC   200000  // 10 ms

// Renvoie le timestamp actuel en microsecondes
unsigned long get_timestamp_us(void)
{
    struct timeval tv;
    gettimeofday(&tv, NULL);
    return (tv.tv_sec * 1000000UL + tv.tv_usec);
}

int main(void)
{
    unsigned long ts_before, ts_after, delta;
    
    printf("Testing usleep(%d µs) for %d iterations:\n\n", SLEEP_USEC, N_ITERATIONS);

	ts_before = get_timestamp_us();
	usleep(SLEEP_USEC);
	ts_after = get_timestamp_us();

	printf("Testing usleep(%d µs) => %d \n\n", SLEEP_USEC, (int)(ts_after - ts_before));


}