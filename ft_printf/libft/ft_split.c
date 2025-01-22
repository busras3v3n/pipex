/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: busseven <busseven@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/18 13:54:16 by busseven          #+#    #+#             */
/*   Updated: 2024/10/28 11:09:46 by busseven         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_wordcount(const char *s, char c)
{
	int	i;
	int	word;

	word = 0;
	i = 0;
	while (s[i])
	{
		while (s[i] == c && s[i])
			i++;
		if (s[i] != c && s[i])
			word++;
		while (s[i] != c && s[i])
			i++;
	}
	return (word);
}

static char	*ft_allocate(const char *s, int i, int j)
{
	char	*a;
	int		x;

	x = 0;
	a = malloc((j - i + 1) * sizeof(char));
	if (!a)
		return (NULL);
	while (i < j)
	{
		a[x] = s[i];
		i++;
		x++;
	}
	a[x] = '\0';
	return (a);
}

static char	**ft_freeall(char **arr)
{
	int	i;

	i = 0;
	while (arr[i])
	{
		free(arr[i]);
		i++;
	}
	free(arr);
	return (NULL);
}

char	**ft_split(const char *s, char c)
{
	char	**arr;
	int		i;
	int		j;
	int		k;

	i = 0;
	k = 0;
	arr = malloc((ft_wordcount(s, c) + 1) * sizeof(char *));
	if (!arr || !s)
		return (NULL);
	while (k < ft_wordcount(s, c))
	{
		while (s[i] == c && s[i])
			i++;
		j = i;
		while (s[j] != c && s[j])
			j++;
		arr[k++] = ft_allocate(s, i, j);
		if (!arr[k - 1])
			return (ft_freeall(arr));
		i = j;
	}
	arr[k] = NULL;
	return (arr);
}
