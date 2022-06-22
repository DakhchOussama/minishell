/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env1.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbjaghou <mbjaghou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/11 17:17:17 by mbjaghou          #+#    #+#             */
/*   Updated: 2022/06/11 17:17:47 by mbjaghou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_env1(t_env *env)
{
	while (env)
	{
		if (env->value)
			printf("%s=%s\n", env->name, env->value);
		if (env->next)
			env = env->next;
		else
			break ;
	}
	g_data.exit_code = 0;
}
