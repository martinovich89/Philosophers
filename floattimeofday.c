#include <stdio.h>
#include <sys/time.h>

int main(void)
{
	struct timeval tv;
	struct timeval tz;
	double time;

	gettimeofday(&tv, &tz);
	time = (double)tv.tv_sec + (double)tv.tv_usec / 1000000;
	printf("%lf\n", time);
}
