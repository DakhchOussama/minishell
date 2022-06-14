/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylabtaim <ylabtaim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/14 14:55:21 by ylabtaim          #+#    #+#             */
/*   Updated: 2022/04/14 14:56:01 by ylabtaim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_if_valid(char *var)
{
	int	i;

	i = 0;
	while (var[i])
	{
		if (!ft_isalnum(var[i]) && var[i] != '_')
		{
			printf("unset: `%s': not a valid identifier\n", var);
			return (1);
		}
		i++;
	}
	return (0);
}

char	**new_envp(t_env *env)
{
	char	**temp_envp;
	char	*tmp_name;
	int		i;

	i = 0;
	temp_envp = malloc(sizeof(char *) * len_env(env) + 1);
	if (!temp_envp)
		exit (EXIT_FAILURE);
	while (env)
	{
		tmp_name = ft_strjoin(env->name, "=");
		temp_envp[i] = ft_strjoin(tmp_name, env->value);
		free(tmp_name);
		if (env->next)
		{
			i++;
			env = env->next;
		}
		else
			break ;
	}
	temp_envp[i + 1] = NULL;
	return (temp_envp);
}

void	update_envp(t_env *env, char **envp)
{
	char	**temp_envp;
	int		i;

	i = 0;
	temp_envp = new_envp(env);
	while (temp_envp[i])
	{
		ft_strlcpy(envp[i], temp_envp[i], ft_strlen(temp_envp[i]) + 1);
		i++;
	}
	free_str(temp_envp);
	if (g_data.exp > 0)
	{
		free(envp[i]);
		g_data.exp--;
	}
	envp[i] = NULL;
}
