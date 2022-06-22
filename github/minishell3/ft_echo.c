/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbjaghou <mbjaghou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/10 17:55:16 by mbjaghou          #+#    #+#             */
/*   Updated: 2022/06/10 17:55:36 by mbjaghou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"minishell.h"

int	check_n(char **str, int *j)
{
	int	i;
	int	z;

	i = 1;
	if (str[1] && str[1][0] == '-' && str[1][1] == 'n')
	{
		(*j) = 0;
		while (str[i])
		{
			z = 0;
			while (str[i][++z])
			{
				if (str[i][z] != 'n')
				{	
					if (i == 1)
						(*j) = 1;
					break ;
				}
			}
			if (str[i][z])
				break ;
			i++;
		}
	}
	return (i);
}

void	print_str(char *str)
{
	int	x;

	x = 0;
	while (str[x])
	{
		if (str[x] && str[x] != '\"' && str[x] != '\'')
		{
			printf("%c", str[x]);
			x++;
		}
		else
			x++;
	}
}

void	ft_echo(char **str)
{
	int		i;
	int		j;
	char	*tmp;

	i = 1;
	j = 1;
	while (str[i])
	{
		tmp = ft_strdup(str[i]);
		free(str[i]);
		str[i] = ft_strtrim(tmp, "\"\'");
		free(tmp);
		i++;
	}
	i = check_n(str, &j);
	while (str[i])
	{
		print_str(str[i]);
		if (str[i + 1])
			printf(" ");
		i++;
	}
	if (j == 1)
		printf("\n");
	g_data.exit_code = 0;
}
