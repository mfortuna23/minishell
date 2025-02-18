/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isalpha.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfortuna <mfortuna@student.42.pt>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/03 15:37:08 by mfortuna          #+#    #+#             */
/*   Updated: 2024/09/03 11:30:21 by mfortuna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_isalpha(int c)
{
	if ((c < 'A') || (c > 'Z' && c < 'a') || (c > 'z'))
		return (0);
	return (1);
}
/*
#include <stdio.h>
int	main(void)
{
	int	c;

	c = '7';
	
	ft_isalpha(c);
	if (ft_isalpha(c) == 1)
	{
		printf("CHAR is ALPHA");
	}
	else
	{
		printf("CHAR is NOT alpha");
	}	
}
*/
