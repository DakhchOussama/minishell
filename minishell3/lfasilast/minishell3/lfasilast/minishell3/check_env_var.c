/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_env_var.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbjaghou <mbjaghou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/08 17:45:47 by mbjaghou          #+#    #+#             */
/*   Updated: 2022/06/12 22:05:00 by mbjaghou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

char	*change_tab(char *table, char *str, char *value, char *tmp)
{
	char	*temp2;

	// VALUE == /Users/mbjaghou
	// table == HOME
	// name == $HOME
	//tmp == string
	temp2 = ft_strdup(table);
	free(table);
	table = ft_strjoin(value, tmp); // /Users/mbjaghou string
	if (table && !table[0] && check_single(str) == 1)  // echo '$HOME' => $HOME
	{
		free(table);
		table = ft_strjoin("$", temp2);
	}
	free(temp2);
	return (table);
}

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
		//alocate name 
		value = get_val(env, name);
		// change name to value
		tmp = ft_strdup(table[x] + j);
		table[x] = change_tab(table[x], str, value, tmp);
		// VALUE == /Users/mbjaghou
		// table == HOME + 5
		// name == $HOME
		//tmp == $HOME
		// str == "$HOME $USER"
		 // table[x] == /Users/mbjaghou string || mbjaghou
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

void	check_env_var(char **str, t_env *env) // str == cmd;
{
	int		i;
	int		x;
	char	**table;

	i = 1;
	while (str[i])
	{
		table = fill_table(str[i], env, 1, 0);
		// split str and alocate name and change name to value 
		// table[x] == /Users/mbjaghou string || mbjaghou
		x = 0;
		str[i][0] = '\0';
		if (table[x] && table[x][0] == '\0') 
		// table is empty == !ft_strcmp(table[x], "");
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