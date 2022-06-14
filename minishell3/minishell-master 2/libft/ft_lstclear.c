/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylabtaim <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/11 20:19:54 by ylabtaim          #+#    #+#             */
/*   Updated: 2021/11/12 01:01:19 by ylabtaim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void *))
{
	t_list	*cur;

	if (lst)
	{
		while (*lst)
		{
			cur = (*lst)->next;
			ft_lstdelone(*lst, del);
			(*lst) = cur;
		}
	}
}
