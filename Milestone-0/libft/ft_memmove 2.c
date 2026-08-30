#include "libft.h"

void *ft_memmove(void *dest, const void *src, size_t len)
{
	size_t  i;
	unsigned char *d;
	const unsigned char *s;
    
	d = (unsigned char *)dest;
	s = (const unsigned char *)src;
	if (d < s)
	{
		i = 0;
		while (i < len)
		{
			d[i] = s[i];
			i++;
		}
	}
	else
	{
		while (len > 0)
		{
			len--;
			d[len] = s[len];
		}
	}
	return (dest);
}
