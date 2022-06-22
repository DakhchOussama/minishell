/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_splite_and_check.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbjaghou <mbjaghou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/31 07:52:24 by mbjaghou          #+#    #+#             */
/*   Updated: 2022/05/31 07:52:46 by mbjaghou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	count_word(const char *s, char c)
{
	int	i;
	int	word;

	i = 0;
	word = 0;
	while (s[i])
	{
		if (s[i] != c)
		{
			if (s[i] == '\"' && i++)
			{
				while (s[i] != '\"')
					i++;
			}
			if (s[i] == '\'' && i++)
			{
				while (s[i] != '\'')
					i++;
			}
			if (s[i + 1] == c || s[i + 1] == '\0')
				word++;
		}	
		i++;
	}
	return (word);
}

static int	len_word(const char *s, char c)
{
	int	i;
	int	len;

	i = 0;
	len = 0;
	while (s[i])
	{
		if (s[i] == '\"')
		{
			i++;
			while (s[i] != '\"')
				i++;
		}
		if (s[i] == '\'')
		{
			i++;
			while (s[i] != '\'')
				i++;
		}
		if (s[i] == c)
			break ;
		i++;
	}
	len = i;
	return (len);
}

static char	**fill(const char *s, char c, int word, char **splitted)
{
	int	i;
	int	j;
	int	len;

	i = 0;
	while (i < word)
	{
		while (*s == c)
			s++;
		len = len_word(s, c);
		splitted[i] = (char *)malloc(sizeof(char) * (len + 1));
		if (!splitted[i])
			return (perror("Error"), exit (EXIT_FAILURE), NULL);
		j = 0;
		while (j < len)
		{
			splitted[i][j++] = *s++;
		}
		splitted[i][j] = '\0';
		i++;
	}
	splitted[i] = NULL;
	return (splitted);
}

char	**ft_split2(char const *s, char c)
{
	int		word;
	char	**splited;

	if (s == NULL)
		return (NULL);
	word = count_word(s, c);
	splited = (char **)malloc(sizeof(char *) * (word + 1));
	if (!splited)
	{
		free_str(splited);
		return (perror("Error"), exit (EXIT_FAILURE), NULL);
	}
	splited = fill(s, c, word, splited);
	return (splited);
}
