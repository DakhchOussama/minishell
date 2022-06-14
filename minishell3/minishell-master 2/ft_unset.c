/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylabtaim <ylabtaim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/02 20:44:58 by yachehbo          #+#    #+#             */
/*   Updated: 2022/04/14 22:46:14 by ylabtaim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_env	*ft_pop(char *name, t_env *env, char *envp[])
{
	t_env	*tmp;

	tmp = env;
	if (!ft_strcmp(env->name, name))
	{
		free_env(env);
		tmp = fill_env(envp + 1);
		return (tmp);
	}
	while (ft_strcmp(env->next->name, name))
		env = env->next;
	free(env->next->name);
	free(env->next->value);
	free(env->next);
	env->next = env->next->next;
	return (tmp);
}

void	pop_last_env(t_env *env, char *cmd_tmp)
{
	while (env)
	{
		if (env->next && !ft_strcmp(env->next->name, cmd_tmp))
		{
			free(env->next->name);
			free(env->next->value);
			free(env->next);
			env->next = NULL;
			break ;
		}
		if (env->next)
			env = env->next;
		else
			break ;
	}
}

t_env	*ft_unset2(t_env *env, t_env *tmp, char *cmd_tmp, char **envp)
{
	while (env->next)
	{
		if (!ft_strcmp(env->name, cmd_tmp))
		{
			tmp = ft_pop(env->name, tmp, envp);
			break ;
		}
		env = env->next;
	}
	if (!env->next)
	{
		env = tmp;
		pop_last_env(env, cmd_tmp);
	}
	return (tmp);
}

t_env	*ft_unset(t_env *env, char **cmd, char *envp[])
{
	int		i;
	t_env	*tmp;
	char	*cmd_tmp;

	i = 1;
	tmp = env;
	while (cmd[i])
	{
		cmd_tmp = ft_strtrim(cmd[i], "\"\'");
		if (check_if_valid(cmd_tmp))
		{
			free(cmd_tmp);
			return (tmp);
		}
		tmp = ft_unset2(env, tmp, cmd_tmp, envp);
		free(cmd_tmp);
		env = tmp;
		i++;
	}
	env = tmp;
	update_envp(env, envp);
	g_data.exit_code = 0;
	return (tmp);
}
