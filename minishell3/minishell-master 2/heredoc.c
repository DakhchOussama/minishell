/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylabtaim <ylabtaim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/20 19:35:06 by ylabtaim          #+#    #+#             */
/*   Updated: 2022/04/14 22:09:20 by ylabtaim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_strcmp(char *s1, char *s2)
{
	int	i;

	i = 0;
	while (s1[i] == s2[i] && s1[i] != '\0' && s2[i] != '\0')
		i++;
	return (s1[i] - s2[i]);
}

char	*heredoc_name(char **table, int *j, int *x)
{
	char	*name;

	name = malloc(sizeof(char) * (*j));
	if (!name)
		exit (EXIT_FAILURE);
	(*j) = 0;
	while (table[(*x)][(*j)])
	{
		if (!ft_isalnum(table[(*x)][(*j)]) && table[(*x)][(*j)] != '?')
			break ;
		else
			name[(*j)] = table[(*x)][(*j)];
		(*j)++;
	}
	name[(*j)] = '\0';
	return (name);
}

char	*here_fill(char **table, int x, t_env *env)
{
	char	*name;
	char	*value;
	char	*tmp;
	int		j;

	j = 0;
	while (table[x][j])
	{
		if (!ft_isalnum(table[x][j]) && table[x][j] != '?')
			break ;
		j++;
	}
	name = heredoc_name(table, &j, &x);
	value = get_val(env, name);
	free(name);
	name = NULL;
	tmp = ft_strdup(table[x] + j);
	free(table[x]);
	table[x] = ft_strjoin(value, tmp);
	free(value);
	free(tmp);
	return (table[x]);
}

char	*change_var(char *str, t_env *env)
{
	int		x;
	char	**table;
	char	*tmpp;

	x = 0;
	if (str[0] == '$')
		x = -1;
	table = ft_split(str, '$');
	while (table[++x])
		table[x] = here_fill(table, x, env);
	x = 0;
	str[0] = '\0';
	if (table[x] && table[x][0] == '\0')
		return (free_str(table), NULL);
	while (table[x])
	{
		tmpp = ft_strdup(str);
		free(str);
		str = ft_strjoin(tmpp, table[x]);
		free(tmpp);
		x++;
	}
	free_str(table);
	return (str);
}

char	*heredoc(char *av, t_env *env)
{
	char	*data;
	char	*res;
	char	*var;
	char	*res2;

	data = readline(">");
	if (!data)
		ctrl_d(0);
	res = ft_strdup("");
	while (ft_strcmp(av, data))
	{
		res2 = change_var(data, env);
		var = ft_strjoin(res, res2);
		free(res2);
		free(res);
		res = ft_strjoin(var, "\n");
		free(var);
		data = readline(">");
		if (!data)
			ctrl_d(0);
	}
	free(data);
	return (res);
}
