#include "philosophers.h"

void show_error(char *s)
{
//TODO: for mandatory pary check if exit forbidden
	ft_putstr_fd(s, 2);
	exit(1);
}
