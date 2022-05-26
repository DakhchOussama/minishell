/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbjaghou <mbjaghou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/11 14:32:43 by mbjaghou          #+#    #+#             */
/*   Updated: 2022/05/26 18:45:58 by mbjaghou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(int ac, char **av, char **envp)
{
	t_env	*env;

	if (ac != 1 && printf("Error For argument"))
		return (1);
	env = stock_env(envp);
	while (1)
	{
		g_data.line = readline("\e[1;33m$➤ \e[0;37m");
	}
}