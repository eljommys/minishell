/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Descriptions.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paris <paris@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/17 16:38:00 by paris             #+#    #+#             */
/*   Updated: 2020/11/17 16:39:01 by paris            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

	<stdlib.h>: malloc(), free(), exit()
	<unistd.h>: write(), read(), close(), fork(), getcwd(), chdir(), execve(), dup(), dup2(), pipe()
	<dirent.h>: opendir(), readdir(), closedir()
	<signal.h>: signal(), kill()
	<errno.h>: errno()					https://www.youtube.com/watch?v=IZiUT-ipnj0&ab_channel=JacobSorber
	<string.h>: strerror()
	<fcntl.h>: open()
	<sys/wait.h>: wait(), waitpid(), wait3(), wait4()
	<sys/stat.h>: stat(), lstat(), fstat()

	- int		chdir(const char *path):			https://man7.org/linux/man-pages/man2/chdir.2.html

		Changes the current working directory of the calling process to the directory specified in path.

	- char 		*getcwd(char *buf, size_t size):	https://man7.org/linux/man-pages/man2/getcwd.2.html

		The function copies an absolute pathname of the current working directory to the array pointed to by buf, which is of length size.

	- int		execve(const char *pathname, char *const argv[], char *const envp[]):	https://man7.org/linux/man-pages/man2/execve.2.html

		Executes the program referred to by pathname. This causes the program that is currently being run by the calling process to be
		replaced with a new program, with newly initialized stack, heap, and (initialized and uninitialized) data segments.

	- pid_t		fork(void):							https://man7.org/linux/man-pages/man2/fork.2.html

		Creates a new process by duplicating the calling process. The new process is referred to as the child process.
		The calling process is referred to as the parent process.

	- int		dup(int oldfd):						https://man7.org/linux/man-pages/man2/dup.2.html
	- int		dup2(int oldfd, int newfd):

		The dup() system call creates a copy of the file descriptor oldfd, using the lowest-numbered unused file descriptor for the new descriptor.

		The dup2() system call performs the same task as dup(), but instead of using the lowest-numbered unused file descriptor, it uses the file
		descriptor number specified in newfd.  If the file descriptor newfd was previously open, it is silently closed before being reused.

	- int		pipe(int pipefd[2]):				https://man7.org/linux/man-pages/man2/pipe.2.html

		Creates a pipe, a unidirectional data channel that can be used for interprocess communication. The array pipefd is used to return
		two file descriptors referring to the ends of the pipe. pipefd[0] refers to the read end of the pipe. pipefd[1] refers to the write
		end of the pipe. Data written to the write end of the pipe is buffered by the kernel until it is read from the read end of the pipe.

	- sighandler_t		signal(int signum, sighandler_t handler):		https://man7.org/linux/man-pages/man2/signal.2.html

		signal() sets the disposition of the signal signum to handler, which is either SIG_IGN, SIG_DFL, or the address of a programmer-defined
		function (a "signal handler").

	- int		kill(pid_t pid, int sig):			https://man7.org/linux/man-pages/man2/kill.2.html

		The kill() system call can be used to send any signal to any process group or process.
		If pid is positive, then signal sig is sent to the process with the ID specified by pid.
		If pid equals 0, then sig is sent to every process in the process group of the calling process.
		If pid equals -1, then sig is sent to every process for which the calling process has permission to send signals,
			except for process 1(init), but see below.
		If pid is less than -1, then sig is sent to every process in the process group whose ID is -pid.
		If sig is 0, then no signal is sent, but existence and permission checks are still performed;
			this can be used to check for the existence of a process ID or process group ID that the caller is permitted to signal.

	- pid_t		wait(int *wstatus):				https://man7.org/linux/man-pages/man2/waitid.2.html

		The wait() system call suspends execution of the calling thread until one of its children terminates.
		The call wait(&wstatus) is equivalent to: waitpid(-1, &wstatus, 0);

	- pid_t		waitpid(pid_t pid, int *wstatus, int options):		https://man7.org/linux/man-pages/man2/waitid.2.html

		The waitpid() system call suspends execution of the calling thread until a child specified by pid argument has changed state.
		By default, waitpid() waits only for terminated children, but this behavior is modifiable via the options argument, as described below.
		The value of pid can be:
		< -1   meaning wait for any child process whose process group ID is equal to the absolute value of pid.
		-1     meaning wait for any child process.
		0      meaning wait for any child process whose process group ID is equal to that of the calling process at the time of the call to waitpid().
		> 0    meaning wait for the child whose process ID is equal to the value of pid.

	- pid_t		wait3(int *wstatus, int options, struct rusage *rusage): 				https://man7.org/linux/man-pages/man2/wait3.2.html
	- pid_t		wait4(pid_t pid, int *wstatus, int options, struct rusage *rusage):

		The wait3() and wait4() system calls are similar to waitpid, but additionally return resource usage information about the child in the
		structure pointed to by rusage.

	- int		stat(const char *pathname, struct stat *statbuf):		https://man7.org/linux/man-pages/man2/stat.2.html
	- int		lstat(const char *pathname, struct stat *statbuf):
	- int		fstat(int fd, struct stat *statbuf):

		These functions return information about a file, in the buffer pointed to by statbuf.  No permissions are required on the file itself,
		but—in the case of stat(), fstatat(), and lstat() — execute(search) permission is required on all of the directories in pathname that lead to the file.

		stat() and fstatat() retrieve information about the file pointed to by pathname; the differences for fstatat() are described below.

		lstat() is identical to stat(), except that if pathname is a symbolic link, then it returns information about the link itself, not the file that the link refers to.

		fstat() is identical to stat(), except that the file about which information is to be retrieved is specified by the file descriptor fd.
