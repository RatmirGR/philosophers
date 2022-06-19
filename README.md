<h3>Project name:</h3>
<h2> philosophers</h2>

<p><ins>Project description:</ins></p>
This project is about learning how threads work by precisely timing a group of philosophers on when to pick up forks and eat spaghetti without dying from hunger.

<p></p>
<p><ins>Task:</ins></p>
<p>• Global variables are forbidden!</p>
<p>• Your(s) program(s) should take the following arguments:</p>
<p> number_of_philosophers time_to_die time_to_eat time_to_sleep</p>
<p> [number_of_times_each_philosopher_must_eat]</p>
<p>◦ number_of_philosophers: The number of philosophers and also the number of forks.</p>
<p>◦ time_to_die (in milliseconds): If a philosopher didn’t start eating time_to_die milliseconds since the beginning of their last meal or the beginning of the simulation, they die.</p>
<p>◦ time_to_eat (in milliseconds): The time it takes for a philosopher to eat. During that time, they will need to hold two forks.</p>
<p>◦ time_to_sleep (in milliseconds): The time a philosopher will spend sleeping.</p>
<p>◦ number_of_times_each_philosopher_must_eat (optional argument): If all philosophers have eaten at least number_of_times_each_philosopher_must_eat times, the simulation stops. If not specified, the simulation stops when a philosopher dies.</p>
<p>• Each philosopher has a number ranging from 1 to number_of_philosophers.</p>
<p>• Philosopher number 1 sits next to philosopher number number_of_philosophers. Any other philosopher number N sits between philosopher number N - 1 and philosopher number N + 1.</p>

<p>About the logs of your program:</p>
<p>• Any state change of a philosopher must be formatted as follows:</p>
<p>◦ timestamp_in_ms X has taken a fork</p>
<p>◦ timestamp_in_ms X is eating</p>
<p>◦ timestamp_in_ms X is sleeping</p>
<p>◦ timestamp_in_ms X is thinking</p>
<p>◦ timestamp_in_ms X died</p>
<p>Replace timestamp_in_ms with the current timestamp in milliseconds and X with the philosopher number.</p>
<p>• A displayed state message should not be mixed up with another message.</p>
<p>• A message announcing a philosopher died should be displayed no more than 10 ms after the actual death of the philosopher.</p>
<p>• Again, philosophers should avoid dying!</p>

<p>•Each philosopher should be a thread.</p>
<p>•• There is one fork between each pair of philosophers. Therefore, if there are several philosophers, each philosopher has a fork on their left side and a fork on their right side. If there is only one philosopher, there should be only one fork on the table.</p>
<p>•• To prevent philosophers from duplicating forks, you should protect the forks state with a mutex for each of them.</p>

<p><ins>Bonus part</ins></p>
<p>The program of the bonus part takes the same arguments as the mandatory program. It has to comply with the requirements of the Global rules chapter.</p>
<p>The specific rules for the bonus part are:</p>
<p>• All the forks are put in the middle of the table.</p>
<p>• They have no states in memory but the number of available forks is represented by a semaphore.</p>
<p>• Each philosopher should be a process. But the main process should not be a philosopher.</p>
