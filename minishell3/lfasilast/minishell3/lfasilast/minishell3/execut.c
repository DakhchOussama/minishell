/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execut.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbjaghou <mbjaghou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/08 17:35:14 by mbjaghou          #+#    #+#             */
/*   Updated: 2022/06/14 03:14:49 by mbjaghou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_exit(char **str, int i)
{
	char	*trim;

	printf("exit\n");
	trim = ft_strtrim(str[1], "'\"");
	if (trim && !ft_isdigit(trim[0]) && trim[0] != '-' && trim[0] != '+')
	{
		printf("exit: %s: numeric argument required\n", trim);
		exit(EXIT_SUCCESS);
	}
	if (str[1] && str[2])
	{
		printf("exit: too many arguments\n");
		free(trim);
		return ;
	}
	while (trim && trim[++i])
	{
		if (!ft_isdigit(trim[i]) && trim[i] != '\'' && trim[i] != '"')
		{
			printf("exit: %s: numeric argument required\n", trim);
			break ;
		}
	}
	exit(EXIT_SUCCESS);
}


int	execute(t_nodes **nodes, char **envp, t_env *env, int dp)
{
	check_env_var((*nodes)->cmd, env);
	/*change name to value;*/
	if (!ft_strcmp((*nodes)->cmd[0], "cd")
		|| !ft_strcmp((*nodes)->cmd[0], "/usr/bin/cd"))
		ft_cd((*nodes)->cmd, env);
	else if (!ft_strcmp((*nodes)->cmd[0], "unset"))
		env = ft_unset(env, (*nodes)->cmd, envp);
	else if (!ft_strcmp((*nodes)->cmd[0], "export"))
	{
		ft_export(env, (*nodes)->cmd, envp);
		close (1);
		if (dup2(dp, 1) == -1)
			exit (1);

	}
	else if (!ft_strcmp((*nodes)->cmd[0], "exit"))
		ft_exit((*nodes)->cmd, 0);
	else
	{
		if (execute_other(nodes, envp, env))
			return (1);
	}
	return (0);
}
