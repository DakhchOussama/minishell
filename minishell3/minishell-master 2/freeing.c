/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   freeing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yachehbo <yachehbo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/29 18:52:54 by ylabtaim          #+#    #+#             */
/*   Updated: 2022/04/14 14:03:35 by yachehbo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_node(t_nodes **node)
{
	t_nodes	*next;
	t_nodes	*tmp;

	next = (*node)->next;
	free((*node));
	free_str((*node)->cmd);
	while (next)
	{
		tmp = next;
		next = next->next;
		free(tmp);
		free_str(tmp->cmd);
	}
	free(node);
}

void	free_env(t_env *env)
{
	t_env	*next;
	t_env	*tmp;

	next = NULL;
	if (env)
	{
		next = env->next;
		free(env->name);
		free(env->value);
		free(env);
	}
	while (next)
	{
		tmp = next;
		next = next->next;
		free(tmp->name);
		free(tmp->value);
		free(tmp);
	}
}

void	free_str(char **str)
{
	int	i;

	i = 0;
	while (str && str[i])
	{
		free (str[i]);
		str[i] = NULL;
		i++;
	}
	if (str)
		free (str);
}
