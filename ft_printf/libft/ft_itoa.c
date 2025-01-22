/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: busseven <busseven@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/18 12:26:28 by busseven          #+#    #+#             */
/*   Updated: 2024/10/27 18:37:44 by busseven         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_intlen(int i)
{
	int	len;
	int	x;

	x = i;
	len = 0;
	if (x < 0)
	{
		len++;
		x = -x;
	}
	while (x / 10 != 0)
	{
		len++;
		x = x / 10;
	}
	len++;
	return (len);
}

char	*ft_itoa(int n)
{
	char	*str;
	int		i;
	int		isnegative;

	if (n == -2147483648)
		return (ft_strdup("-2147483648"));
	i = ft_intlen(n) - 1;
	str = malloc(ft_intlen(n) * sizeof(char) + 1);
	isnegative = 0;
	if (!str)
		return (NULL);
	str[ft_intlen(n)] = '\0';
	if (n < 0)
	{
		str[0] = '-';
		n = -n;
		isnegative = 1;
	}
	while (i >= isnegative)
	{
		str[i] = (n % 10) + '0';
		n = n / 10;
		i--;
	}
	return (str);
}
