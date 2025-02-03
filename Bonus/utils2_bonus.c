/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: busseven <busseven@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/03 09:34:27 by busseven          #+#    #+#             */
/*   Updated: 2025/02/03 11:00:11 by busseven         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include <unistd.h>
#include <sys/wait.h>
#include "../ft_printf/ft_printf.h"
#include "../ft_printf/libft/libft.h"
#include <fcntl.h>
#include "pipex_bonus.h"
#include <stdio.h>
#include <signal.h>

void	free_prog(t_pipex *prog)
{
	int i;

	i = 0;
	if(!prog->here_doc)
		close(prog->fd_infile);
	close(prog->fd_outfile);
	while (i < prog->cmd_cnt)
	{
		free_2d_char(prog->commands[i]);
		if (prog->paths[i] != NULL)
			free(prog->paths[i]);
		if (i != 0)
			free(prog->fd[i - 1]);
		i++;
	}
	free(prog->commands);
	free(prog->paths);
	free(prog->fd);
}
char	**free_2d_char(char **arr)
{
	int	i;
	i = 0;
	if(!arr)
		return (NULL);
	while (arr[i])
	{
		free(arr[i]);
		i++;
	}
	free(arr);
	return (NULL);
}
void	close_pipes(int i, t_pipex *prog)
{
	if (i != 0)
		close(prog->fd[i - 1][0]);
	if (i != prog->cmd_cnt - 1)
		close(prog->fd[i][1]);
}