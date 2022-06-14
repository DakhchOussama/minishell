/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_env.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbjaghou <mbjaghou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/09 16:23:12 by ylabtaim          #+#    #+#             */
/*   Updated: 2022/05/24 16:25:45 by mbjaghou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

t_env	*fill_env(char *envp[])
{
	t_env	*env;
	char	cwd[1024];
	int		i;

	i = 0;
	env = NULL;
	while (envp[i]) // if env is not empty
	{
		add_var(&env, envp[i++]);
	}
	if (!envp[0]) // if env is empty
	{
		getcwd(cwd, 1024); // directory (pwd)
		env = (t_env *)malloc(sizeof(t_env));
		if (!env)
			return (perror("Error"), exit (EXIT_FAILURE), NULL);
		env->name = ft_strdup("PWD");
		env->value = ft_strdup(cwd);
		env->next = NULL;
	}
	return (env);
}
