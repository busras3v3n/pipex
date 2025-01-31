/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: busseven <busseven@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/23 13:57:17 by busseven          #+#    #+#             */
/*   Updated: 2025/01/31 19:37:27 by busseven         ###   ########.fr       */
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
	if(prog->fd_outfile < 0 || (prog->here_doc == 0 && prog->fd_infile < 0))
	{
		ft_printf("Invalid file descriptor\n");
		exit(1);
	}
}

void	invalid_command(t_pipex *prog, int i)
{
	ft_printf("Error\n");
	ft_printf("No path for %s\n", prog->commands[i][0]);
	exit(1);
}
void	check_for_empty_arg(char **argv)
{
	int i;

	i = 2;
	while(argv[i] && argv[i + 1])
	{
		if(is_all_space(argv[i]) || argv[i][0] == '\0')
		{
			ft_printf("Empty argument(s)");
			exit(1);
		}
		i++;
	}
}
