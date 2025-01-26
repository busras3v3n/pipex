/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: busseven <busseven@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/23 13:51:25 by busseven          #+#    #+#             */
/*   Updated: 2025/01/26 11:50:35 by busseven         ###   ########.fr       */
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

void	process(int i, t_pipex *prog, char **env)
{
	if(i == 0)
	{
		dup2(prog->fd_infile, 0);
		dup2(prog->fd[1], 1);
		close(prog->fd[0]);
		execve(prog->cmd_arr[0]->path, prog->cmd_arr[0]->arg_arr, env);
	}
	if(i == 1)
	{
		dup2(prog->fd_outfile, 1);
		dup2(prog->fd[0], 0);
		close(prog->fd[1]);
		execve(prog->cmd_arr[1]->path, prog->cmd_arr[1]->arg_arr, env);
	}
}
int	main(int argc, char **argv, char **env)
{
	t_pipex *prog;
	int id;
	int i;
	i = 0;
	id = 1;
	if(argc == 5)
	{
		prog = ft_calloc(1, sizeof(t_pipex));
		init_program(prog, argv, env);
		while(i <= 1)
		{
			if(id != 0)
				id = fork();
			if(id == 0)
				process(i, prog, env);
			else
				ft_printf("parent\n");
			i++;
		}
		wait(NULL);
		free_prog(prog);
	}
	else
		ft_printf("incorrect number of arguments\n");
}
