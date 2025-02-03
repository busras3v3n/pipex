/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: busseven <busseven@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/23 13:51:25 by busseven          #+#    #+#             */
/*   Updated: 2025/02/03 09:16:39 by busseven         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <sys/wait.h>
#include "../ft_printf/ft_printf.h"
#include "../ft_printf/libft/libft.h"
#include <fcntl.h>
#include "pipex_bonus.h"
#include <stdio.h>
#include <signal.h>

void	here_doc(char *stop, t_pipex *prog)
{
	char *line;
	char *limiter;
	int i;

	i = 0;
	pipe(prog->hd);
	limiter = ft_calloc(ft_strlen(stop) + 1, sizeof(char));
	while(stop[i])
	{
		limiter[i] = stop[i];
		i++;
	}
	limiter[ft_strlen(stop)] = '\n';
	while(1)
	{
		line = get_next_line(0);
		write(prog->hd[1], line, ft_strlen(line));
		if(!ft_strncmp(line, limiter, ft_strlen(line)))
		{
			free(line);
			free(limiter);
			close(prog->hd[1]);
			return;
		}
		free(line);
	}
}
void	free_prog(t_pipex *prog)
{
	int i;

	i = 0;
	close(prog->fd_infile);
	close(prog->fd_outfile);
	while (i < prog->cmd_cnt)
	{
		free_2d_char(prog->commands[i]);
		if (prog->paths[i] != NULL)
			free(prog->paths[i]);
		if (i != 0)
			free(prog->fd[i - 1]);
		i++;
	}
	free(prog->commands);
	free(prog->paths);
	free(prog->fd);
}
void	open_files(t_pipex *prog, char **argv, int argc)
{
	if(prog->here_doc == 0)
		prog->fd_infile = open(argv[1], O_RDWR);
	prog->fd_outfile = open(argv[argc - 1], O_RDWR | O_CREAT | O_TRUNC, 774);
	if((!prog->here_doc && prog->fd_infile < 0) || (prog->fd_outfile < 0))
		invalid_file_descriptor(prog);
}
void	init_prog(t_pipex *prog, int argc, char **argv, char **env)
{
	int i;

	i = 0;
	if(!ft_strncmp(argv[1], "here_doc", ft_strlen(argv[1])))
		prog->here_doc = 1;
	else
		prog->here_doc = 0;
	prog->cmd_cnt = argc - 3 - prog->here_doc;
	if(prog->here_doc == 1)
		here_doc(argv[2], prog);
	prog->fd = ft_calloc(argc - 4 - prog->here_doc, sizeof(int *));
	prog->commands = ft_calloc(argc - 3 - prog->here_doc, sizeof(char **));
	prog->paths = ft_calloc(argc - 3 - prog->here_doc, sizeof(char *));
	while(i < argc - 3 - prog->here_doc)
	{
		if (i != 0)
		{
			prog->fd[i - 1] = ft_calloc(2, sizeof(int));
			pipe(prog->fd[i - 1]);			
		}
		prog->commands[i] = ft_split(argv[i + 2 + prog->here_doc], ' ');
		prog->paths[i] = find_correct_path(prog->commands[i][0], env);
		if(!prog->paths[i])
			invalid_command(prog, i);
		i++;
	}
	open_files(prog, argv, argc);
}

void	process(int i, int id, t_pipex *prog, char **env)
{
	if(id != 0)
		id = fork();
	if(id != 0)
		return ;
	if(i == 0 && prog->here_doc == 1)
	{
		dup2(prog->hd[0], 0);
		close(prog->hd[1]);
	}
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
		while (i < argc - 3 - prog.here_doc)
		{
			process(i, id, &prog, env);
			if (i != 0)
				close(prog.fd[i - 1][0]);
			if (i != prog.cmd_cnt - 1)
				close(prog.fd[i][1]);
			i++;
		}
		while(i-- >= 0)
			wait(NULL);
		free_prog(&prog);
	}
	else
		ft_printf("incorrect number of arguments\n");
}
