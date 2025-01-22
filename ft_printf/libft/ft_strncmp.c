/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: busseven <busseven@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/16 15:39:35 by busseven          #+#    #+#             */
/*   Updated: 2024/10/22 20:48:22 by busseven         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	unsigned char	*s1u;
	unsigned char	*s2u;
	size_t			i;

	s1u = (unsigned char *)s1;
	s2u = (unsigned char *)s2;
	i = 0;
	while (i < n)
	{
		if (s1u[i] == '\0' && s2u[i] == '\0')
			return (0);
		else if (!s1u[i] && s2u[i])
			return (-s2u[i]);
		else if (!s2u[i] && s1u[i])
			return (s1u[i]);
		else if (s1u[i] != s2u[i])
			return (s1u[i] - s2u[i]);
		i++;
	}
	return (0);
}
