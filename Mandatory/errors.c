/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: busseven <busseven@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/23 13:57:17 by busseven          #+#    #+#             */
/*   Updated: 2025/01/31 14:53:22 by busseven         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <sys/wait.h>
#include "../ft_printf/ft_printf.h"
#include "../ft_printf/libft/libft.h"
#include <fcntl.h>
#include "pipex.h"

void	invalid_file_descriptor(t_pipex *prog)
{
	ft_printf("Error\n");
	if (prog->fd_infile < 0)
		ft_printf("invalid infile\n");
	if (prog->fd_outfile < 0)
		ft_printf("invalid outfile\n");
	exit(1);
}

void	invalid_command(t_pipex *prog, int i)
{
	ft_printf("Error\n");
	ft_printf("No path for %s\n", prog->commands[i][0]);
	free_prog(prog);
	exit(1);
}
void	check_for_empty_arg(char **argv)
{
	if((argv[2][0] == '\0') | (argv[3][0] == '\0'))
	{
		ft_printf("Empty arguments\n");
		exit(1);
	}
	else if(is_all_space(argv[2]) | is_all_space(argv[3]))
	{
		ft_printf("Empty arguments\n");
		exit(1);
	}
}
