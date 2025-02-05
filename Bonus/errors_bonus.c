/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: busseven <busseven@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/23 13:57:17 by busseven          #+#    #+#             */
/*   Updated: 2025/02/05 10:27:07 by busseven         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

void	wrong_argc(t_pipex *prog)
{
	ft_printf("Invalid format\nValid formats:\n");
	ft_printf("infile cmd ... cmd1 outfile\n");
	ft_printf("infile here_doc LIMITER cmd ... cmd1 outfile\n");
	if (prog)
		free(prog);
	exit(1);
}

void	invalid_file_descriptor(t_pipex *prog)
{
	if (prog->fd_infile < 0 && !prog->here_doc)
		ft_printf("Invalid infile\n");
	if (prog->fd_outfile < 0)
		ft_printf("Invalid outfile\n");
	free(prog);
	exit(1);
}

void	invalid_command(t_pipex *prog, int i)
{
	ft_printf("%s: Command not found", prog->commands[i][0]);
	free_prog(prog);
	exit(127);
}

void	check_for_empty_arg(char **argv, t_pipex *prog)
{
	int	i;

	i = 2;
	while (argv[i] && argv[i + 1])
	{
		if (is_all_space(argv[i]) || argv[i][0] == '\0')
		{
			ft_printf("Empty argument(s)\n");
			free(prog);
			exit(2);
		}
		i++;
	}
}

void	execve_fail(t_pipex *prog)
{
	ft_printf("execve failed\n");
	free_prog(prog);
	exit(1);
}
