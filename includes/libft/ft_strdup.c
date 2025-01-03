/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfortuna <mfortuna@student.42.pt>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/17 13:09:01 by mfortuna          #+#    #+#             */
/*   Updated: 2024/09/03 11:29:04 by mfortuna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *str)
{
	char	*p2;

	p2 = malloc(ft_strlen(str) + 1);
	if (!p2)
		return (NULL);
	ft_strlcpy(p2, str, ft_strlen(str) + 1);
	return (p2);
}
