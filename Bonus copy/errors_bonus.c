/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: busseven <busseven@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/23 13:57:17 by busseven          #+#    #+#             */
/*   Updated: 2025/01/29 15:53:14 by busseven         ###   ########.fr       */
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
	if(prog->fd_infile < 0)
		ft_printf("invalid infile\n");
	if(prog->fd_outfile < 0)
		ft_printf("invalid outfile\n");
	if(prog->fd_infile >= 0)
		close(prog->fd_infile);
	if(prog->fd_outfile >= 0)
		close(prog->fd_outfile);
	free(prog);
	exit(1);
}
void	path_not_found(char *cmd, t_pipex *prog)
{
	ft_printf("No path found for %s", cmd);
	free_prog(prog);
	exit(1);
}