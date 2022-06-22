/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_other.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbjaghou <mbjaghou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/14 03:11:13 by mbjaghou          #+#    #+#             */
/*   Updated: 2022/06/14 03:11:34 by mbjaghou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	execute_other(t_nodes **nodes, char **envp, t_env *env)
{
	int		pid;

	pipe((*nodes)->fi);
	pid = fork();
	g_data.forks++;
	if (!pid)
	{
		if (dup2(g_data.temp, 0) == -1 || close(g_data.temp) == -1
			|| ((*nodes)->next && (dup2((*nodes)->fi[1], 1) == -1
					|| close((*nodes)->fi[0]) == -1
					|| close((*nodes)->fi[1]) == -1)))
			return (1);
		execution((*nodes)->cmd, envp, env);
		exit(g_data.exit_code);
	}
	if (((*nodes)->next && (dup2((*nodes)->fi[0], g_data.temp) == -1
				|| close((*nodes)->fi[0]) == -1
				|| close((*nodes)->fi[1]) == -1))
		|| (!(*nodes)->next && dup2(0, g_data.temp) == -1))
		return (1);
	return (0);
}
