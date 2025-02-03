/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: busseven <busseven@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/23 13:21:45 by busseven          #+#    #+#             */
/*   Updated: 2025/02/03 17:20:11 by busseven         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include <stdlib.h>
# include <unistd.h>
# include <sys/wait.h>
# include "../ft_printf/ft_printf.h"
# include "../ft_printf/libft/libft.h"
# include <fcntl.h>
# include <errno.h>

typedef struct s_pipex
{
	int		fd_infile;
	int		fd_outfile;
	int		fd[2];
	char	**paths;
	char	***commands;
}	t_pipex;

char	*find_correct_path(char *cmd, char **env);
char	*add_chars(char *str, char a);
char	**free_2d_char(char **arr);
void	invalid_file_descriptor(t_pipex *prog);
void	invalid_command(t_pipex *prog, int i);
void	free_prog(t_pipex *prog);
void	check_for_empty_arg(char **argv);
int		is_all_space(char *str);
void	execve_fail(t_pipex *prog);
void	close_pipes(int i, t_pipex *prog);

#endif