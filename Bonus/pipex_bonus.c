/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: busseven <busseven@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/23 13:51:25 by busseven          #+#    #+#             */
/*   Updated: 2025/01/26 17:35:11 by busseven         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <sys/wait.h>
#include "../ft_printf/ft_printf.h"
#include "../ft_printf/libft/libft.h"
#include <fcntl.h>
#include "pipex.h"
#include <stdio.h>
#include <signal.h>

void	init_program(t_pipex *prog, char **argv, int argc, char **env)
{
	int i;

	i = 0;
	prog->fd_infile = open(argv[1], O_RDWR);
	prog->fd_outfile = open(argv[argc - 1], O_RDWR);
	prog->cmd_arr = ft_calloc(argc - 3, sizeof(t_cmd));
	prog->paths = extract_env_path(env);
	while(i < argc - 3)
	{
		prog->cmd_arr[i] = ft_calloc(1, sizeof(t_cmd));
		prog->cmd_arr[i]->arg_arr = make_command_arr(argv[i + 2]);
		prog->cmd_arr[i]->path = find_correct_path(prog->cmd_arr[i]->arg_arr[0], prog->paths);
		if (!prog->cmd_arr[i]->path) 
			invalid_command(prog, prog->cmd_arr[i]->arg_arr[0]);
		i++;
	}
	i = 0;
	prog->fd = ft_calloc(argc - 4, sizeof(int *));
	while(i < argc - 4)
	{
		prog->fd[i] = ft_calloc(2, sizeof(int));
		pipe(prog->fd[i]);
		i++;
	}
	if (prog->fd_infile < 0 || prog->fd_outfile < 0)
		invalid_file(prog);
}

void	process(int i, t_pipex *prog, char **env, int argc)
{
	if (i == 0)
	{
		dup2(prog->fd_infile, 0);
		dup2(prog->fd[i][1], 1);
		close(prog->fd[i][0]);
		execve(prog->cmd_arr[i]->path, prog->cmd_arr[i]->arg_arr, env);
	}
	else if (i == argc - 4)
	{
		dup2(prog->fd_outfile, 1);
		dup2(prog->fd[i - 1][0], 0);
		close(prog->fd[i - 1][1]);
		execve(prog->cmd_arr[i]->path, prog->cmd_arr[i]->arg_arr, env);
	}
	else if(i < argc - 4 && i > 0)
	{
		dup2(prog->fd[i - 1][0], 0);
		dup2(prog->fd[i][1], 1);
        close(prog->fd[i - 1][1]);
        close(prog->fd[i][0]);   
		execve(prog->cmd_arr[i]->path, prog->cmd_arr[i]->arg_arr, env);
	}
}

int	main(int argc, char **argv, char **env)
{
	t_pipex	*prog;
	int		id;
	int		i;

	i = 0;
	id = 1;
	if (argc >= 5)
	{
		prog = ft_calloc(1, sizeof(t_pipex));
		init_program(prog, argv, argc, env);
		while (prog->cmd_arr[i])
		{
			if (id != 0)
				id = fork();
			if (id == 0)
				process(i, prog, env, argc);
			else
				ft_printf("parent\n");
			i++;
			wait(NULL);
		}
	}
	else
		ft_printf("incorrect number of arguments\n");
}
