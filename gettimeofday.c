#include <stdio.h>
#include <sys/time.h>

int main(void)
{
	struct timeval tv;
	struct timezone tz;

	gettimeofday(&tv, &tz);
	printf("%zu.%zu\n", tv.tv_sec, tv.tv_usec);
	printf("%d\n", tz.tz_minuteswest);
}
