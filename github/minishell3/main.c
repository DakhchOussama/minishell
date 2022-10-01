/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: odakhch <mbjaghou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/11 14:32:43 by odakhch          #+#    #+#             */
/*   Updated: 2022/06/20 20:25:38 by odakhch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_nodes	**ft_parsing(t_nodes **nodes)
{
	char	*str;

	str = ft_strtrim(g_data.line, " ");
	if (!ft_strcmp(str, ""))
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

void	ft_shell(char *envp[], t_env *env, int dp, t_nodes *tmp)
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
			if (execute(nodes, envp, env, dp))
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
	g_data.exp = 0;
	g_data.forks = 0;
	g_data.exit_code = 1;
	env = stock_env(envp);
	signal(SIGINT, ft_signal);
	signal(SIGQUIT, ft_signal);
	g_data.temp = dup(0);
	ft_shell(envp, env, dup(1), NULL);
	return (0);
}
