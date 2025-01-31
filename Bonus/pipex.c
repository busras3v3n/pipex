/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: busseven <busseven@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/23 13:51:25 by busseven          #+#    #+#             */
/*   Updated: 2025/01/31 20:26:19 by busseven         ###   ########.fr       */
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

void	free_prog(t_pipex *prog)
{
	int i;

	i = 0;
	close(prog->fd_infile);
	close(prog->fd_outfile);
	while(i < 2)
	{
		free_2d_char(prog->commands[i]);
		free(prog->paths[i]);
		i++;
	}
	free(prog->commands);
	free(prog->paths);
}
void	open_files(char **argv, int argc, t_pipex *prog)
{
	if(prog->here_doc == 0)
	{
		prog->fd_infile = open(argv[1], O_RDWR);
		prog->fd_outfile = open(argv[argc - 1], O_RDWR);
	}
	else
	{
		prog->fd_outfile = open(argv[argc - 1], O_RDWR, O_APPEND);
		prog->limiter = argv[2];
	}
}
void	wait_for_children(int n)
{
	while(n > 0)
	{
		wait(NULL);
		n--;
	}
}
void	wrong_argc()
{
	ft_printf("!argc < 6\n");
	exit(1);
}
void	make_pipes(int **fd, int argc, t_pipex *prog)
{
	int i;

	i = 0;
	while(i < argc - 3 - prog->here_doc)
	{
		fd[i] = ft_calloc(2, sizeof(int));
		pipe(fd[i]);
		i++;
	}
}
void	init_prog(t_pipex *prog, int argc, char **argv, char **env)
{
	int i;

	i = 0;
	if(!ft_strncmp(argv[1], "here_doc", ft_strlen(argv[1])))
		prog->here_doc = 1;
	else
		prog->here_doc = 0;
	if(prog->here_doc == 1 && argc < 6)
		wrong_argc();
	prog->cmd_cnt = argc - 3 - prog->here_doc;
	open_files(argv, argc, prog);
	if((prog->fd_infile < 0) | (prog->fd_outfile < 0))
		invalid_file_descriptor(prog);
	prog->commands = ft_calloc(argc - 3 - prog->here_doc, sizeof(char **));
	prog->paths = ft_calloc(argc - 3 - prog->here_doc, sizeof(char *));
	while(i < argc - 3 - prog->here_doc)
	{
		prog->commands[i] = ft_split(argv[i + 2 + prog->here_doc], ' ');
		prog->paths[i] = find_correct_path(prog->commands[i][0], env);
		if(!prog->paths[i])
			invalid_command(prog, i);
		i++;
	}
	prog->fd = ft_calloc(argc - 3 - prog->here_doc, sizeof(int *));
	make_pipes(prog->fd, argc, prog);
}
void	here_doc(t_pipex *prog)
{
	char *line;
	int	stop;

	stop = 0;
	while(!stop)
	{
		line = get_next_line(0);
		if(!ft_strncmp(line, prog->limiter, ft_strlen(line - 1)))
		{
			stop = 1;
		}
		free(line);
	}
	return;
}
void	process(int i, int id, t_pipex *prog, char **env)
{
	ft_printf("process %d", i);
	if(id != 0)
		id = fork();
	if(id != 0)
		return ;
	if(i == 0 && prog->here_doc == 1)
		here_doc(prog);
	else if(i == 0)
		dup2(prog->fd_infile, 0);
	else
	{
		dup2(prog->fd[i - 1][0], 0);
		close(prog->fd[i - 1][1]);
	}
	if(i == prog->cmd_cnt - 1)
		dup2(prog->fd_outfile, 1);
	else
	{
		dup2(prog->fd[i][1], 1);
		close(prog->fd[i][0]);
	}
	if(execve(prog->paths[i], prog->commands[i], env) == -1)
	{
		ft_printf("execve fail");
		exit(1);
	}
}
int		is_all_space(char *str)
{
	int i;

	i = 0;
	while(str[i])
	{
		if(str[i] != ' ')
			return (0);
		i++;
	}
	return(1);
}
int	main(int argc, char **argv, char **env)
{
	t_pipex	prog;
	int		id;
	int		i;

	i = 0;
	id = 1;
	if (argc >= 5)
	{
		check_for_empty_arg(argv);
		init_prog(&prog, argc, argv, env);
		while(i < argc - 3)
		{
			process(i, id, &prog, env);
			if(i != 0)
				close(prog.fd[i - 1][0]);
			else if(i != prog.cmd_cnt - 1)
				close(prog.fd[i][1]);
			i++;
		}
		ft_printf("waiting....");
		wait_for_children(argc - 3 - 1 - prog.here_doc);
	}
	else
		ft_printf("incorrect number of arguments\n");
}
