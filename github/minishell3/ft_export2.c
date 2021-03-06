#include "minishell.h"

void	allocate(char **name, char **value, char *str, int pos)
{
	(*name) = malloc(sizeof(char) * pos + 1);
	if (!(*name))
		exit (EXIT_FAILURE);
	if (pos == (int)ft_strlen(str))
		(*value) = NULL;
	else
	{
		(*value) = malloc(sizeof(char) * ((ft_strlen(str) - pos) + 1));
		if (!(*value))
			exit (EXIT_FAILURE);
	}
}

int	check_identifier(char *str)
{
	int	i;

	if (ft_isdigit(str[0]))
	{
		printf("export: '%s': not a valid identifier\n", str);
		return (1);
	}
	i = 0;
	while (str[i])
	{
		if (!ft_isalnum(str[i]) && str[i] != '_')
		{
			printf("export: '%s': not a valid identifer\n", str);
			return (1);
		}
		i++;
	}
	return (0);
}

void	new_env_var(char *name, char *value, t_env *env)
{
	t_env	*new;

	new = (t_env *)malloc(sizeof(t_env));
	if (!new)
		exit (EXIT_FAILURE);
	new->name = ft_strdup(name);
	if (value)
		new->value = ft_strdup(value);
	else
		new->value = NULL;
	new->next = NULL;
	env->next = new;
}

void	update_env(t_env *env, char *name, char *value)
{
	while (env)
	{
		if (!ft_strcmp(name, env->name))
		{
			if (!value && ((env->value && env->value[0] == '\0') \
			|| !env->value))
				return ;
			else if (value)
			{
				if (env->value)
					free(env->value);
				env->value = ft_strdup(value);
				return ;
			}
		}
		if (env->next)
			env = env->next;
		else
			break ;
	}
	if (env && !env->next)
		new_env_var(name, value, env);
}

int	ft_add(t_env *env, char *str, int i, int pos)
{
	char	*name;
	char	*name_trim;
	char	*value;

	pos = get_post(str);
	allocate(&name, &value, str, pos);
	i = -1;
	while (++i < pos)
		name[i] = str[i];
	name[i] = '\0';
	name_trim = ft_strtrim(name, "\"\'");
	free(name);
	if (check_identifier(name_trim))
		return (free(name_trim), free(value), 0);
	i = 0;
	while (value && str[++pos])
		value[i++] = str[pos];
	if (i != 0)
		value[i] = '\0';
	update_env(env, name_trim, value);
	free(name_trim);
	if (value)
		free(value);
	return (0);
}
