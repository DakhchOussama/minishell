/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbjaghou <mbjaghou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/11 14:32:47 by mbjaghou          #+#    #+#             */
/*   Updated: 2022/06/14 03:38:42 by mbjaghou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include<stdio.h>
# include<unistd.h>
# include<stdlib.h>
# include<readline/readline.h>
# include<readline/history.h>
# include"libft/libft.h"

struct s_data
{
	int		exp;
	char	*line;
	int		exit_code;
	int		forks;
	int		temp;
}		g_data;

typedef struct s_nodes
{
	char			**cmd;
	int				fi[2];
	struct s_nodes	*prev;
	struct s_nodes	*next;
}			t_nodes;

typedef struct s_env // env parsing
{
	char			*name;
	char			*value;
	struct s_env	*next;
}	t_env;

char		*ft_strdup(const char *s1);
t_env		*stock_env(char **envp);
int			add_var(t_env **env, char *line);
char		*get_name(char *line);
char		*get_value(char *line);
char		*ft_substr(char const *s, unsigned int start, size_t len);
size_t		ft_strlcpy(char *dst, const char *src, size_t dstsize);
size_t		ft_strlen(const char *s);
void		ft_signal(int signum);
// void 	ft_shell(char *envp[], t_env *env, int dup);
void	ft_shell(char *envp[], t_env *env, int dp, t_nodes *tmp);
char		*ft_strtrim(char const *s1, char const *set);
t_nodes		**parsing(void);
int			check_pipes(void);
t_nodes		**ft_parsing(t_nodes **nodes);
int			check_quotes(void);
void		ctrl_d(int num);
char		*ft_strchr(const char *s, int c);
int			check_pipes_two(char *str);
int			check_first_last(void);
int			print_error(void);

void		fill1(char **str, t_nodes **nodes);
t_nodes		*ft_nodenew(char *content);
void		new_node(t_nodes **nodes, t_nodes *new);
t_nodes		*ft_nodelast(t_nodes *lst);
// static int	count_word(const char *s, char c);
// static int	len_word(const char *s, char c);
// static char	**fill(const char *s, char c, int word, char **splitted);
char		**ft_split2(char const *s, char c);
char		**fill_str2(char **temp);
void		free_str(char **str);
int			check_redirect_pos(char **str);
int			ft_isalnum(int c);
char		*ft_strjoin(char const *s1, char const *s2);
void		*ft_memcpy(void *dst, const void *src, size_t n);
int			check_single(char *str);
int			ft_strcmp(char *s1, char *s2);
char		*ft_itoa(int n);
char		**ft_split(char const *s, char c);
char		*fill_name(char *table, int *j);
int			ft_isdigit(int c);

int			execute(t_nodes **nodes, char **envp, t_env *env, int dp);
char		*get_val(t_env *env, char *name);
char		*change_tab(char *table, char *str, char *value, char *tmp);
char		**fill_table(char *str, t_env *env, int x, int j);
char		*change_str(char *str, char *tab);
void		check_env_var(char **str, t_env *env);
void		ft_exit(char **str, int i);
void		ft_echo(char **str);
void		print_str(char *str);
int			check_n(char **str, int *j);
void		ft_pwd(void);
void		ft_env1(t_env *env);
void	ft_env(t_env *env);
void	execution(char **str, char *envp[], t_env *env);
int	execute_other(t_nodes **nodes, char **envp, t_env *env);

void	exect2(char **envp, char **str, t_env *env);
void	exec_it(char **str, char **envp, t_env *env);
void	ft_wait(void);
void	free_node(t_nodes **node);
char	*get_home(t_env *env);
char	*add_home(char *str, char *home);
int		change_dir(t_env *env, char *name, char *value, int len);
int		ft_cd2(char **str, int i, t_env *env);
void	ft_cd(char **str, t_env *env);
t_env	*ft_unset(t_env * env, char **cmd, char **envp);
int		check_valid(char *var);
t_env	*ft_unset2(t_env *env, t_env *tmp, char *cmd_tmp, char **envp);
t_env	*ft_pop(char *name, t_env *env, char **envp);
void	free_env(t_env *env);
void	pop_last_env(t_env *env, char *cmd_tmp);
void	update_envp(t_env *env, char **envp);
char	**new_envp(t_env *env);
int		len_env(t_env *env);
void	ft_export(t_env *env, char **str, char **envp);
char	**sort_tmp(t_env *env, int len);
char	**fill_tmp_str(t_env *env, int len);
char	**fill_tmp_str2(t_env *tmp, int x, char **temp_str);
int		ft_add(t_env *env, char *str, int i, int pos);
int		get_post(char *str);
void	allocate(char **name, char **value, char *str, int pos);
void	update_env(t_env *env, char *name, char *value);
int		check_and_change(char *str, t_env *env);
void	copy_to_envp(char **temp_envp, char **envp);
#endif