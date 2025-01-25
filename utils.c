/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: busseven <busseven@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/22 12:06:33 by busseven          #+#    #+#             */
/*   Updated: 2025/01/25 17:40:38 by busseven         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <sys/wait.h>
#include "./ft_printf/ft_printf.h"
#include "./ft_printf/libft/libft.h"
#include <fcntl.h>
#include "pipex.h"

char	**ft_freeall(char **arr)
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
	int i = 0;
	char	**path_arr;

	while(env[i])
	{
		if(!ft_strncmp(env[i], "PATH=", 5))
		{
			path_arr = ft_split(env[i] + 5, ':');
			break ;
		}

		i++;
	}
	return(path_arr);
}

char	*find_correct_path(char **cmd_arr, t_pipex *prog)
{
	int i = 0;
	char *path;
	char *c;
	char	*temp;

	c = "/";
	while(prog->paths[i])
	{
		temp = ft_strjoin(prog->paths[i], c);
		path = ft_strjoin(temp, cmd_arr[0]);
		if(access(path, F_OK | X_OK) == 0)
			break ;
		free(path);
		free(temp);
		i++;
	}
	if(!path)
		invalid_command(cmd_arr[0]);
	return (path);
}

char	**make_command_arr(char *cmd)
{
	char **cmd_arr;

	cmd_arr = ft_split(cmd, ' ');
	return(cmd_arr);
}

void	init_program(t_pipex *prog, char **argv, char **env, int argc)
{
	int i;

	prog->paths = extract_env_path(env);
	prog->fd_infile = open(argv[1], O_RDWR);
	prog->fd_outfile = open(argv[argc - 1], O_RDWR);
	prog->cmd_cnt = argc - 3;
	prog->fd = ft_calloc(prog->cmd_cnt - 1, sizeof(int[2]));
	i = 2;
	while(i <= prog->cmd_cnt + 1)
	{
		prog->cmd_arr[i - 2] = ft_calloc(1, sizeof(t_cmd));
		prog->cmd_arr[i - 2]->arg_arr = make_command_arr(argv[i]);
		prog->cmd_arr[i - 2]->path = find_correct_path(prog->cmd_arr[i - 2]->arg_arr, prog);
		i++;
	}
	i = 0;
	while(i < prog->cmd_cnt - 1)
	{
		pipe(prog->fd[i]);
		i++;
	}
}
