/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: busseven <busseven@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/22 12:06:33 by busseven          #+#    #+#             */
/*   Updated: 2025/01/28 12:19:12 by busseven         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <sys/wait.h>
#include "../ft_printf/ft_printf.h"
#include "../ft_printf/libft/libft.h"
#include <fcntl.h>
#include "pipex.h"

void	free_prog(t_pipex *prog)
{
	int	i;

	i = 0;
	while (prog->cmd_arr[i] != NULL)
	{
		ft_free_2d_arr(prog->cmd_arr[i]->arg_arr);
		if(prog->cmd_arr[i]->path)
			free(prog->cmd_arr[i]->path);
		free(prog->cmd_arr[i]);
		if(i != 0)
			free(prog->fd[i - 1]);
		i++;
	}
	close(prog->fd_infile);
	close(prog->fd_outfile);
	ft_free_2d_arr(prog->paths);
	if(prog->fd)
		free(prog->fd);
	free(prog->cmd_arr);
	free(prog);
}

char	**ft_free_2d_arr(char **arr)
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

char	**extract_env_path(char **env)
{
	int		i;
	char	**path_arr;

	i = 0;
	while (env[i])
	{
		if (!ft_strncmp(env[i], "PATH=", 5))
		{
			path_arr = ft_split(env[i] + 5, ':');
			break ;
		}
		i++;
	}
	return (path_arr);
}

char	*find_correct_path(char *cmd, char **paths)
{
	int		i;
	char	*path;
	char	*c;
	char	*temp;

	c = "/";
	i = 0;
	while (paths[i])
	{
		temp = ft_strjoin(paths[i], c);
		path = ft_strjoin(temp, cmd);
		if (access(path, F_OK | X_OK) == 0)
		{
			free(temp);
			return (path);
		}
		free(path);
		free(temp);
		i++;
	}
	return (NULL);
}

char	**make_command_arr(char *cmd)
{
	char	**cmd_arr;

	cmd_arr = ft_split(cmd, ' ');
	return (cmd_arr);
}
