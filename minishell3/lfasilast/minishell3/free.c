/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbjaghou <mbjaghou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/31 07:56:24 by mbjaghou          #+#    #+#             */
/*   Updated: 2022/06/14 03:38:33 by mbjaghou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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