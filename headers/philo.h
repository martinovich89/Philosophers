#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include <sys/wait.h>
# include <string.h>

/*
** ttd, tte and tts refer to : time to die, time to eat and time to sleep.
*/

typedef struct	s_vars
{
	int	philos;
	int	ttd;
	int	tte;
	int	tts;
}	t_vars;

#endif
