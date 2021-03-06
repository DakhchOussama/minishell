/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stock_env.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbjaghou <mbjaghou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/25 15:58:51 by mbjaghou          #+#    #+#             */
/*   Updated: 2022/06/10 16:48:38 by mbjaghou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_signal(int signum)
{
	g_data.exit_code = 128 + signum;
	if (signum == SIGINT)
	{
		if (g_data.forks == 1 || g_data.forks == 0)
			printf("\n");
		if (g_data.forks == 0)
			rl_on_new_line();
		rl_redisplay();
	}
	else if (signum == SIGQUIT)
	{
		if (g_data.forks == 1)
		{
			printf("Quit: \n");
		}
		else
		{
			rl_on_new_line();
			rl_redisplay();
		}
	}
}

char	*get_value(char *line)
{
	int	start;
	int	len;
	int	i;

	start = 0;
	while (line[start] && line[start] != '=')
		start++;
	start++;
	len = 0;
	i = start;
	while (line[i])
	{
		i++;
		len++;
	}	
	return (ft_substr(line, start, len));
}

char	*get_name(char *line)
{
	int	len;

	len = 0;
	while (line[len] && line[len] != '=')
		len++;
	return (ft_substr(line, 0, len));
}

int	add_var(t_env **env, char *line)
{
	t_env	*var;
	t_env	*head;

	var = (t_env *)malloc(sizeof(t_env));
	if (!var)
		return (perror("Error"), exit (EXIT_FAILURE), 1);
	var->name = get_name(line);
	var->value = get_value(line);
	var->next = NULL;
	if (!*env)
		return (*env = var, 0);
	head = *env;
	while (head->next)
		head = head->next;
	head->next = var;
	return (0);
}

t_env	*stock_env(char **envp)
{
	t_env	*env;
	char	cwd[1024];
	int		i;

	i = 0;
	env = NULL;
	while (envp[i])
	{
		add_var(&env, envp[i++]);
	}
	if (!envp[0])
	{
		getcwd(cwd, 1024);
		env = (t_env *)malloc(sizeof(t_env));
		if (!env)
			return (perror("Error"), exit (1), NULL);
		env->name = ft_strdup("PWD");
		env->value = ft_strdup(cwd);
		env->next = NULL;
	}
	return (env);
}
