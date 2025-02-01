/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: busseven <busseven@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/23 13:21:45 by busseven          #+#    #+#             */
/*   Updated: 2025/02/01 19:16:39 by busseven         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include <stdlib.h>

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

char	*find_correct_path(char *cmd, char **env);
char	*add_chars(char *str, char a);
char	**free_2d_char(char **arr);
void	invalid_file_descriptor(t_pipex *prog);
void	invalid_command(t_pipex *prog, int i);
void	free_prog(t_pipex *prog);
void	check_for_empty_arg(char **argv);
int		is_all_space(char *str);


#endif