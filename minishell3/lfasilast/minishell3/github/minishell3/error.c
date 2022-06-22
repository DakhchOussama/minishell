/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbjaghou <mbjaghou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/28 16:30:09 by mbjaghou          #+#    #+#             */
/*   Updated: 2022/05/28 16:30:11 by mbjaghou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	print_error_2(int i, char c)
{
	if (c == 'i')
	{
		ft_putstr_fd("minishell: syntax error near unexpected token `", 2);
		if (i > 5)
			ft_putstr_fd("<<<'\n", 2);
		else if (i > 4)
			ft_putstr_fd("<<'\n", 2);
		else
			ft_putstr_fd("<'\n", 2);
		g_data.exit_code = 258;
	}
	else if (c == 'o')
	{
		ft_putstr_fd("minishell: syntax error near unexpected token `", 2);
		if (i >= 4)
			ft_putstr_fd(">>'\n", 2);
		else
			ft_putstr_fd(">'\n", 2);
		g_data.exit_code = 258;
	}
	return (-1);
}

int	print_error(void)
{
	printf("minishell: syntax error near unexpected token `|'\n");
	return (0);
}

int	redirect_count_err(char *str)
{
	int	i;
	int	compteur;

	i = 0;
	while (str[i])
	{
		compteur = 0;
		while (str[i] && str[i] == '>')
		{
			compteur++;
			i++;
		}
		if (compteur > 2)
			return (print_error_2(compteur, 'o'));
		compteur = 0;
		while (str[i] && str[i] == '<')
		{
			compteur++;
			i++;
		}
		if (compteur > 1)
			return (print_error_2(compteur, 'i'));
		i++;
	}
	return (0);
}

int	check_redirect_error(char *str, int start, int red_nbr)
{
	char	*tmp;

	if (red_nbr > 0)
	{
		tmp = ft_substr(str, start, red_nbr);
		if (!valid_redirect(tmp, red_nbr))
		{
			redirect_count_err(str);
			free(str);
			return (-1);
		}
		free(str);
	}
	return (0);
}
