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

void ctrl_d(void)
{
	printf("exit\n");
	rl_clear_history();
	free (g_data.line);
	exit (g_data.exit_code);
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
	while (1)
	{
		g_data.line = readline("\e[1;33m$➤ \e[0;37m");
		if (!g_data.line)
			ctrl_d();
	}
}