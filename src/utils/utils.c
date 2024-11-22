/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfortuna <mfortuna@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/21 11:01:03 by mfortuna          #+#    #+#             */
/*   Updated: 2024/11/22 10:55:39 by mfortuna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*str_join(char *s1, char *s2)
{
	size_t	size;
	char	*p;

	if (s1 == NULL)
		size = ft_strlen(s2) + 1;
	else
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

void	ms_bomb(t_data *data, int check)
{
	if (data->cmd)
		delete_cmds(data);
	free(data->prompt);
	free(data->path);
	if (check == 1)
	{
		if (data->input)
			free(data->input);
	}
	while (data->var)
		del_lastenv(data);
}

//if type == 0 returns last return value
int	r_value(int value, int type)
{
	static int	r_v;

	if (type == 0)
		return (r_v);
	r_v = value;
	return (r_v);
}
