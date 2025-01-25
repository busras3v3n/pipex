/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: busseven <busseven@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/22 12:06:33 by busseven          #+#    #+#             */
/*   Updated: 2025/01/25 19:32:05 by busseven         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <sys/wait.h>
#include "./ft_printf/ft_printf.h"
#include "./ft_printf/libft/libft.h"
#include <fcntl.h>
#include "pipex.h"

void	free_prog(t_pipex *prog)
{
	int i;
	
	i = 0;

	while(i <= 1)
	{
		close(prog->fd[i]);
		ft_free_2d_arr(prog->cmd_arr[i]->arg_arr);
		if(prog->cmd_arr[i]->path)
			free(prog->cmd_arr[i]->path);
		free(prog->cmd_arr[i]);
		i++;
	}
	close(prog->fd_infile);
	close(prog->fd_outfile);
	ft_free_2d_arr(prog->paths);
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

char	*find_correct_path(char *cmd, char **paths)
{
	int i = 0;
	char *path;
	char *c;
	char	*temp;

	c = "/";
	while(paths[i])
	{
		temp = ft_strjoin(paths[i], c);
		path = ft_strjoin(temp, cmd);
		if(access(path, F_OK | X_OK) == 0)
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
	char **cmd_arr;

	cmd_arr = ft_split(cmd, ' ');
	return(cmd_arr);
}

void	init_program(t_pipex *prog, char **argv, char **env)
{
	prog->fd_infile = open(argv[1], O_RDWR);
	prog->fd_outfile = open(argv[4], O_RDWR);
	prog->cmd_arr = ft_calloc(2, sizeof(t_cmd));
	prog->paths = extract_env_path(env);
	prog->cmd_arr[0] = ft_calloc(1, sizeof(t_cmd));
	prog->cmd_arr[1] = ft_calloc(1, sizeof(t_cmd));
	prog->cmd_arr[0]->arg_arr = make_command_arr(argv[2]);
	prog->cmd_arr[1]->arg_arr = make_command_arr(argv[3]);
	prog->cmd_arr[0]->path = find_correct_path(prog->cmd_arr[0]->arg_arr[0], prog->paths);
	prog->cmd_arr[1]->path = find_correct_path(prog->cmd_arr[1]->arg_arr[0], prog->paths);
	pipe(prog->fd);
	if(prog->fd_infile < 0 || prog->fd_outfile < 0)
		invalid_file(prog);
	if(!prog->cmd_arr[0]->path || !prog->cmd_arr[1]->path)
		invalid_command(prog);
}
