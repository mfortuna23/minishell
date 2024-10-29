/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfortuna <mfortuna@student.42.pt>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/21 11:01:03 by mfortuna          #+#    #+#             */
/*   Updated: 2024/10/28 12:05:14 by mfortuna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*str_join(char *s1, char *s2)
{
	size_t	size;
	char	*p;

	size = ft_strlen(s1) + ft_strlen(s2) + 1;
	p = (char *)ft_calloc(sizeof(char), size);
	if (!p)
		return (0);
	ft_memcpy(p, s1, ft_strlen(s1));
	ft_strlcat(p, s2, size);
	free(s1);
	free(s2);
	return (p);
}

void	ms_bomb(t_data *data)
{
	free(data->prompt);
	free(data->path);
	if (data->input)
		free(data->input);
	while (data->var)
		del_lastenv(data);
}