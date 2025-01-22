#include <unistd.h>
#include <sys/wait.h>
#include "./ft_printf/ft_printf.h"
#include "./ft_printf/libft/libft.h"
#include <fcntl.h>

char	**make_command_arr(char *cmd)
{
	char **cmd_arr;

	cmd_arr = ft_split(cmd, ' ');
	return(cmd_arr);
}

char	**extract_env_path(char **env)
{
	int i = 0;
	char	**path_arr;

	while(env[i])
	{
		if(!ft_strncmp(env[i], "PATH=", 5))
		{
			path_arr = ft_split(env[i] + 5, ':');
		}
		i++;
	}
	return(path_arr);
}
char	*find_correct_path(char **cmd_arr, char **paths)
{
	int i = 0;
	while(paths[i])
	{
		ft_st
	}
}
int	main(int argc, char **argv, char **env)
{
	int i = 0;
	int id;
	char **paths;
	if(argc == 5 && argv && env[i])
	{
		paths = extract_env_path(env);
		while(paths[i])
		{
			ft_printf("%s\n", paths[i]);
			i++;
		}
		id = fork();
		if(id == 0)
			ft_printf("I am in child process\n");
		else
		{
			wait(NULL);
			ft_printf("parent process\n");
		}
	}
	else
		write(1, "incorrect number of arguments\n", 30);
}