#include "libft.h"

char	*ft_strchr(const char *s, int c)
{
	size_t	i;
	char	v;

	v = (char)c;
	i = 0;
	while (s[i])
	{
		if (s[i] == v)
			return((char *)&s[i]);
		i++;
	}
	if (v == '\0')
		return((char *)&s[i]);
	return(NULL);
}
