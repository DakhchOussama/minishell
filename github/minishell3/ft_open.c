/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_open.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbjaghou <mbjaghou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/19 20:12:36 by mbjaghou          #+#    #+#             */
/*   Updated: 2022/06/19 20:37:48 by mbjaghou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_open(int j, char *p_file)
{
	int	fd;

	fd = 0;
	if (j == 1)
	{
		fd = open(p_file, O_RDWR | O_TRUNC | O_CREAT, 1411);
		free(p_file);
		p_file = NULL;
	}
	else if (j == 2)
	{
		fd = open(p_file, O_RDWR | O_APPEND | O_CREAT, 1411);
		free(p_file);
		p_file = NULL;
	}
	if (fd < 0)
	{
		printf("minishell: %s: %s\n", p_file, strerror(errno));
		exit (1);
	}
	return (fd);
}
