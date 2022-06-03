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

static size_t	s2_len(char const *s1, char const *set)
{
	size_t	i;
	size_t	len;

	i = -1;
	len = ft_strlen(s1);
	while (set[++i] && *s1)
	{
		if (*s1 == set[i])
		{
			len--;
			s1++;
			i = -1;
		}
	}
	i = -1;
	while (set[++i] && *s1)
	{
		if (s1[len - 1] == set[i])
		{
			len--;
			i = -1;
		}
	}
	return (len);
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

char	*ft_strtrim(char const *s1, char const *set)
{
	size_t	len;
	size_t	i;
	char	*s2;

	if (!s1)
		return (0);
	len = s2_len(s1, set);
	i = 0;
	while (set[i] && *s1)
	{
		if (*s1 == set[i])
		{
			s1++;
			i = -1;
		}
		i++;
	}
	s2 = (char *)malloc(sizeof(char) * (len + 1));
	if (!s2)
		return (0);
	ft_strlcpy(s2, (char *)s1, len + 1);
	return (s2);
}

char	*ft_strchr(const char *s, int c)
{
	unsigned char	*t;

	t = (unsigned char *)s;
	while (*t != (unsigned char)c && *t)
		t++;
	if (*t == (unsigned char)c)
		return ((char *)t);
	else
		return (0);
}

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t			i;
	unsigned char	*s11;
	unsigned char	*s22;

	s11 = (unsigned char *)s1;
	s22 = (unsigned char *)s2;
	if (n == 0)
		return (0);
	i = 0;
	while (s11[i] && s22[i] && s11[i] == s22[i] && i < n - 1)
		i++;
	return (s11[i] - s22[i]);
}

