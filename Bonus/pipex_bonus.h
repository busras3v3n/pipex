/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: busseven <busseven@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/23 13:21:45 by busseven          #+#    #+#             */
/*   Updated: 2025/02/03 18:42:43 by busseven         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_BONUS_H
# define PIPEX_BONUS_H

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
	int		**fd;
	int		cmd_cnt;
	char	*limiter;
	char	**paths;
	char	***commands;
	int		here_doc;
	int		hd[2];
}	t_pipex;

char	*find_correct_path(t_pipex *prog, char *cmd, char **env);
char	*add_chars(char *str, char a);
char	**free_2d_char(char **arr);
void	invalid_file_descriptor(t_pipex *prog);
void	invalid_command(t_pipex *prog, int i);
void	free_prog(t_pipex *prog);
void	wrong_argc(t_pipex *prog);
void	check_for_empty_arg(char **argv);
int		is_all_space(char *str);
void	close_pipes(int i, t_pipex *prog);
void	execve_fail(t_pipex *prog);
char	*get_next_line2(int fd, int k);

#endif