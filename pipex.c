/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: busseven <busseven@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/23 13:51:25 by busseven          #+#    #+#             */
/*   Updated: 2025/01/25 17:52:20 by busseven         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <sys/wait.h>
#include "./ft_printf/ft_printf.h"
#include "./ft_printf/libft/libft.h"
#include <fcntl.h>
#include "pipex.h"
#include <stdio.h>
#include <signal.h>

int	main(int argc, char **argv, char **env)
{
	if(argc && argv)
	{
		char *correct_path;
		char **env_path;
		env_path = extract_env_path(env);
		int i = 0;
		while(env_path[i])
		{
			ft_printf("%s\n", env_path[i]);
			i++;
		}
		i = 1;
		while(argv[i])
		{
			correct_path = find_correct_path(argv[i], env_path);
			ft_printf("correct path: %s for %s\n", correct_path, argv[i]);
			free(correct_path);
			i++;
		}
	}
}
