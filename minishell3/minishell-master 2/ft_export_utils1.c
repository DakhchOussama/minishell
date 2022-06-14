/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export_utils1.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylabtaim <ylabtaim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/14 17:11:10 by ylabtaim          #+#    #+#             */
/*   Updated: 2022/04/14 23:17:39 by ylabtaim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	len_env(t_env *tmp)
{
	int	len;

	len = 0;
	while (tmp)
	{
		len++;
		tmp = tmp->next;
	}
	return (len);
}

char	**fill_tmp_str2(t_env *tmp, int x, char **temp_str)
{
	char	*tmp_name;
	char	*tmp_value;
	char	*str;
	char	*value;

	if (tmp->value)
	{
		tmp_name = ft_strjoin(tmp->name, "=");
		value = ft_strjoin("\"", tmp->value);
		tmp_value = ft_strjoin(value, "\"");
		free(value);
		str = ft_strjoin(tmp_name, tmp_value);
		free(tmp_value);
		free(tmp_name);
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

char	**fill_tmp_str(t_env *tmp, int len)
{
	char	**temp_str;
	int		x;

	temp_str = malloc(sizeof(char *) * (len + 1));
	if (!temp_str)
		return (perror("Error"), exit (EXIT_FAILURE), NULL);
	x = 0;
	while (tmp)
	{
		temp_str = fill_tmp_str2(tmp, x, temp_str);
		x++;
		if (tmp->next)
			tmp = tmp->next;
		else
			break ;
	}
	temp_str[x + 1] = NULL;
	return (temp_str);
}

char	**sort_tmp_str(t_env *env, int len)
{
	int		x;
	int		i;
	char	*temp;
	char	**temp_str;

	temp_str = fill_tmp_str(env, len);
	i = -1;
	x = 0;
	while (++i < len)
	{
		x = i;
		while (++x < len)
		{
			if (temp_str[x] && ft_strcmp(temp_str[i], temp_str[x]) > 0)
			{
				temp = ft_strdup(temp_str[i]);
				free(temp_str[i]);
				temp_str[i] = ft_strdup(temp_str[x]);
				free(temp_str[x]);
				temp_str[x] = ft_strdup(temp);
				free (temp);
			}
		}
	}
	return (temp_str[i] = NULL, temp_str);
}

void	new_env_var(char *name, char *value, t_env *env)
{
	t_env	*new;

	new = (t_env *)malloc(sizeof(t_env));
	if (!new)
		exit (EXIT_FAILURE);
	new->name = ft_strdup(name);
	if (value)
		new->value = ft_strdup(value);
	else
		new->value = NULL;
	new->next = NULL;
	env->next = new;
}
