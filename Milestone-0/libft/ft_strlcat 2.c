#include "libft.h"

size_t  ft_strlcat(char *dst, const char *src, size_t dstsize)
{
    size_t    s_len;
    size_t    d_len;
    size_t   i;

    s_len = ft_strlen(src);
    d_len = 0;
    while (d_len < dstsize && dst[d_len])
        d_len++;
    if (d_len == dstsize)
        return (dstsize + s_len);
    i = 0;
    while(src[i] && (d_len + i +1) < dstsize)
    {
        dst[d_len + i] = src[i];
        i++;
    }
    dst[d_len + i] = '\0';
    return (d_len + s_len);
}
