#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	char	v;
	int	i;

	v = (char)c;
	i = ft_strlen(s);
	while(i >= 0)
	{
		if (s[i] == v)
                        return((char *)&s[i]);
                i--;
	}
        return(NULL);
}			
