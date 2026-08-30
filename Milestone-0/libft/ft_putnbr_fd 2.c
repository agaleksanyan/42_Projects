#include "libft.h"

void	ft_putnbr_fd(int n, int fd)
{
	long	i;
	char	c;

	i = n;
	if (i < 0)
	{
		write(fd, "-", 1);
		i = -i;
	}
	if (i >= 10)
		ft_putnbr_fd(i / 10, fd);
	c = (i % 10) + '0';
	write(fd, &c, 1);	
}
