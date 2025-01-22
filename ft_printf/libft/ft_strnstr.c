/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: busseven <busseven@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/16 18:22:43 by busseven          #+#    #+#             */
/*   Updated: 2024/10/22 20:48:26 by busseven         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *haysack, const char *needle, size_t len)
{
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	if (*needle == '\0')
		return ((char *)haysack);
	if (ft_strlen(needle) > ft_strlen(haysack) || ft_strlen(needle) > len)
		return (NULL);
	while (haysack[i] && (i + j < len) && needle[j])
	{
		j = 0;
		while (haysack[i + j] == needle[j] && (i + j < len) && needle[j])
		{
			if (j == ft_strlen(needle) - 1)
				return ((char *)(haysack + i));
			j++;
		}
		i++;
	}
	return (NULL);
}
