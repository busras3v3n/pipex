/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: busseven <busseven@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/17 13:48:20 by busseven          #+#    #+#             */
/*   Updated: 2024/10/22 20:48:36 by busseven         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char			*str;
	unsigned int	i;
	unsigned int	j;

	i = start;
	j = 0;
	if (len > ft_strlen(s) - start)
		len = ft_strlen(s) - start;
	if (len == 0 || i >= ft_strlen(s))
		return (ft_strdup(""));
	str = malloc((len * sizeof(char)) + 1);
	if (!str)
		return (NULL);
	while (i < start + len && j < len)
	{
		str[j] = s[i];
		i++;
		j++;
	}
	str[j] = '\0';
	return (str);
}
