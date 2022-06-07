/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbjaghou <mbjaghou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/28 16:30:00 by mbjaghou          #+#    #+#             */
/*   Updated: 2022/05/31 14:41:20 by mbjaghou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_nodes	**parsing(void)
{
	t_nodes	**nodes;
	char	**str;
	char	**temp;

	add_history(g_data.line);
	nodes = malloc(sizeof(t_nodes *));
	if (!nodes)
		return (perror("Error"), exit (EXIT_FAILURE), NULL);
	if (check_pipes() == 0 || check_quotes() == 0)
		return (NULL);
	temp = ft_split2(g_data.line, '|');
	str = fill_str2(temp);
	if (!check_redirect_pos(str))
		return (NULL);
	free_str(str);
	free_str(temp);
	temp = NULL;
	str = NULL;
	return (nodes);
}
