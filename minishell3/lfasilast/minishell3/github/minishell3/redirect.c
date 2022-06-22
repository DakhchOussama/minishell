/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbjaghou <mbjaghou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/19 20:10:16 by mbjaghou          #+#    #+#             */
/*   Updated: 2022/06/20 20:25:10 by mbjaghou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_cmd(char **str, int i, char *tmp)
{
	int	x;

	if (i == 0 && ft_strcmp(str[i], ">") && ft_strcmp(str[i], ">>")
		&& str[i][0] != '>')
	{
		tmp = ft_strjoin(tmp, str[i]);
		tmp = ft_strjoin(tmp, " ");
	}
	else if (i != 0 && (ft_strcmp(str[i - 1], ">")
			&& ft_strcmp(str[i - 1], ">>"))
		&& str[i - 1][ft_strlen(str[i - 1]) - 1] != '>' && str[i][0] != '>')
	{
		x = 0;
		while (str[i][x])
		{
			if (str[i][x] != '>')
				x++;
			else
				break ;
		}
		str[i][x] = '\0';
		tmp = ft_strjoin(tmp, str[i]);
		tmp = ft_strjoin(tmp, " ");
	}
	return (tmp);
}

void	upd_cmd(char **str)
{
	int		i;
	char	*tmp;
	char	**temp;

	i = 0;
	tmp = ft_strdup("");
	while (str[i])
	{
		if (ft_strcmp(str[i], ">") && ft_strcmp(str[i], ">>"))
			tmp = get_cmd(str, i, tmp);
		i++;
	}
	i = 0;
	temp = ft_split(tmp, ' ');
	free(tmp);
	tmp = NULL;
	while (temp[i])
	{
		str[i] = ft_strdup(temp[i]);
		i++;
	}
	if (i != 0 || !temp[0])
		str[i] = NULL;
	free_str(temp);
	temp = NULL;
}

char	*get_file_name(char *str, int x)
{
	int		i;
	int		j;
	char	*file;

	i = 0;
	j = x + 1;
	while (str[j] && str[j] != '>')
	{
		i++;
		j++;
	}
	file = malloc(sizeof(char) * (i + 1));
	if (!file)
		return (perror("Error"), exit (EXIT_FAILURE), NULL);
	j = 0;
	x = x + 1;
	while (str[x] && j < i)
	{
		file[j] = str[x];
		x++;
		j++;
	}
	file[j] = '\0';
	return (file);
}

int	redirect_help(int *i, int *j, int *x, char **str)
{
	int		fd;
	char	*p_file;

	(*j) = 1;
	if (str[(*i)][(*x) + 1] && str[(*i)][(*x) + 1] == '>')
	{
		(*j) = 2;
		(*x) = (*x) + 1;
	}
	if (!str[(*i)][(*x) + 1])
	{
		(*i) = (*i) + 1;
		(*x) = -1;
	}
	p_file = get_file_name(str[(*i)], (*x));
	fd = ft_open((*j), p_file);
	return (fd);
}

void	redir(char **str, int kk, int i, int j)
{
	int		x;
	int		fd;

	while (str[++i])
	{
		x = -1;
		if (str[i][0] != '\"' && str[i][0] != '\'')
		{
			while (str[i][++x])
			{
				if (str[i][x] == '>')
					fd = redirect_help(&i, &j, &x, str);
			}
		}
	}
	if (j != 0)
		upd_cmd(str);
	if (kk == 1 && fd)
	{
		dup2(fd, 1);
		close(fd);
	}
}
