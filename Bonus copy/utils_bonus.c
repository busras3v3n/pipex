/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: busseven <busseven@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/22 12:06:33 by busseven          #+#    #+#             */
/*   Updated: 2025/01/29 18:49:54 by busseven         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <sys/wait.h>
#include "../ft_printf/ft_printf.h"
#include "../ft_printf/libft/libft.h"
#include <fcntl.h>
#include "pipex.h"

char	**free_2d_char(char **arr)
{
	int	i;
	i = 0;
	if(!arr)
		return (NULL);
	while (arr[i])
	{
		free(arr[i]);
		i++;
	}
	free(arr);
	return (NULL);
}

char	**extract_env_path(char **env)
{
	int		i;
	char	**path_arr;
	i = 0;
	while (env[i])
	{
		if (!ft_strncmp(env[i], "PATH=", 5))
			break;
		i++;
	}
	path_arr = ft_split(env[i] + 5, ':');
	i = 0;
	while (path_arr[i])
	{
		path_arr[i] = add_chars(path_arr[i], '/');
		i++;
	}
	return (path_arr);
}

char	*find_correct_path(char *cmd, char **env)
{
	int		i;
	char	*path;
	char	**paths;
	
	i = 0;
	paths = extract_env_path(env);
	while (paths[i])
	{
		path = ft_strjoin(paths[i], cmd);
		if (access(path, F_OK | X_OK) == 0)
		{
			free_2d_char(paths);
			return (path);
		}
		free(path);
		i++;
	}
	free_2d_char(paths);
	return (NULL);
}

char	*add_chars(char *str, char a)
{
	int i;
	char *temp;

	i = 0;
	temp = ft_calloc(ft_strlen(str) + 2, sizeof(char));
	while (str[i])
	{
		temp[i] = str[i];
		i++;
	}
	temp[i] = a;
	temp[i + 1] = '\0';
	free(str);
	return (temp);
}
