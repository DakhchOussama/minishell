/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_var_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yachehbo <yachehbo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/14 02:12:32 by yachehbo          #+#    #+#             */
/*   Updated: 2022/04/14 02:15:07 by yachehbo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_val(t_env *env, char *name)
{
	while (env)
	{
		if (!ft_strcmp(env->name, name))
			return (ft_strdup(env->value));
		env = env->next;
	}
	if (name[0] == '?')
	{
		return (ft_itoa(g_data.exit_code));
	}
	return (ft_strdup(""));
}

char	*alloc_tmp(int *x, int *j)
{
	char	*tmp;

	if (*x == 1)
	{
		(*j) = (*j) - 3;
		tmp = malloc(sizeof(char) * (*j) + 1);
		if (!tmp)
			return (perror("Error"), exit (EXIT_FAILURE), NULL);
		(*x) = (*x) + 1;
	}
	else
	{
		(*j) = (*j) - 1;
		tmp = malloc(sizeof(char) * (*j) + 1);
		if (!tmp)
			return (perror("Error"), exit (EXIT_FAILURE), NULL);
		(*x) = (*x) + 1;
	}
	return (tmp);
}

char	*save_it(char *str, int x, t_env *env)
{
	int		i;
	int		j;
	char	*tmp;
	char	*tab;

	j = ft_strlen(str);
	tmp = alloc_tmp(&x, &j);
	j += x;
	i = 0;
	while (x < j)
	{	
		tmp[i] = str[x];
		i++;
		x++;
	}
	tmp[i] = '\0';
	tab = get_val(env, tmp);
	if (!tab)
		tab = ft_strdup("");
	return (tab);
}

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

int	check_single(char *str)
{
	int	x;
	int	z;

	x = 0;
	z = 0;
	while (str[x])
	{
		if (str[x] == '\'')
			z = 1;
		x++;
	}
	return (z);
}
