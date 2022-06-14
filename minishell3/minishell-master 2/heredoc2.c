/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylabtaim <ylabtaim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/09 23:20:16 by yachehbo          #+#    #+#             */
/*   Updated: 2022/04/14 21:56:08 by ylabtaim         ###   ########.fr       */
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
