/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: busseven <busseven@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/03 09:34:27 by busseven          #+#    #+#             */
/*   Updated: 2025/02/03 18:44:24 by busseven         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

int	free_buffer(int k, char *buffer)
{
	if (k == 0)
	{
		if(buffer)
			free(buffer);
		return (0);
	}
	return (1);
}

char	*get_next_line2(int fd, int k)
{
	static char	*buffer[1024];
	char		*next_line;

	if (!free_buffer(k, buffer[fd]))
		return(NULL);
	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	buffer[fd] = ft_read_file(fd, buffer[fd]);
	if (!buffer[fd])
		return (NULL);
	if (ft_findnewline(buffer[fd]) == -1)
		next_line = ft_substr(buffer[fd], 0, ft_strlen(buffer[fd]));
	else
		next_line = ft_substr(buffer[fd], 0, ft_findnewline(buffer[fd]) + 1);
	if (!next_line)
		return (NULL);
	if (next_line[0] == '\0')
	{
		free(next_line);
		free(buffer[fd]);
		return (NULL);
	}
	buffer[fd] = new_buffer(buffer[fd]);
	return (next_line);
}
void	free_prog(t_pipex *prog)
{
	int	i;

	i = 0;
	if (!prog->here_doc)
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
	free(prog);
}

char	**free_2d_char(char **arr)
{
	int	i;

	i = 0;
	if (!arr)
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
	if(i == 0 && prog->here_doc)
		close(prog->hd[0]);
	if (i != 0)
		close(prog->fd[i - 1][0]);
	if (i != prog->cmd_cnt - 1)
		close(prog->fd[i][1]);
}
