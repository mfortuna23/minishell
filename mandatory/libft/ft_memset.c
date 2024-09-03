/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfortuna <mfortuna@student.42.pt>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/09 16:08:52 by mfortuna          #+#    #+#             */
/*   Updated: 2024/09/03 11:29:29 by mfortuna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void *s, int c, size_t n)
{
	unsigned char	*p;

	p = (unsigned char *)s;
	while (n > 0)
	{
		*p = c;
		p++;
		n--;
	}
	return (s);
}
/*
#include <string.h>
#include <stdio.h>
int	main(void)
{
	char	str1[50] = "egjhbckwie8niuh euytb";
	char	str2[50] = "egjhbckwie8niuh euytb";
	
	ft_memset(str1, 'k', 9);
	memset(str2, 'k', 9);
	printf("%s \n", str1);
	printf("%s \n", str2);
}
*/
