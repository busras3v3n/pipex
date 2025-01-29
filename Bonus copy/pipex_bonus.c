/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: busseven <busseven@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/23 13:51:25 by busseven          #+#    #+#             */
/*   Updated: 2025/01/29 18:48:13 by busseven         ###   ########.fr       */
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

void	free_prog(t_pipex *prog, int argc)
{
	int i;
	i = 0;
	close(prog->fd_infile);
	close(prog->fd_outfile);
	while (i < argc - 3)
	{
		free_2d_char(prog->commands[i]);
		if(prog->paths[i])
			free(prog->paths[i]);
		if (i != 0)
		{
			free(prog->fd[i - 1]);
		}
		i++;
	}
	free(prog->commands);
	free(prog->paths);
	free(prog->fd);
	free(prog);
}
void	init_prog(t_pipex *prog, int argc, char **argv, char **env)
{
	int i;
	i = 0;
	prog->fd_infile = open(argv[1], O_RDWR);
	prog->fd_outfile = open(argv[argc - 1], O_CREAT | O_RDWR);
	if((prog->fd_infile < 0) | (prog->fd_outfile < 0))
		invalid_file(prog);
	prog->commands = ft_calloc(argc - 3, sizeof(char **));
	prog->paths = ft_calloc(argc - 3, sizeof(char *));
	prog->fd = ft_calloc(argc - 4, sizeof(int *));
	while (i < argc - 3)
	{
		if (i != 0)
		{
			prog->fd[i - 1] = ft_calloc(2, sizeof(int));
			pipe(prog->fd[i - 1]);
		}
		prog->commands[i] = ft_split(argv[i + 2], ' ');
		prog->paths[i] = find_correct_path(prog->commands[i][0], env);
		if(!prog->paths[i])
		{
			free_prog(prog, argc);
			exit(1);
		}
		i++;
	}
}
void	process(t_pipex *prog, char **env, int argc, int i)
{
	if (i == 0)
		dup2(prog->fd_infile, 0);
	else
	{
		dup2(prog->fd[i - 1][0], 0);
		close(prog->fd[i - 1][1]);
	}
	if (i == argc - 4)
		dup2(prog->fd_outfile, 1);
	else
	{
		dup2(prog->fd[i][1], 1);
		close(prog->fd[i][0]);
	}
	if(execve(prog->paths[i], prog->commands[i], env) == -1)
	{
		ft_printf("execve fail\nArgument(s) probably invalid\n");
		free_prog(prog, argc);
		exit(1);
	}
}
void	wait_for_children(int n)
{
	int i;

	i = 0;
	while (i < n)
	{
		wait(NULL);
		i++;
	}
}
int	main(int argc, char **argv, char **env)
{
	t_pipex	*prog;
	int		i;
	int		id;

	i = 0;
	id = 1;
	if (argc >= 5)
	{
		prog = ft_calloc(1, sizeof(t_pipex));
		init_prog(prog, argc, argv, env);
		while (i < argc - 3)
		{
			if (id != 0)
				id = fork();
			else
				process(prog, env, argc, i);
			if (i >= 1)
				close(prog->fd[i - 1][0]);
			if (i != argc - 4)
				close(prog->fd[i][1]);
			i++;
		}
		wait_for_children(argc - 4);
	}
	else
		ft_printf("argc < 5 !\n");
	free_prog(prog, argc);
}
