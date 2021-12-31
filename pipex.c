/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sel-mars <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/27 16:20:10 by sel-mars          #+#    #+#             */
/*   Updated: 2021/12/28 19:13:17 by sel-mars         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static char	**ft_path_split(char **envp)
{
	int		i;
	char	*path;
	char	**path_split;

	i = 0;
	while (envp[i] && ft_strncmp(envp[i], "PATH=", 5))
		i++;
	if (!envp[i])
	{
		perror(0);
		exit(0);
	}
	path = ft_substr(envp[i], 5, ft_strlen(envp[i]));
	path_split = ft_split(path, ':');
	return (path_split);
}

static char	*ft_path_search(char **cmd_split, char **envp)
{
	int		i;
	int		ret_access;
	char	*joined_cmd;
	char	*joined_path;
	char	**path_split;

	path_split = ft_path_split(envp);
	joined_cmd = ft_strjoin("/", cmd_split[0]);
	i = 0;
	while (path_split[i])
	{
		joined_path = ft_strjoin(path_split[i], joined_cmd);
		ret_access = access(joined_path, X_OK);
		if (ret_access == 0)
			break ;
		free(joined_path);
		joined_path = NULL;
		i++;
	}
	if (!path_split[i])
	{
		perror(0);
		exit(0);
	}
	return (joined_path);
}

void	ft_child1(char **av, char **envp, int *fd)
{
	int		fd_in;
	char	*path;
	char	**av_cmd;

	dup2(fd[1], 1);
	close(fd[0]);
	close(fd[1]);
	av_cmd = ft_cmd_split(av[2]);
	path = ft_path_search(av_cmd, envp);
	fd_in = open(av[1], O_RDONLY);
	ft_error(fd_in, -1);
	dup2(fd_in, 0);
	close(fd_in);
	execve(path, av_cmd, envp);
}

void	ft_child2(char **av, char **envp, int *fd)
{
	int		fd_out;
	char	*path;
	char	**av_cmd;

	dup2(fd[0], 0);
	close(fd[0]);
	close(fd[1]);
	av_cmd = ft_cmd_split(av[3]);
	path = ft_path_search(av_cmd, envp);
	fd_out = open(av[4], O_RDWR | O_CREAT, 0555);
	dup2(fd_out, 1);
	close(fd_out);
	execve(path, av_cmd, envp);
}

int	main(int ac, char **av, char **envp)
{
	int		fd[2];
	pid_t	pid[2];
	int		ret_pipe;

	ft_error(ac, 5);
	ret_pipe = pipe(fd);
	ft_error(ret_pipe, -1);
	pid[0] = fork();
	ft_error(pid[0], -1);
	if (pid[0] == 0)
		ft_child1(av, envp, fd);
	pid[1] = fork();
	ft_error(pid[1], -1);
	if (pid[1] == 0)
		ft_child2(av, envp, fd);
	close(fd[0]);
	close(fd[1]);
	waitpid(pid[0], NULL, 0);
	waitpid(pid[1], NULL, 0);
}
