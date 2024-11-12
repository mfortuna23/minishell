/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isprint.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfortuna <mfortuna@student.42.pt>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/04 14:32:24 by mfortuna          #+#    #+#             */
/*   Updated: 2024/09/03 11:30:14 by mfortuna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_isprint(int c)
{
	if ((c > 31) && (c < 127))
		return (1);
	else
		return (0);
}
/*
#include <stdio.h>
int	main(void)
{
	int	c;
	
	c = 30;
	ft_isprint(c);
	if (ft_isprint(c) == 1)
		printf("CHAR is PRINTABLE");
	else
		printf("CHAR is NOT printable");
}
*/
