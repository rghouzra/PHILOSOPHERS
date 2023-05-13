#include "philosophers.h"

void *ft_malloc(size_t size)
{
	void *ptr;

	ptr = malloc(size);
	if (!ptr)
	{
		ft_putstr_fd("Error: malloc failed\n", 2);
		exit(1);
	}
	return (ptr);
}

pid_t ft_fork()
{
	pid_t pid;

	pid = fork();
	if(pid == -1)
	{
		ft_putstr_fd("Error: fork failed\n", 2);
		exit(1);
	}
	return (pid);
}