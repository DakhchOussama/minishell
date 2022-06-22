/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_name.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbjaghou <mbjaghou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/08 18:53:11 by mbjaghou          #+#    #+#             */
/*   Updated: 2022/06/12 21:46:32 by mbjaghou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*alloc_name(char *table)
{
	char	*name;
	int		j;

	j = 0;
	while (table[j])
	{
		if (ft_isdigit(table[j]) && j == 0)
		{
			j++;
			break ;
		}
		if (!ft_isalnum(table[j]) && table[j] != '?'
			&& table[j] != '\'')
			break ;
		if (table[j] == '?')
		{
			j++;
			break ;
		}
		j++;
	}
	name = malloc(sizeof(char) * j);
	if (!name)
		exit (EXIT_FAILURE);
	return (name);
}

char	*fill_name(char *table, int *j)
{
	char	*name;

	name = alloc_name(table);
	while (table[*j])
	{
		if ((ft_isdigit(table[*j]) && *j == 0) || table[*j] == '?')
		{
			name[*j] = table[*j];
			(*j)++;
			break ;
		}
		else if (!ft_isalnum(table[*j]) && table[*j] != '?'
			&& table[*j] != '\'')
			break ;
		else
			name[*j] = table[*j];
		(*j)++;
	}
	name[*j] = '\0';
	return (name);
}
