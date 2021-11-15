#include <stdio.h>
#include <sys/time.h>
#include <string.h>
#include <unistd.h>

void	my_usleep(size_t time, struct timeval *tv, struct timeval *tz)
{
	double	oldtime;
	double	newtime;

	gettimeofday(tv, tz);
	oldtime = (double)tv->tv_sec + (double)tv->tv_usec / 1000000;
	newtime = oldtime;
	while (newtime - oldtime < (double)time /1000000)
	{
		gettimeofday(tv, tz);
		newtime = (double)tv->tv_sec + (double)tv->tv_usec / 1000000;
	}
}

int main(void)
{
	struct	timeval tv;
	struct	timeval tz;
	double	time;
	double	my_time;
	double	before;
	double	after;

	gettimeofday(&tv, &tz);
	before = (double)tv.tv_sec + (double)tv.tv_usec;
	my_usleep(10000, &tv, &tz);
	after = (double)tv.tv_sec + (double)tv.tv_usec;
	my_time = after - before;
	printf("%lf | %lf\n", my_time, (double)time / 1000000);
	gettimeofday(&tv, &tz);
	before = (double)tv.tv_sec + (double)tv.tv_usec / 1000000;
	usleep(10000);
	gettimeofday(&tv, &tz);
	after = (double)tv.tv_sec + (double)tv.tv_usec / 1000000;
	time = after - before;
	printf("%lf\n", after - before);
}
