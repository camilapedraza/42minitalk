
// SIGINT - ctrl + c, an INTerrupt
// SIGTERM - TERMinate (gracefully and can be ignored)
// SIGKILL - guaranteed termination Cannot be caught, ignored or blocked
// SIGHUP - reload configuration ???

sighandler_t signal(int signum, sighandler_t handler);
/* SIGNAL */
/*
** Specify a hanlder function to be called when a particular signal is received.
** (i.e. take specified action in response to a specific signal).
*/

int sigemptyset(sigset_t *set);
/* SIGEMPTYSET */
/*
** Initialize an empty signal set.
** Takes a pointer to a set of signals and empties that set (puts no signal).
*/

int sigaddset(sigset_t *set, int signum);
/* SIGADDSET */
/*
** Add a signal to a set of signals. 
** Takes two arguments: 
** - a pointer to a set of signals
** - the number of the signal to be added to the set.
*/

// example
example_1 (sigset_t signal_set)
{
	sigset_t signal_set;

	// Initialize an empty signal set
	sigemptyset(&signal_set);

	// Add SIGINT to the signal set
	sigaddset(&signal_set, SIGINT);
}

int sigaction(int signum, const struct sigaction *act, struct sigaction *oldact);
/* SIGACTION */
/*
** Modern signal() ? - unlike signal(), handler is not reset after execution
**
** Specifies the action to be taken when a specific signal is received by a process.
** - The signum param specifies the signal for which the action is being specified.
** - The act param is a pointer to a sigaction struct that specifies the action to be taken when the signal is received.
** - The oldact param is a pointer to a sigaction struct that is used to retrieve the previous action for the specified signal.
**
** sigaction struct can specify:
** - Handler function (sa_handler)
** - Signals to block during handler execution (sa_mask)
** ----- initialized with sigemptyset(&act.sa_mask);
** - Flags controlling behavior (sa_flags)
**
** USEFUL FLAGS
** SA_RESTART – restart interrupted system calls
** SA_SIGINFO – get extra information about the signal
** SA_NOCLDWAIT – avoid zombie processes
** SA_NODEFER – don’t block the signal being handled
*/

example_2()
{
	struct sigaction action;
	action.sa_handler = signal_handler;
	sigemptyset(&action.sa_mask);
	action.sa_flags = 0;

	sigaction(SIGINT, &action, NULL);
}

int kill(pid_t pid, int sig);
/* KILL */
/*
** Send a signal to a process (or group of processes).
** - The pid param specifies the process ID of the process you want to communicate with.
** - The sig param specifies the signal to be sent to the process.
** Despite the name, it doesn't actually kill anything.
** kill() sends a signal, such as:
**
** EXAMPLE SIGNALS
** SIGTERM (polite request to terminate)
** SIGKILL (force termination)
** SIGINT (like Ctrl+C)
** SIGSTOP / SIGCONT (pause / resume)
**
** RETURN VALUES
** 0 → success
** -1 → error
**
** COMMON ERRORS
** ESRCH → no such process
** EPERM → no permission
** EINVAL → invalid signal
*/

// - getpid() returns an int with the ID of the process. 
// Very useful when programs generate child processes via fork
// - pause() puts a process to sleep until a signal is received
// - sleep() puts a process to sleep for a specified number of seconds
// - usleep() puts a process to sleep for a specified number of microseconds

// SIGUSR1 and SIGUSR2
// User-defined signals with no predefined value. They are NOT real-time.
// Not queued (multiple signals may collapse into one)
// No payload
