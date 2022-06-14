/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execut.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbjaghou <mbjaghou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/08 17:35:14 by mbjaghou          #+#    #+#             */
/*   Updated: 2022/06/14 03:14:49 by mbjaghou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_exit(char **str, int i)
{
	char	*trim;

	printf("exit\n");
	trim = ft_strtrim(str[1], "'\"");
	if (trim && !ft_isdigit(trim[0]) && trim[0] != '-' && trim[0] != '+')
	{
		printf("exit: %s: numeric argument required\n", trim);
		exit(EXIT_SUCCESS);
	}
	if (str[1] && str[2])
	{
		printf("exit: too many arguments\n");
		free(trim);
		return ;
	}
	while (trim && trim[++i])
	{
		if (!ft_isdigit(trim[i]) && trim[i] != '\'' && trim[i] != '"')
		{
			printf("exit: %s: numeric argument required\n", trim);
			break ;
		}
	}
	exit(EXIT_SUCCESS);
}

void	ft_env(t_env *env)
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

char *get_home(t_env *env)
{
	while (env)
	{
		if (!ft_strcmp(env->name, "HOME"))
			return (env->value);
		env = env->next;
	}
	return (NULL);
}

char *add_home(char *str, char *home)
{
	char *dir;
	int i;
	int j;

	i = 0;
	j = 1;
	while (str[i])
		i++;
	dir = malloc(sizeof(char) * (ft_strlen(home) + i));
	if (!dir)
		return (perror("ERROR"), exit (EXIT_FAILURE), NULL);
	if (home)
		ft_strlcpy(dir, home, ft_strlen(home) + 1);
	i = 0;
	while (dir[i])
		i++;
	while (str[j])
	{
		dir[i] = str[j];
		i++;
		j++;
	}
	return (dir);
}

int change_dir(t_env *env, char *name, char *value, int len)
{
	t_env *var;

	while (env && env->next)
	{
		if (!ft_strcmp(env->name, name)
		 	&& ft_strlcpy(env->value, value, len + 1))
			break;
		env = env->next;
	}
	if (env && !ft_strcmp(env->name, name))
		return (ft_strlcpy(env->value, value, len + 1), 0);
	if (!env || !env->next)
	{
		var = (t_env *)malloc(sizeof(t_env));
		if (!var)
			return (perror("Error"), exit(EXIT_FAILURE), 1);
		var->name = ft_strdup(name);
		var->value = ft_strdup(value);
		var->next = NULL;
		if (env)
			env->next = var;
	}
	return (0);	
}

int ft_cd2(char **str, int i, t_env *env)
{
	char *home;
	char *dir;
	char *trim;

	home = get_home(env); // path home
	trim = ft_strtrim(str[1], "\'\""); // trim beginning and end of string with the specified characters.
	if (trim && trim[0] == '~')
	{
		dir = add_home(trim, home); // trim + home
		i = chdir(dir); // commande used to change of the calling process to the directory specified in path
		free (dir);
	}
	else if (trim && trim[0] != '~')
		i = chdir(trim);
	else if (!trim)
	{
		if (home)
			i = chdir(home);
		else 
		{
			printf("minishell: cd: HOME not set\n");
			g_data.exit_code = 1;
		}
	}
	return (free(trim), i);
}

void ft_cd(char **str, t_env *env)
{
	int i;
	char old[1024];
	char new[1024];

	i = 0;
	getcwd(old, 1024);
	i = ft_cd2(str, i, env);
	if (i == -1)
	{
		printf("cd: no such file or directory: %s\n", str[1]);
		g_data.exit_code = 1;
	}
	else
	{
		getcwd(new, 1024);
		change_dir(env, "PWD", new, ft_strlen(new));
		if (ft_strcmp(old, new))
			change_dir(env, "OLDPWD", old, ft_strlen(old));
		g_data.exit_code = 0;
	}
}

int	execute(t_nodes **nodes, char **envp, t_env *env)
{
	check_env_var((*nodes)->cmd, env);
	/*change name to value;*/
	if (!ft_strcmp((*nodes)->cmd[0], "cd")
		|| !ft_strcmp((*nodes)->cmd[0], "/usr/bin/cd"))
		ft_cd((*nodes)->cmd, env);
	else if (!ft_strcmp((*nodes)->cmd[0], "exit"))
		ft_exit((*nodes)->cmd, 0);
	else
	{
		if (execute_other(nodes, envp, env))
			return (1);
	}
	return (0);
}
