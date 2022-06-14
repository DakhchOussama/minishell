/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbjaghou <mbjaghou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/11 14:32:43 by mbjaghou          #+#    #+#             */
/*   Updated: 2022/06/14 22:59:49 by mbjaghou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_wait(void)
{
	int		status;

	while (waitpid(-1, &status, 0) != -1)
	{
		if (WIFEXITED(status))
			g_data.exit_code = WEXITSTATUS(status);
		if (WIFSIGNALED(status))
			g_data.exit_code = WTERMSIG(status);
		g_data.forks--;
	}
}

void	ctrl_d(int num)
{
	if (num)
		printf("exit\n");
	rl_clear_history();
	free (g_data.line);
	exit (g_data.exit_code);
}

t_nodes	**ft_parsing(t_nodes **nodes)
{
	char	*str;

	str = ft_strtrim(g_data.line, " ");
	if (!str)
	{
		free(str);
		free(g_data.line);
		return (NULL);
	}
	free(str);
	if (g_data.line)
	{
		nodes = parsing();
		free(g_data.line);
	}
	return (nodes);
}

void	ft_shell(char *envp[], t_env *env, t_nodes *tmp)
{
	t_nodes	**nodes;
	int		num;

	num = 1;
	while (1)
	{
		g_data.line = readline("\e[1;33m$➤ \e[0;37m");
		if (!g_data.line)
			ctrl_d(num);
		nodes = NULL;
		nodes = ft_parsing(nodes);
		tmp = *nodes;
		while (((*nodes)))
		{
			if (execute(nodes, envp, env))
				return ;
			if ((*nodes)->next)
				(*nodes) = (*nodes)->next;
			else
				break ;
		}
		ft_wait();
		*nodes = tmp;
		free_node(nodes);
	}
}

int	main(int ac, char **av, char **envp)
{
	t_env	*env;

	(void)av;
	if (ac != 1 && printf("Error For argument"))
		return (1);
	g_data.forks = 0;
	g_data.exit_code = 1;
	env = stock_env(envp); // stock env
	signal(SIGINT, ft_signal);// control c
	signal(SIGQUIT, ft_signal); // control \;
	g_data.temp = dup(0);
	ft_shell(envp, env, NULL);
	return (0);
}