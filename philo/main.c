#include "philosophers.h"

int main(int ac, char **argv)
{
	t_params params;

	printf("%d\n", ft_strcmp("died", "died"));
	exit(0);
	if (ac < 5 || ac > 6)
		return(ft_putstr_fd("invalid nums of arguments\n", 2), 1);
	if (parsing(ac - 1, argv + 1, &params) != 1)
		return(ft_putstr_fd("invalid args", 2), 1);
	prepare_table(params);
	return (0);
}
