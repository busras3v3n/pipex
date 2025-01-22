/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: busseven <busseven@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/17 17:56:02 by busseven          #+#    #+#             */
/*   Updated: 2024/10/22 20:48:33 by busseven         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	checkset(char c, const char *set)
{
	int	i;

	i = 0;
	while (set[i])
	{
		if (set[i] == c)
			return (1);
		i++;
	}
	return (0);
}

char	*ft_strtrim(const char *s1, const char *set)
{
	int		i;
	int		j;
	int		x;
	char	*trimmed;

	if (!s1)
		return (NULL);
	if (*s1 == '\0')
		return (ft_strdup(""));
	i = 0;
	j = ft_strlen(s1) - 1;
	x = 0;
	while (checkset(s1[i], set))
		i++;
	while (checkset(s1[j], set) && j >= i)
		j--;
	trimmed = malloc(sizeof(char) * (j - i + 2));
	if (!trimmed)
		return (NULL);
	while (i <= j)
		trimmed[x++] = s1[i++];
	trimmed[x] = '\0';
	return (trimmed);
}
