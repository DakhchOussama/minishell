/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylabtaim <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/08 17:12:17 by ylabtaim          #+#    #+#             */
/*   Updated: 2021/11/08 20:19:17 by ylabtaim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static	char	*ft_allocate(char *string, long *n1, int *i)
{
	if ((*n1) <= 0)
	{
		string = (char *)malloc(sizeof(char) * (*i));
		if (!string)
			return ("allocation failed");
		if (!(*n1))
		{
			string[0] = '0';
			string[1] = '\0';
			return (string);
		}
		(*n1) = -(*n1);
		string[0] = '-';
		(*i)--;
	}
	else
	{
		string = (char *)malloc(sizeof(char) * ((*i) - 1));
		if (!string)
			return ("allocation failed");
		(*i) -= 2;
		ft_bzero(string, (*i));
	}
	return (string);
}

static	int	ft_numlen(int n1, int i)
{
	while (n1)
	{
		n1 /= 10;
		i++;
	}
	i++;
	return (i);
}

char	*ft_itoa(int n)
{
	int		res;
	long	n1;
	int		i;
	char	*string;

	string = 0;
	n1 = n;
	i = 1;
	i = ft_numlen(n1, i);
	string = ft_allocate(string, &n1, &i);
	if (!ft_strncmp(string, "allocation failed", 17))
		return (0);
	res = 0;
	if (ft_strncmp(string, "0", 1))
		string[i] = '\0';
	while (n1)
	{
		res = n1 % 10;
		n1 /= 10;
		i--;
		string[i] = res + '0';
	}
	return (string);
}
