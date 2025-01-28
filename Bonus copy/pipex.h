/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: busseven <busseven@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/23 13:21:45 by busseven          #+#    #+#             */
/*   Updated: 2025/01/28 20:08:23 by busseven         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include <stdlib.h>

typedef struct s_pipex
{
	int		fd_infile;
	int		fd_outfile;
	char	***commands;
	char	**paths;
	int		**fd;
}	t_pipex;

void	free_prog(t_pipex *prog, int argc);
void	invalid_file(t_pipex *prog);
void	invalid_command(t_pipex *prog, char *cmd);
char	**ft_freeall(char **arr);
char	**extract_env_path(char **env);
char	*find_correct_path(char *cmd_arr, char **paths);
char	**make_command_arr(char *cmd);
void	init_program(t_pipex *prog, char **argv, int argc, char **env);
char	**free_2d_char(char **arr);
char	*add_chars(char *str, char a);

#endif