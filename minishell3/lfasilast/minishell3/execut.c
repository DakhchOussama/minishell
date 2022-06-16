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

int check_valid(char *var)
{
	int i;

	i = 0;
	while (var[i])
	{
		if (!ft_isalnum(var[i])  && var[i] != '_')
		{
			printf("unset: `%s': not a valid identifier\n", var);
			return (1);
		}
		i++;
	}
	return (0);
}

t_env *ft_pop(char *name, t_env *env, char **envp)
{
	t_env *tmp;

	tmp = env;
	if (!ft_strcmp(env->name, name))
	{
		free_env(env);
		tmp = stock_env(envp + 1);
		return (tmp);
	}
	while (ft_strcmp(env->next->name, name))
		env = env->next;
	free(env->next->name);
	free(env->next->value);
	free(env->next);
	env->next = env->next->next;
	return (tmp);
}

void pop_last_env(t_env *env, char *cmd_tmp)
{
	while (env)
	{
		if (env->next && !ft_strcmp(env->next->name, cmd_tmp))
		{
			free(env->next->name);
			free(env->next->value);
			free(env->next);
			env->next = NULL;
			break ;
		}
		if (env->next)
			env = env->next;
		else
			break;
	}
}

t_env *ft_unset2(t_env *env, t_env *tmp, char *cmd_tmp, char **envp)
{
	while (env->next)
	{
		if (!ft_strcmp(env->name, cmd_tmp))
		{
			tmp = ft_pop(env->name, tmp, envp);
			break ;
		}
		env = env->next;
	}
	if (!env->next)
	{
		env = tmp;
		pop_last_env(env, cmd_tmp);
	}
	return (tmp);
}

int len_env(t_env *env)
{
	int len;

	len = 0;
	while (env)
	{
		len++;
		env = env->next;
	}
	return (len);
}

char **new_envp(t_env *env)
{
	char **temp_envp;
	char *tmp_name;
	int i;

	i = 0;
	temp_envp = malloc(sizeof(char *) * len_env(env) + 1);
	if (!temp_envp)
		exit (EXIT_FAILURE);
	while (env)
	{
		tmp_name = ft_strjoin(env->name, "=");
		temp_envp[i] = ft_strjoin(tmp_name, env->value);
		free(tmp_name);
		if (env->next)
		{
			i++;
			env = env->next;
		}
		else
			break ;
	}
	temp_envp[i + 1] = NULL;
	return (temp_envp);
}

void update_envp(t_env *env, char **envp)
{
	char **temp_envp;
	int i;

	i = 0;
	temp_envp = new_envp(env);
	while (temp_envp[i])
	{
		ft_strlcpy(envp[i], temp_envp[i], ft_strlen(temp_envp[i] + 1));
		i++;
	}
	free_str(temp_envp);
	if (g_data.exp > 0)
	{
		free(envp[i]);
		g_data.exp--;
	}
	envp[i] = NULL;
}

t_env *ft_unset(t_env * env, char **cmd, char **envp)
{
	int		i;
	t_env	*tmp;
	char	*cmd_tmp;

	i = 0;
	tmp = env;
	while (cmd[i])
	{
		cmd_tmp = ft_strtrim(cmd[i], "\"\'");
		if (check_valid(cmd_tmp))
		{
			free(cmd_tmp);
			return (tmp);
		}
		tmp = ft_unset2(env, tmp, cmd_tmp, envp);
		free(cmd_tmp);
		env = tmp;
		i++;
	}
	env = tmp;
	update_envp(env, envp);
	g_data.exit_code = 0;
	return (tmp);
}

int	execute(t_nodes **nodes, char **envp, t_env *env)
{
	check_env_var((*nodes)->cmd, env);
	/*change name to value;*/
	if (!ft_strcmp((*nodes)->cmd[0], "cd")
		|| !ft_strcmp((*nodes)->cmd[0], "/usr/bin/cd"))
		ft_cd((*nodes)->cmd, env);
	else if (!ft_strcmp((*nodes)->cmd[0], "unset"))
		env = ft_unset(env, (*nodes)->cmd, envp);
	else if (!ft_strcmp((*nodes)->cmd[0], "exit"))
		ft_exit((*nodes)->cmd, 0);
	else
	{
		if (execute_other(nodes, envp, env))
			return (1);
	}
	return (0);
}
