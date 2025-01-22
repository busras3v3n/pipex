/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_nbr.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: busseven <busras3v3n@proton.me>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/05 12:42:07 by busseven          #+#    #+#             */
/*   Updated: 2024/11/09 17:20:01 by busseven         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./libft/libft.h"

static int	ft_intlen(int i)
{
	int	len;
	int	n;

	len = 0;
	n = i;
	if (n < 0)
	{
		len++;
		n = -n;
	}
	while (n / 10 != 0)
	{
		len++;
		n = n / 10;
	}
	len++;
	return (len);
}

int	ft_print_nbr(int i)
{
	ft_putnbr_fd(i, 1);
	return (ft_intlen(i));
}
