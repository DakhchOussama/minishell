/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_var.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yachehbo <yachehbo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/08 17:56:42 by yachehbo          #+#    #+#             */
/*   Updated: 2022/04/14 02:14:30 by yachehbo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

char	*change_tab(char *table, char *str, char *value, char *tmp)
{
	char	*temp2;

	temp2 = ft_strdup(table);
	free(table);
	table = ft_strjoin(value, tmp);
	if (table && !table[0] && check_single(str) == 1)
	{
		free(table);
		table = ft_strjoin("$", temp2);
	}
	free(temp2);
	return (table);
}

char	**fill_table(char *str, t_env *env, int x, int j)
{
	char	**table;
	char	*name;
	char	*value;
	char	*tmp;

	table = NULL;
	table = ft_split(str, '$');
	if (str[0] == '$')
		x = 0;
	while (table[x])
	{
		j = 0;
		name = fill_name(table[x], &j);
		value = get_val(env, name);
		tmp = ft_strdup(table[x] + j);
		table[x] = change_tab(table[x], str, value, tmp);
		free(value);
		free(tmp);
		free(name);
		x++;
	}
	return (table);
}

char	*change_str(char *str, char *tab)
{
	char	*tmpp;

	tmpp = ft_strdup(str);
	free(str);
	str = ft_strjoin(tmpp, tab);
	free(tmpp);
	return (str);
}

void	check_env_var(char **str, t_env *env)
{
	int		i;
	int		x;
	char	**table;

	i = 1;
	while (str[i])
	{
		table = fill_table(str[i], env, 1, 0);
		x = 0;
		str[i][0] = '\0';
		if (table[x] && table[x][0] == '\0')
		{
			free_str(table);
			table[x] = NULL;
			i++;
			continue ;
		}	
		while (table[x])
			str[i] = change_str(str[i], table[x++]);
		free_str(table);
		i++;
	}
}
