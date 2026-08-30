#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*s;
	size_t	j;
	size_t	i;
	size_t	s1_len;
	size_t	s2_len;

	if (s1 == NULL || s2 == NULL)
		return (NULL);
	s1_len = ft_strlen(s1);
	s2_len = ft_strlen(s2);
	s = malloc(s1_len + s2_len + 1);
	if (!s)
		return(NULL);
	i = 0;
	j = 0;
	while(s1[i])
	{
		s[i] = s1[i];
		i++;
	}
	while(s2[j])
	{
		s[i + j] = s2[j];
		j++;
	}
	s[i + j] = '\0';
	return(s);
}
