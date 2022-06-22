/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbjaghou <mbjaghou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/11 17:16:00 by mbjaghou          #+#    #+#             */
/*   Updated: 2022/06/20 20:26:20 by mbjaghou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_pwd(void)
{
	char	cwd[1024];

	getcwd(cwd, 1024);
	printf("%s\n", cwd);
	g_data.exit_code = 0;
}

void	ctrl_d(int num)
{
	if (num)
		printf("exit\n");
	rl_clear_history();
	free (g_data.line);
	exit (g_data.exit_code);
}

void	ft_wait(void)
{
	int		status;

	while (waitpid(-1, &status, 0) != -1)
	{
		if (WIFEXITED(status))
			g_data.exit_code = WEXITSTATUS(status);
		if (WIFSIGNALED(status))
			g_data.exit_code = WTERMSIG(status);
		g_data.forks--;
	}
}

char	**fill_str2(char **temp)
{
	char	**str;
	int		i;

	i = 0;
	while (temp && temp[i])
		i++;
	str = malloc(sizeof(char *) * i + 1);
	i = 0;
	while (temp && temp[i])
	{
		str[i] = ft_strtrim(temp[i], " ");
		i++;
	}
	str[i] = NULL;
	return (str);
}

int	ft_strcmp(char *s1, char *s2)
{
	int	i;

	i = 0;
	while (s1[i] == s2[i] && s1[i] != '\0' && s2[i] != '\0')
		i++;
	return (s1[i] - s2[i]);
}
