#include "libft.h"

char    *ft_strnstr(const char *src, const char *dest, size_t len)
{
    size_t  i;
    size_t  j;
    
    if (dest[0] == '\0')
    return ((char *)src);
    i = 0;
    while(src[i] && i < len)
    {
        j = 0;
        while(dest[j]
        	&& src[i +j]
        	&& i + j < len
        	&& src[i +j] == dest[j])
        j++;
        if (dest[j] == '\0')
        return((char *)&src[i]);
        i++;
    }
    return (NULL);
}
