#include "libft.h"

void    *ft_memset(void *b, int c, size_t len)
{
    size_t  i;
    unsigned char   *p;
    
    p = (unsigned char *)b;
    i = 0;
    while (i < len)
    {
        p[i] = (unsigned char)c;
        i++;
    }
    return (b);
}
// #include <stdio.h>

// // int main()
// // {
// //     char    *b = "qwertyuiop";
// //     int f = 6;
// //     int g ='h';

// //     printf("%s", ft_memset(b, g, f));
// // }