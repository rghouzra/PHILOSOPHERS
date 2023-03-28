#include "philosophers.h"

int main(int ac, char **argv)
{
	t_params params;

	if(ac < 5 || ac > 6)
		return(ft_putstr_fd("invalid nums of arguments\n", 2), 1);
	if (parsing(ac - 1, argv + 1, &params) != 1)
		return(ft_putstr_fd("invalid args", 2), 1);
	philosophy_start(params);
	return (0);
}
