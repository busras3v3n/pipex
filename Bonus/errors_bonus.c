/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: busseven <busseven@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/23 13:57:17 by busseven          #+#    #+#             */
/*   Updated: 2025/01/26 14:52:40 by busseven         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <sys/wait.h>
#include "../ft_printf/ft_printf.h"
#include "../ft_printf/libft/libft.h"
#include <fcntl.h>
#include "pipex.h"

void	invalid_file(t_pipex *prog)
{
	ft_printf("Error\n");
	if (prog->fd_infile < 0)
		ft_printf("invalid infile\n");
	if (prog->fd_outfile < 0)
		ft_printf("invalid outfile\n");
	free_prog(prog);
	exit(1);
}

void	invalid_command(t_pipex *prog, char *cmd)
{
	ft_printf("Error\n");
	ft_printf("can't find path for %s\n", cmd);
	free_prog(prog);
	exit(1);
}
