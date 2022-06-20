#include "minishell.h"

char **fill_tmp_str2(t_env *tmp, int x, char **temp_str)
{
	char *tmp_name;
	char *tmp_value;
	char *value;
	char *str;

	if (tmp->value)
	{
		tmp_name = ft_strjoin(tmp->name, "=");
		value = ft_strjoin("\"", tmp->value);
		tmp_value = ft_strjoin(value, "\"");
		free(value);
		str = ft_strjoin(tmp_name, tmp_value);
		free(tmp_name);
		free(tmp_value);
	}
	else 
	{
		tmp_name = ft_strdup(tmp->name);
		str = ft_strdup(tmp_name);
		free(tmp_name);
	}
	temp_str[x] = ft_strjoin("declare -x ", str);
	free(str);
	return(temp_str);
}

char **fill_tmp_str(t_env *env, int len)
{

	char **tmp_str;
	int  i;

	tmp_str = malloc(sizeof(char *) * (len + 1));
	if (!tmp_str)
		return (perror("ERROR"), exit(EXIT_FAILURE), NULL);
	i = 0;
	while (env)
	{
		tmp_str = fill_tmp_str2(env, i, tmp_str);
		i++;
		if (env->next)
			env = env->next;
		else
			break;
	}
	tmp_str[i + 1] = NULL;
	return (tmp_str);
}

char **sort_tmp(t_env *env, int len)
{
	int y;
	int i;
	char *tmp;
	char **tmp_str;

	tmp_str = fill_tmp_str(env, len);
	i = -1;
	y = 0;
	while (++i < len)
	{
		y = i;
		while (++y < len)
		{
			if (tmp_str[y] && ft_strcmp(tmp_str[i], tmp_str[y]) > 0)
			{
				tmp = ft_strdup(tmp_str[i]);
				free(tmp_str[i]);
				tmp_str[i] = ft_strdup(tmp_str[y]);
				free(tmp_str[y]);
				tmp_str[y] = ft_strdup(tmp);
				free(tmp);
			}
		}
	}
	return (tmp_str[i] = NULL, tmp_str);
}

void sort_and_print(t_env *env)
{
	char **temp;
	int i;
	int len;

	len = len_env(env);
	temp = sort_tmp(env, len);
	i = 0;
	while (i < len)
	{
		if (temp[i][0])
			printf("%s\n",temp[i]);
		i++;
	}
	if (temp)
		free_str(temp);
}

int get_post(char *str)
{
	int cmd;
	int i;

	cmd = 0;
	i = 0;
	while(str[i])
	{
		if (str[i] == '=')
			break;
		i++;
		cmd++;
	}
	return (cmd);
}

void allocate(char **name, char **value, char *str, int pos)
{
	(*name) = malloc(sizeof(char) * pos + 1); // ....=
	if (!(*name))
		exit (EXIT_FAILURE);
	if (pos == (int)ft_strlen(str))
		(*value) = NULL;
	else 
	{
		(*value) = malloc(sizeof(char) * ((ft_strlen(str) - pos) + 1)); // =......
		if (!(*value))
			exit (EXIT_FAILURE); 
	}
}

int check_identifier(char *str)
{
	int i;

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

void new_env_var(char *name, char *value, t_env *env)
{
	t_env *new;

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

void update_env(t_env *env, char *name, char *value)
{
	while (env)
	{
		if (!ft_strcmp(name, env->name))
		{
			if (!value && ((env->value && env->value[0] == '\0')
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
			break;
	}
	if (env && !env->next)
		new_env_var(name, value, env);
}

int ft_add(t_env *env, char *str, int i, int pos)
{
	char *name;
	char *name_trim;
	char *value;

	pos = get_post(str); // ....=
	allocate(&name, &value, str, pos);
	i = -1;
	while (++i < pos)
		name[i] = str[i];
	name[i] = '\0';
	name_trim = ft_strtrim(name, "\"\'");
	free(name);
	if (check_identifier(name_trim))
		return(free(name_trim), free(value), 0);
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

int check_and_change(char *str, t_env *env)
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

char **fill_temp_envp(t_env *env)
{
	char *tmp_name;
	char **temp_envp;
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
			break;
	}
	temp_envp[i + 1] = NULL;
	return (temp_envp);
}

void copy_to_envp(char **temp_envp, char **envp)
{
	int i;

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

void ft_export(t_env *env, char **str, char **envp)
{
	int i;
	char **temp_envp;

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