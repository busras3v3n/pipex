/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: busseven <busseven@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/23 13:57:17 by busseven          #+#    #+#             */
/*   Updated: 2025/01/26 11:57:14 by busseven         ###   ########.fr       */
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

void	invalid_command(t_pipex *prog)
{
	ft_printf("Error\n");
	if (!prog->cmd_arr[0]->path)
		ft_printf("can't find path for %s\n", prog->cmd_arr[0]->arg_arr[0]);
	if (!prog->cmd_arr[1]->path)
		ft_printf("can't find path for %s\n", prog->cmd_arr[1]->arg_arr[0]);
	free_prog(prog);
	exit(1);
}
