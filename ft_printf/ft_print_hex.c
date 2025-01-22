/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_hex.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: busseven <busras3v3n@proton.me>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/06 09:41:52 by busseven          #+#    #+#             */
/*   Updated: 2024/11/09 17:19:14 by busseven         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>

static int	ft_putnbr_hex_fd(unsigned int n, int fd)
{
	char	*base;
	int		count;

	base = "0123456789abcdef";
	count = 0;
	if (n >= 16)
	{
		count += ft_putnbr_hex_fd(n / 16, fd);
		count += ft_putnbr_hex_fd(n % 16, fd);
	}
	else if (n < 16)
	{
		write(fd, &base[n], 1);
		count++;
	}
	return (count);
}

static int	ft_putnbr_hex_upcase_fd(unsigned int n, int fd)
{
	char	*base;
	int		count;

	base = "0123456789ABCDEF";
	count = 0;
	if (n >= 16)
	{
		count += ft_putnbr_hex_upcase_fd(n / 16, fd);
		count += ft_putnbr_hex_upcase_fd(n % 16, fd);
	}
	else if (n < 16)
	{
		write(fd, &base[n], 1);
		count++;
	}
	return (count);
}

int	ft_print_hex(int i, char s)
{
	unsigned int	u;

	u = (unsigned int)i;
	if (s == 'x')
		return (ft_putnbr_hex_fd(u, 1));
	if (s == 'X')
		return (ft_putnbr_hex_upcase_fd(u, 1));
	else
		return (0);
}
