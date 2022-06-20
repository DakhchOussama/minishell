#include "minishell.h"

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
	temp_envp = malloc(sizeof(char *) * (len_env(env) + 1));
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
