/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execut1.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbjaghou <mbjaghou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/13 01:18:31 by mbjaghou          #+#    #+#             */
/*   Updated: 2022/06/20 20:14:33 by mbjaghou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	execution(char **str, char *envp[], t_env *env)
{
	redir(str, 1, -1, 0);
	if (ft_readfile(str))
		return ;
	ft_here(str, env);
	if (!ft_strcmp(str[0], "pwd") || !ft_strcmp(str[0], "PWD")
		|| !ft_strcmp(str[0], "/bin/pwd"))
		ft_pwd();
	else if (!ft_strcmp(str[0], "env") || !ft_strcmp(str[0], "ENV")
		|| !ft_strcmp(str[0], "/usr/bin/env"))
		ft_env1(env);
	else if (!ft_strcmp(str[0], "echo") || !ft_strcmp(str[0], "ECHO")
		|| !ft_strcmp(str[0], "/bin/echo"))
		ft_echo(str);
	else
		exect2(envp, str, env);
	if (dup2(g_data.temp, 0) == -1)
		exit(1);
}
