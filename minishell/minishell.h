/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbjaghou <mbjaghou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/11 14:32:47 by mbjaghou          #+#    #+#             */
/*   Updated: 2022/05/25 16:10:03 by mbjaghou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include<stdio.h>
# include<unistd.h>
# include<stdlib.h>
# include<readline/readline.h>
# include<readline/history.h>

struct s_data
{
	char	*line;
	int		exit_code;
}		g_data;

typedef struct s_env // env parsing
{
	char			*name;
	char			*value;
	struct s_env	*next;
}	t_env;

char	*ft_strdup(const char *s1);
t_env	*stock_env(char **envp);
int		add_var(t_env **env, char *line);
char	*get_name(char *line);
char	*get_value(char *line);
char	*ft_substr(char const *s, unsigned int start, size_t len);
size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize);
size_t	ft_strlen(const char *s);
#endif