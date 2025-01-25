/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: busseven <busseven@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/23 13:57:17 by busseven          #+#    #+#             */
/*   Updated: 2025/01/25 19:11:48 by busseven         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <sys/wait.h>
#include "./ft_printf/ft_printf.h"
#include "./ft_printf/libft/libft.h"
#include <fcntl.h>
#include "pipex.h"

void	invalid_file(t_pipex *prog)
{
	ft_printf("Error\n");
	if(prog->fd_infile < 0)
		ft_printf("invalid infile\n");
	if(prog->fd_outfile < 0)
		ft_printf("invalid outfile\n");
}
void	invalid_command(char *cmd)
{
	ft_printf("Error\n %s does not exist", cmd);
}