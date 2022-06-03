/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbjaghou <mbjaghou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/28 16:30:00 by mbjaghou          #+#    #+#             */
/*   Updated: 2022/05/28 16:30:02 by mbjaghou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int skip_quotes(char *str, int i)
{
    if (str[i] && str[i] == '\'')
    {
        i++;
        while (str[i] != '\'')
            i++;
    }
    if (str[i] && str[i] == '"')
    {
        i++;
        while (str[i] != '"')
            i++;
    }
    return (i);    
}

int count_word(char *str, char c)
{
    int i;
    int word;

    i = 0;
    word = 0;
    while (str[i])
    {
        if (str[i] != c)
        {
            if (str[i] == '\"' && i++)
            {
                while (str[i] != '\"')
                    i++;
            }
            if (str[i] == '\'' && i++)
            {
                while (str[i] != '\'')
                    i++;
            }
            if (str[i + 1] == c || str[i + 1] == '\0')
                word++;
        }
        i++;
    }
    return (word);
}

int len_word(char *str, char c)
{
    int i;

    i = 0;
    while(str[i])
    {
        if (str[i] == '\"')
        {
            i++;
            while (str[i] != '\"')
                i++;
        }
        if (str[i] == '\'')
        {
            i++;
            while (str[i] != '\'')
                i++;
        }
        if (str[i] == c)
            break ;
        i++;
    }
    return (i);
}

char **remplir(char *str, char c, int compteur, char **split)
{
    int i;
    int j;
    int len;

    i = 0;
    while (i < compteur)
    {
        while (*str == c)
            str++;
        len = len_word(str, c);
        split[i] = (char *)malloc(sizeof(char *) * (len + 1));
        if (!split[i])
            return (perror("Error"), exit (EXIT_FAILURE), NULL);
        j = 0;
        while (j < len)
        {
            split[i][j++] = *str++; 
        }
        split[i][j] = '\0';
        i++;
    }
    split[i] = NULL;
    return (split);
}

char **ft_split(char *str, char c)
{
    int compteur;
    char **split;

    if (str == NULL)
        return (NULL);
    compteur = count_word(str, c);
    split = (char **)malloc(sizeof(char *) * (compteur + 1));
    if (!split)
    {
        free_str(split);
        return (perror("Error"), exit (EXIT_FAILURE), NULL);
    }
    split = remplir(str, c, compteur, split);
    return (split);
}

t_nodes **parsing (void)
{
    t_nodes **nodes;
    char    **tab;

    add_history(g_data.line);
    nodes = malloc(sizeof(t_nodes *));
    if (!nodes)
		  return (perror("Error"), exit (EXIT_FAILURE), NULL);
    if (check_pipes() == 0 || check_quotes() == 0)
        return (NULL);
    if (!(check_redirection(g_data.line)))
        return (NULL);
    tab = ft_split(g_data.line, '|');
    return (nodes);
}