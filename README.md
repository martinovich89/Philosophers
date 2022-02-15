# philosophers
Solve philosophers puzzle with forks and mutex


# User Manual
to run the program, type
$> make
$> ./philo arg arg arg arg (arg)

args are all positive numbers. The last one is optional.  
arg1 : amount of philosophers. Must be 0 < arg1 <= 200.  
arg2 : tiime to die. must be a number >= 0  
arg3 : time to eat. must be a number >= 0  
arg4 : time to sleep. must be a number >= 0  
arg5 : minimum amount of meals every philospher has to eat.  

# My reading of the subject
I would like to clarify some shady thing that made me change and think again my code several times.

The subject says :
"time_to_die: is in milliseconds, if a philosopher doesn’t start eating ’time_to_die’ milliseconds after starting their last meal or the beginning of the simulation, it dies".

So if my understanding is correct, I should count a philosopher as dead if (current_timestamp - lastmeal_timestamp) > time_to_die.
So if for example current_timestamp - lastmeal_timestamp = 400 and time_to_die = 400 in milliseconds, philosopher shouldn't die.
But this leads to some clemency from the program, because although we take measure of time in microseconds, we skip the micro and only take milliseconds into account.
Therefore, a 400.999 is still 400 milliseconds and allows a technically dead philo to keep going.
So I initially thought it should not be allowed.
But What have made me change my mind is that the subject says ".."... doesn't start eating time_to_die milliseconds ...". Which means an elapsed time equal to time_to_die will not result in a death.
And if it was asked an infinite precision, it could never be equal (always either inferior or superior, even zillions of 0 in decimal place).
So I decided to be indulgent and only count philo as dead if time_to_die + 1 is reached.
That's why tests such as 4 400 200 200 will pass most of the time (depends on system stability and PCs).
