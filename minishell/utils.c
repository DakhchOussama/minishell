/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbjaghou <mbjaghou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/25 15:54:45 by mbjaghou          #+#    #+#             */
/*   Updated: 2022/05/25 16:02:46 by mbjaghou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize)
{
	size_t	i;
	size_t	len;

	i = 0;
	len = ft_strlen(src);
	if (dstsize == 0)
		return (len);
	while (src[i] != '\0' && i < dstsize - 1)
	{
		dst[i] = src[i];
		i++;
	}
	dst[i] = '\0';
	return (len);
}

size_t	ft_strlen(const char *s)
{
	size_t	i;

	i = 0;
	while (s[i] != '\0')
	{
		i++;
	}
	return (i);
}

char	*ft_strdup(const char *s1)
{
	char	*cp;

	cp = (char *)malloc(sizeof(char) * ft_strlen (s1) + 1);
	if (cp == 0)
	{
		return (NULL);
	}
	else
	{
		ft_strlcpy(cp, s1, ft_strlen(s1) + 1);
	}
	return (cp);
}

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*test;
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	if (s == 0)
		return (0);
	while (s[start + i] && i < len)
		i++;
	test = (char *)malloc(sizeof(char) * (i + 1));
	if (test == 0)
		return (0);
	i = 0;
	while (s[i])
	{
		if (j < len && i >= start)
		{
			test[j] = s[i];
			j++;
		}
		i++;
	}
	test[j] = '\0';
	return (test);
}
