#include "minishell.h"

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