/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exect.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylabtaim <ylabtaim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/01 17:59:15 by ylabtaim          #+#    #+#             */
/*   Updated: 2022/04/14 21:51:12 by ylabtaim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	exec_it(char **str, char **envp, t_env *env)
{
	char	**paths;
	char	*cmd;
	int		i;

	paths = ft_split(get_val(env, "PATH"), ':');
	if (!paths[0])
	{
		printf("minishell: %s: No such file or directory\n", str[0]);
		exit(127);
	}
	i = 0;
	cmd = ft_strdup(str[0]);
	while (paths[i])
	{
		execve(str[0], str, envp);
		str[0] = ft_strdup(cmd);
		str[0] = ft_strjoin("/", str[0]);
		str[0] = ft_strjoin(paths[i], str[0]);
		i++;
	}
	printf("minishell: %s : command not found\n", cmd);
	g_data.exit_code = 127;
	exit(g_data.exit_code);
}

void	exect2(char **envp, char **str, t_env *env)
{
	int	pid;
	int	status;

	pid = fork();
	g_data.forks++;
	if (pid == 0)
	{
		str[1] = ft_strtrim(str[1], "\"\'");
		exec_it(str, envp, env);
	}
	if (waitpid(0, &status, 0) != 0)
	{
		g_data.forks--;
		if (WIFEXITED(status))
			g_data.exit_code = WEXITSTATUS(status);
		if (WIFSIGNALED(status))
			g_data.exit_code = WTERMSIG(status);
	}
}

void	execution(char **str, char *envp[], t_env *env)
{
	redir(str, 1, -1, 0);
	if (ft_readfile(str))
		return ;
	ft_here(str, env);
	if (!ft_strcmp(str[0], "echo") || !ft_strcmp(str[0], "ECHO")
		|| !ft_strcmp(str[0], "/bin/echo"))
		ft_echo(str);
	else if (!ft_strcmp(str[0], "pwd") || !ft_strcmp(str[0], "PWD")
		|| !ft_strcmp(str[0], "/bin/pwd"))
		ft_pwd();
	else if (!ft_strcmp(str[0], "env") || !ft_strcmp(str[0], "ENV")
		|| !ft_strcmp(str[0], "/usr/bin/env"))
		ft_env(env);
	else
		exect2(envp, str, env);
	if (dup2(g_data.temp, 0) == -1)
		exit(1);
}
