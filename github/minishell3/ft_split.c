/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbjaghou <mbjaghou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/08 21:05:58 by mbjaghou          #+#    #+#             */
/*   Updated: 2022/06/20 20:26:17 by mbjaghou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	word_count(char const *s, char c)
{
	unsigned int	i;
	int				n;

	i = 0;
	n = 0;
	while (s[i])
	{
		while (s[i] == c)
			i++;
		if (s[i])
			n++;
		while (s[i] && s[i] != c)
			i++;
	}
	return (n);
}

static char	*ft_allocate(char **strs, const char *s, size_t n)
{
	char	*copy;

	copy = (char *)malloc(sizeof(char) * (n + 1));
	if (!copy)
	{
		while ((*strs)--)
			free(*strs);
		free(strs);
		return (0);
	}
	ft_strlcpy(copy, s, (n + 1));
	return (copy);
}

char	**ft_split(char const *s, char c)
{
	char	**splited_strs;
	int		i;
	int		j;
	int		k;

	if (!s)
		return (0);
	splited_strs = (char **)malloc(sizeof(char *) * (word_count(s, c) + 1));
	if (!splited_strs)
		return (0);
	i = 0;
	k = 0;
	while (s[i])
	{
		while (s[i] == c)
			i++;
		j = i;
		while (s[i] && s[i] != c)
			i++;
		if (i > j)
			splited_strs[k++] = ft_allocate(splited_strs, s + j, i - j);
	}
	splited_strs[k] = 0;
	return (splited_strs);
}
