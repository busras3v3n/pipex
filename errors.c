/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: busseven <busseven@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/23 13:57:17 by busseven          #+#    #+#             */
/*   Updated: 2025/01/23 18:29:24 by busseven         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <sys/wait.h>
#include "./ft_printf/ft_printf.h"
#include "./ft_printf/libft/libft.h"
#include <fcntl.h>
#include "pipex.h"

void	free_prog(t_pipex *prog)
{
	int i;

	i = 0;
	if(prog->fd_infile >= 0)
		close(prog->fd_infile);
	if(prog->fd_outfile >= 0)
		close(prog->fd_outfile);
	while(prog->cmd_arr && prog->cmd_arr[i])
	{
		if(prog->cmd_arr[i]->arg_arr)
			ft_freeall(prog->cmd_arr[i]->arg_arr);
		if(prog->cmd_arr[i]->path)
			free(prog->cmd_arr[i]->path);
		i++;
	}
	if(prog->cmd_arr)
		free(prog->cmd_arr);
	free(prog);
}
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