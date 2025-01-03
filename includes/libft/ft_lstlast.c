/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstlast.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfortuna <mfortuna@student.42.pt>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/26 10:59:53 by mfortuna          #+#    #+#             */
/*   Updated: 2024/09/03 11:29:51 by mfortuna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstlast(t_list *lst)
{
	int		size;
	t_list	*last;

	if (!lst)
		return (0);
	size = ft_lstsize(lst) - 1;
	last = lst;
	while (size > 0)
	{
		last = last->next;
		size --;
	}
	return (last);
}
