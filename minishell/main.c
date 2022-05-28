/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbjaghou <mbjaghou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/11 14:32:43 by mbjaghou          #+#    #+#             */
/*   Updated: 2022/05/26 18:45:58 by mbjaghou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void ctrl_d(int num)
{
	if (num)
		printf("exit\n");
	rl_clear_history();
	free (g_data.line);
	exit (g_data.exit_code);
}

t_nodes **ft_parsing(t_nodes **nodes)
{
	char *str;

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

void ft_shell(void)
{
	t_nodes	**nodes;
	int num;

	num = 1;
	while (1)
	{
		g_data.line = readline("\e[1;33m$➤ \e[0;37m");
		if (!g_data.line)
			ctrl_d(num);
		nodes = NULL;
		nodes = ft_parsing(nodes);
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
	env = stock_env(envp);
	signal(SIGINT, ft_signal);
	signal(SIGQUIT, ft_signal);
	g_data.temp = dup(0); // stock input
	// ft_shell(envp, env, dup(1));
	ft_shell();
	return (0);
}