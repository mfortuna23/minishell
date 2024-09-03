/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bzero.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfortuna <mfortuna@student.42.pt>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/09 16:07:50 by mfortuna          #+#    #+#             */
/*   Updated: 2024/09/03 11:30:28 by mfortuna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_bzero(void *s, size_t n)
{
	int	c;

	c = '\0';
	ft_memset(s, c, n);
}
/*
#include <strings.h>
#include <stdio.h>
int	main(void)
{
	char	str1[50] = "egjhbckwie8niuh euytb";
	char	str2[50] = "egjhbckwie8niuh euytb";
	
	ft_bzero(str1, 9);
	bzero(str2, 9);
	printf("%s \n", str1);
	printf("%s \n", str2);
}
*/
