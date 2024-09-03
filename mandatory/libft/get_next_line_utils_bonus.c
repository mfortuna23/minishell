/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils_bonus.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfortuna <mfortuna@student.42.pt>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/29 13:04:56 by mfortuna          #+#    #+#             */
/*   Updated: 2024/09/03 11:28:27 by mfortuna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_erro(char *rest, char *line, int size)
{
	free(line);
	line = 0;
	if (size == -1)
	{
		free(rest);
		rest = 0;
		return (0);
	}
	return (rest);
}

int	len_str(char *str)
{
	int	i;

	i = 0;
	while (*str != 0)
	{
		str ++;
		i++;
	}
	return (i);
}

int	check_char(char *s, int c)
{
	int	i;

	i = 0;
	while (s[i] != 0)
	{
		if (s[i] == c)
			return (i);
		i++;
	}
	return (-1);
}
