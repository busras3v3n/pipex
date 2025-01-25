/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: busseven <busseven@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/23 13:21:45 by busseven          #+#    #+#             */
/*   Updated: 2025/01/25 18:17:52 by busseven         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include <stdlib.h>

typedef struct s_cmd
{
	char	**arg_arr;
	char	*path;
}	t_cmd;

typedef struct s_pipex
{
	int		fd_infile;
	int		fd_outfile;
	t_cmd	**cmd_arr;
	char	**paths;
	int		fd[2];
}	t_pipex;

void	free_prog(t_pipex *prog);
void	invalid_file(t_pipex *prog);
void	invalid_command(char *cmd);
char	**ft_freeall(char **arr);
char	**extract_env_path(char **env);
char	*find_correct_path(char *cmd_arr, char **paths);
char	**make_command_arr(char *cmd);
void	init_program(t_pipex *prog, char **argv, char **env);

#endif