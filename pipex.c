/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: busseven <busseven@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/23 13:51:25 by busseven          #+#    #+#             */
/*   Updated: 2025/01/23 20:08:49 by busseven         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <sys/wait.h>
#include "./ft_printf/ft_printf.h"
#include "./ft_printf/libft/libft.h"
#include <fcntl.h>
#include "pipex.h"
#include <stdio.h>
#include <signal.h>

void	process(int i, t_pipex *prog)
{
	int fd_in;
	int fd_out;

	if(i == 0)
		fd_in = prog->fd_infile;
	else
		fd_in = prog->fd[0];
	if(!prog->cmd_arr[i + 1])
		fd_out = prog->fd_outfile;
	else
		fd_out = prog->fd[1];
	dup2(fd_in, STDIN_FILENO);
	close(fd_in);
	dup2(fd_out, STDOUT_FILENO);
	close(fd_out);
}

int	main(int argc, char **argv, char **env)
{
	t_pipex *prog;
	int i;
	int id;

	i = 0;
	id = 1;
	if(argc >= 5)
	{
		prog = ft_calloc(1, sizeof(t_pipex));
		init_program(prog, argv, env, argc);
		if(prog->fd_infile < 0 || prog->fd_outfile < 0)
			invalid_file(prog);
	}
	else
	{
		write(1, "incorrect number of arguments\n", 30);
		return 0;
	}
	while(prog->cmd_arr[i])
	{
		if(id != 0)
			id = fork();
		if(id != 0)
		{
			ft_printf("parent process\n");
		}
		if(id == 0)
		{
			ft_printf("child process %d\n", i);
			return 0;
		}
		i++;
	}
	wait(NULL);
}
