/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exect2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbjaghou <mbjaghou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/14 03:12:44 by mbjaghou          #+#    #+#             */
/*   Updated: 2022/06/14 23:00:45 by mbjaghou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
		str[0] = ft_strdup(cmd);
		str[0] = ft_strjoin("/", str[0]);
		str[0] = ft_strjoin(paths[i], str[0]);
		execve(str[0], str, envp);
		i++;
	}
	printf("minishell: %s : command not found\n", cmd);
	g_data.exit_code = 127;
	exit(g_data.exit_code);
}

void	check_env_var(char **str, t_env *env)
{
	int		i;
	int		x;
	char	**table;

	i = 1;
	while (str[i])
	{
		table = fill_table(str[i], env, 1, 0);
		x = 0;
		str[i][0] = '\0';
		if (table[x] && table[x][0] == '\0')
		{
			free_str(table);
			table[x] = NULL;
			i++;
			continue ;
		}	
		while (table[x])
			str[i] = change_str(str[i], table[x++]);
		free_str(table);
		i++;
	}
}

int	valid_redirect(char *tmp, int red_nbr)
{
	if (ft_strncmp(tmp, ">", red_nbr) == 0 || ft_strncmp(tmp, "<", red_nbr) == 0
		|| ft_strncmp(tmp, ">>", red_nbr) == 0
		|| ft_strncmp(tmp, "<<", red_nbr) == 0)
		return (1);
	else
		return (0);
}
