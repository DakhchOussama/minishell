/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbjaghou <mbjaghou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/28 16:30:00 by mbjaghou          #+#    #+#             */
/*   Updated: 2022/06/20 20:25:25 by mbjaghou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_nodes	*ft_nodenew(char *content)
{
	t_nodes	*new;
	char	**str;
	int		i;

	new = (t_nodes *)malloc(sizeof(t_nodes));
	if (!new)
		return (perror("Error"), exit (EXIT_FAILURE), NULL);
	str = ft_split2(content, ' ');
	i = 0;
	while (str[i])
		i++;
	new->cmd = malloc(sizeof(char *) * i + 1);
	if (!new->cmd)
		return (perror("Error"), exit (EXIT_FAILURE), NULL);
	i = 0;
	while (str && str[i])
	{
		new->cmd[i] = ft_strdup(str[i]);
		i++;
	}
	new->cmd[i] = NULL;
	new->next = NULL;
	free_str(str);
	str = NULL;
	return (new);
}

t_nodes	*ft_nodelast(t_nodes *lst)
{
	if (!lst)
		return (0);
	while (lst->next)
		lst = lst->next;
	return (lst);
}

void	new_node(t_nodes **nodes, t_nodes *new)
{
	t_nodes	*last;

	if (!(*nodes))
		*nodes = new;
	else
	{
		last = ft_nodelast(*nodes);
		last->next = new;
		new->prev = last;
	}
}

void	fill1(char **str, t_nodes **nodes)
{
	int	i;

	i = 0;
	while (str[i])
	{
		new_node(nodes, ft_nodenew(str[i]));
		i++;
	}
}

t_nodes	**parsing(void)
{
	t_nodes	**nodes;
	char	**str;
	char	**temp;

	add_history(g_data.line);
	nodes = malloc(sizeof(t_nodes *));
	if (!nodes)
		return (perror("Error"), exit (EXIT_FAILURE), NULL);
	*nodes = NULL;
	if (check_pipes() == 0 || check_quotes() == 0)
		return (NULL);
	if (check_redirect(g_data.line) == -1)
		return (NULL);
	temp = ft_split2(g_data.line, '|');
	str = fill_str2(temp);
	if (!check_redirect_pos(str))
		return (NULL);
	fill1(str, nodes);
	free_str(str);
	free_str(temp);
	temp = NULL;
	str = NULL;
	return (nodes);
}
