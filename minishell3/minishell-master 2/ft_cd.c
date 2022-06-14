/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yachehbo <yachehbo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/02 16:46:41 by yachehbo          #+#    #+#             */
/*   Updated: 2022/04/14 14:10:57 by yachehbo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"minishell.h"

char	*get_home(t_env *env)
{
	while (env)
	{
		if (!ft_strcmp(env->name, "HOME"))
			return (env->value);
		env = env->next;
	}
	return (NULL);
}

char	*add_home(char *str, char *home)
{
	char	*dir;
	int		i;
	int		j;

	i = 0;
	j = 1;
	while (str[i])
		i++;
	dir = malloc(sizeof(char) * (ft_strlen(home) + i));
	if (!dir)
		return (perror("Error"), exit (EXIT_FAILURE), NULL);
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

int	change_dir(t_env *env, char *name, char *value, int len)
{
	t_env	*var;

	while (env && env->next)
	{
		if (!ft_strcmp(env->name, name)
			&& ft_strlcpy(env->value, value, len + 1))
			break ;
		env = env->next;
	}
	if (env && !ft_strcmp(env->name, name))
		return (ft_strlcpy(env->value, value, len + 1), 0);
	if (!env || !env->next)
	{
		var = (t_env *)malloc(sizeof(t_env));
		if (!var)
			return (perror("Error"), exit (EXIT_FAILURE), 1);
		var->name = ft_strdup(name);
		var->value = ft_strdup(value);
		var->next = NULL;
		if (env)
			env->next = var;
	}
	return (0);
}

int	ft_cd2(char **str, int i, t_env *env)
{
	char	*home;
	char	*dir;
	char	*trim;

	home = get_home(env);
	trim = ft_strtrim(str[1], "\'\"");
	if (trim && trim[0] == '~')
	{
		dir = add_home(trim, home);
		i = chdir(dir);
		free(dir);
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

void	ft_cd(char **str, t_env *env)
{
	int		i;
	char	old_dir[1024];
	char	new_dir[1024];

	i = 0;
	getcwd(old_dir, 1024);
	i = ft_cd2(str, i, env);
	if (i == -1)
	{
		printf("cd: no such file or directory: %s\n", str[1]);
		g_data.exit_code = 1;
	}
	else
	{
		getcwd(new_dir, 1024);
		change_dir(env, "PWD", new_dir, ft_strlen(new_dir));
		if (ft_strcmp(old_dir, new_dir))
			change_dir(env, "OLDPWD", old_dir, ft_strlen(old_dir));
		g_data.exit_code = 0;
	}
}
