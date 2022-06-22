/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbjaghou <mbjaghou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/20 20:11:36 by mbjaghou          #+#    #+#             */
/*   Updated: 2022/06/20 20:30:32 by mbjaghou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**fill_tmp_str2(t_env *tmp, int x, char **temp_str)
{
	char	*tmp_name;
	char	*tmp_value;
	char	*value;
	char	*str;

	if (tmp->value)
	{
		tmp_name = ft_strjoin(tmp->name, "=");
		value = ft_strjoin("\"", tmp->value);
		tmp_value = ft_strjoin(value, "\"");
		free(value);
		str = ft_strjoin(tmp_name, tmp_value);
		free(tmp_name);
		free(tmp_value);
	}
	else
	{
		tmp_name = ft_strdup(tmp->name);
		str = ft_strdup(tmp_name);
		free(tmp_name);
	}
	temp_str[x] = ft_strjoin("declare -x ", str);
	free(str);
	return (temp_str);
}

char	**fill_tmp_str(t_env *env, int len)
{
	char	**tmp_str;
	int		i;

	tmp_str = malloc(sizeof(char *) * (len + 1));
	if (!tmp_str)
		return (perror("ERROR"), exit(EXIT_FAILURE), NULL);
	i = 0;
	while (env)
	{
		tmp_str = fill_tmp_str2(env, i, tmp_str);
		i++;
		if (env->next)
			env = env->next;
		else
			break ;
	}
	tmp_str[i + 1] = NULL;
	return (tmp_str);
}

char	**sort_tmp(t_env *env, int len)
{
	int		y;
	int		i;
	char	*tmp;
	char	**tmp_str;

	tmp_str = fill_tmp_str(env, len);
	i = -1;
	y = 0;
	while (++i < len)
	{
		y = i;
		while (++y < len)
		{
			if (tmp_str[y] && ft_strcmp(tmp_str[i], tmp_str[y]) > 0)
			{
				tmp = ft_strdup(tmp_str[i]);
				free(tmp_str[i]);
				tmp_str[i] = ft_strdup(tmp_str[y]);
				free(tmp_str[y]);
				tmp_str[y] = ft_strdup(tmp);
				free(tmp);
			}
		}
	}
	return (tmp_str[i] = NULL, tmp_str);
}

void	sort_and_print(t_env *env)
{
	char	**temp;
	int		i;
	int		len;

	len = len_env(env);
	temp = sort_tmp(env, len);
	i = 0;
	while (i < len)
	{
		if (temp[i][0])
			printf("%s\n", temp[i]);
		i++;
	}
	if (temp)
		free_str(temp);
}

int	get_post(char *str)
{
	int	cmd;
	int	i;

	cmd = 0;
	i = 0;
	while (str[i])
	{
		if (str[i] == '=')
			break ;
		i++;
		cmd++;
	}
	return (cmd);
}
