#include "philosophers.h"

void	*ft_calloc(size_t nelem, size_t elsize)
{
	char	*ptr;

	ptr = (char *)malloc(nelem * elsize);
	if (!ptr)
		return (NULL);
	memset(ptr, '\0', (nelem * elsize));
	return (ptr);
}
