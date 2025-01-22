/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: busseven <busseven@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/12 19:00:50 by busseven          #+#    #+#             */
/*   Updated: 2024/10/22 20:47:31 by busseven         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	size_t	i;

	i = len - 1;
	if (len == 0 || dst == src)
		return (dst);
	if (dst > src)
	{
		while (i > 0)
		{
			*(char *)(dst + i) = *(char *)(src + i);
			i--;
		}
		if (i == 0)
			*(char *)(dst + i) = *(char *)(src + i);
	}
	else
	{
		ft_memcpy(dst, src, len);
	}
	return (dst);
}
