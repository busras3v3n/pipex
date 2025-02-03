/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: busseven <busseven@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/23 13:51:25 by busseven          #+#    #+#             */
/*   Updated: 2025/02/03 11:50:11 by busseven         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	free_prog(t_pipex *prog)
{
	int	i;

	i = 0;
	close(prog->fd_infile);
	close(prog->fd_outfile);
	while (i < 2)
	{
		free_2d_char(prog->commands[i]);
		free(prog->paths[i]);
		i++;
	}
	free(prog->commands);
	free(prog->paths);
	free(prog);
}

void	init_prog(t_pipex *prog, char **argv, char **env)
{
	int	i;

	i = 0;
	prog->fd_infile = open(argv[1], O_RDWR);
	prog->fd_outfile = open(argv[4], O_RDWR | O_CREAT | O_TRUNC, 0777);
	if ((prog->fd_infile < 0) || (prog->fd_outfile < 0))
		invalid_file_descriptor(prog);
	prog->commands = ft_calloc(2, sizeof(char **));
	prog->paths = ft_calloc(2, sizeof(char *));
	while (i < 2)
	{
		prog->commands[i] = ft_split(argv[i + 2], ' ');
		prog->paths[i] = find_correct_path(prog->commands[i][0], env);
		if (!prog->paths[i])
			invalid_command(prog, i);
		i++;
	}
	pipe(prog->fd);
}

void	process(int i, int id, t_pipex *prog, char **env)
{
	if (id != 0)
		id = fork();
	if (id != 0)
		return ;
	if (i == 0)
		dup2(prog->fd_infile, 0);
	else
	{
		dup2(prog->fd[0], 0);
		close(prog->fd[1]);
	}
	if (i == 0)
	{
		dup2(prog->fd[1], 1);
		close(prog->fd[0]);
	}
	else
		dup2(prog->fd_outfile, 1);
	if (execve(prog->paths[i], prog->commands[i], env) == -1)
		execve_fail(prog);
}

int	is_all_space(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] != ' ')
			return (0);
		i++;
	}
	return (1);
}

int	main(int argc, char **argv, char **env)
{
	t_pipex	*prog;
	int		id;
	int		i;

	i = 0;
	id = 1;
	if (argc == 5)
	{
		check_for_empty_arg(argv);
		prog = ft_calloc(1, sizeof(t_pipex));
		init_prog(prog, argv, env);
		while (i < 2)
		{
			process(i, id, prog, env);
			i++;
		}
		wait(NULL);
		wait(NULL);
		free_prog(prog);
	}
	else
		ft_printf("format: ./pipex infile cmd cmd1 outfile\n");
}
