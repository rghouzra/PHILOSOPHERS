#include "philosophers.h"

int main(int ac, char **argv)
{
	if(ac >= 5 && ac <= 6)
	{
		printf("parsing->%d", parsing(ac - 1, argv + 1));
	}
	else
		ft_putstr_fd("invalid number of args\n", 2);
}
