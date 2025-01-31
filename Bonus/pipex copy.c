/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex copy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: busseven <busseven@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/23 13:51:25 by busseven          #+#    #+#             */
/*   Updated: 2025/01/31 20:06:33 by busseven         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <sys/wait.h>
#include "../ft_printf/ft_printf.h"
#include "../ft_printf/libft/libft.h"
#include <fcntl.h>
#include "pipex.h"
#include <stdio.h>
#include <signal.h>

int	main(int argc, char **argv)
{
	char *line;
	int	stop;

	stop = 0;
	(void)argc;
	while(!stop)
	{
		line = get_next_line(0);
		if(!line)
			return 0;
		if(!ft_strncmp(line, argv[1], ft_strlen(line) - 1))
		{
			stop = 1;
		}
		free(line);
	}
}