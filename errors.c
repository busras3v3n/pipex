/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: busseven <busseven@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/23 13:57:17 by busseven          #+#    #+#             */
/*   Updated: 2025/01/23 15:13:18 by busseven         ###   ########.fr       */
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
	close(prog->fd_infile);
	close(prog->fd_outfile);
	while(prog->cmd_arr[i])
	{
		ft_freeall(prog->cmd_arr[i]->arg_arr);
		free(cmd_arr[i]->path);
		i++;
	}
	free(prog->cmd_arr);
	free(prog);
}
void	invalid_file(t_pipex *prog)
{
	ft_printf("Error\n");
	if(prog->fd_infile < 0)
		ft_printf("invalid infile\n");
	if(prog->outfile < 0)
		ft_printf("invalid outfile\n");
	free_prog(prog);
}
void	invalid_command(t_pipex *prog, char *cmd)
{
	ft_printf("Error\n %s does not exist", cmd);
	free_prog(prog);
}