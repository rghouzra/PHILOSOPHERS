#include "philosophers.h"

int main(int ac, char **argv)
{
	t_params params;

	if(ac < 5 || ac > 6)
		show_error("invalid nums of arguments\n");
	if (parsing(ac - 1, argv + 1, &params) != 1)
		show_error("invalid args");
	philosophy_start(params);
}

