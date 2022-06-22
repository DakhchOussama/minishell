/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_file.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbjaghou <mbjaghou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/19 20:18:09 by mbjaghou          #+#    #+#             */
/*   Updated: 2022/06/19 20:18:25 by mbjaghou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	readfile_help(char **str, int i, int x)
{
	int	fd;

	fd = open(str[i + 1], O_RDWR);
	if (fd < 0)
	{
		printf("minishell: %s: %s\n", str[i + 1], strerror(errno));
		return (1);
	}
	else
	{
		x = i;
		i += 2;
		if (dup2(fd, 0) == -1)
			exit(1);
		while (str[i])
		{
			str[x] = ft_strdup(str[i]);
			x++;
			i++;
		}
		if (!str[i])
			str[x] = NULL;
	}
	return (0);
}

int	ft_readfile(char **str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (!ft_strcmp(str[i], "<"))
			break ;
		i++;
	}
	if (str[i] && !ft_strcmp(str[i], "<") && str[i + 1])
	{
		if (readfile_help(str, i, 0))
			return (1);
	}
	return (0);
}
