/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: busseven <busseven@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/17 16:46:28 by busseven          #+#    #+#             */
/*   Updated: 2024/10/22 20:48:05 by busseven         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	char		*joined;
	size_t		j;
	size_t		i;

	joined = malloc((sizeof(char) * (ft_strlen(s1) + ft_strlen(s2))) + 1);
	if (!joined)
		return (NULL);
	j = 0;
	i = 0;
	while (j < ft_strlen(s1))
	{
		joined[j] = s1[j];
		j++;
	}
	while (i < ft_strlen(s2))
	{
		joined[j] = s2[i];
		i++;
		j++;
	}
	joined[j] = '\0';
	return (joined);
}
