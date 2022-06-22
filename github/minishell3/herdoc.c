/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   herdoc.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbjaghou <mbjaghou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/19 20:32:11 by mbjaghou          #+#    #+#             */
/*   Updated: 2022/06/19 20:37:12 by mbjaghou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"minishell.h"

void	ft_here2(int i, char **str)
{
	int	x;
	int	fd;

	x = i;
	i += 2;
	while (str[i])
	{
		str[x] = ft_strdup(str[i]);
		x++;
		i++;
	}
	str[x] = NULL;
	fd = open(".tmp", O_RDWR, 1411);
	if (fd == -1)
		exit (EXIT_FAILURE);
	close(0);
	if (dup2(fd, 0) == -1)
		exit(1);
}

void	ft_here(char **str, t_env *env)
{
	int		i;
	int		x;
	char	*tmp;
	int		fd;

	i = 0;
	x = 0;
	while (str[i])
	{
		if (!ft_strcmp(str[i], "<<"))
			break ;
		i++;
	}
	if (str[i] && !ft_strcmp(str[i], "<<"))
	{
		tmp = ft_strdup(heredoc(str[i + 1], env));
		fd = open(".tmp", O_RDWR | O_TRUNC | O_CREAT, 1411);
		if (fd == -1)
			exit (EXIT_FAILURE);
		ft_putstr_fd(tmp, fd);
		close(fd);
		ft_here2(i, str);
	}
}

int	skip_quotes(char *str, int i)
{
	if (str[i] && str[i] == '\'')
	{
		i++;
		while (str[i] != '\'')
			i++;
	}
	if (str[i] && str[i] == '"')
	{
		i++;
		while (str[i] != '"')
			i++;
	}
	return (i);
}

int	check_syntax(char *str)
{
	int	i;

	i = 0;
	while (str[i] && str[i] != '>' && str[i] != '"' && str[i] != '\'')
		i++;
	i = skip_quotes(str, i);
	if (str[i])
	{
		i++;
		if (str[i] && str[i] == '>')
			i++;
		while (str[i] && str[i] == ' ')
			i++;
		if (str[i] && str[i] == '>')
			return (printf("syntax error in unexpected token '>'\n"), -1);
		else if (str[i] && str[i] == '<')
			return (printf("syntax error in unexpected token '<'\n"), -1);
	}
	if (check_other_side(str) == -1)
		return (-1);
	return (0);
}

int	check_redirect(char *str)
{
	int	i;
	int	start;
	int	red_nbr;

	if (check_syntax(str) == -1)
		return (-1);
	i = 0;
	while (str[i])
	{
		red_nbr = 0;
		start = i;
		i = skip_quotes(str, i);
		while (str[i] && (str[i] == '>' || str[i] == '<'))
		{
			red_nbr++;
			i++;
		}
		if (start != i && check_redirect_error(str, start, red_nbr) == -1)
			return (-1);
		i++;
	}
	return (0);
}
