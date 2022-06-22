#include "minishell.h"

int	check_and_change(char *str, t_env *env)
{
	if (str[0] == '=' || !ft_strcmp(str, "\"\"")
		|| !ft_strcmp(str, "\'\'"))
	{
		if (!ft_strcmp(str, "\"\"") || !ft_strcmp(str, "\'\'"))
			str = ft_strdup("");
		printf("export: '%s': not a valid identifier\n", str);
		g_data.exit_code = 1;
		return (1);
	}
	else
		ft_add(env, str, 0, 0);
	return (0);
}

char	**fill_temp_envp(t_env *env)
{
	char	*tmp_name;
	char	**temp_envp;
	int		i;

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

void	copy_to_envp(char **temp_envp, char **envp)
{
	int	i;

	i = 0;
	while (temp_envp[i])
	{
		if (!envp[i])
		{
			envp[i] = ft_strdup(temp_envp[i]);
			g_data.exp++;
		}
		else
			ft_strlcpy(envp[i], temp_envp[i], ft_strlen(temp_envp[i]) + 1);
		i++;
	}
	envp[i] = NULL;
	free_str(temp_envp);
}

void	ft_export(t_env *env, char **str, char **envp)
{
	int		i;
	char	**temp_envp;

	if (!str[1])
		sort_and_print(env);
	else
	{
		i = 0;
		while (str[++i])
		{
			if (check_and_change(str[i], env))
				return ;
		}
		temp_envp = fill_temp_envp(env);
		copy_to_envp(temp_envp, envp);
	}
	g_data.exit_code = 0;
}
