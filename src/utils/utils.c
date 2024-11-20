/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfortuna <mfortuna@student.42.pt>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/21 11:01:03 by mfortuna          #+#    #+#             */
/*   Updated: 2024/11/20 12:10:02 by mfortuna         ###   ########.fr       */
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

int	ft_atoi_base(const char *nptr)
{
	int		i;
	int		nbr;
	int		sign;

	i = 0;
	nbr = 0;
	sign = 1;
	if (nptr[i] == '-' || nptr[i] == '+')
	{
		if (nptr[i ++] == '-')
			sign = sign * -1;
	}
	while (nptr[i] != '\0')
	{
		while (nptr[i] == '0')
			i++;
		while (nptr[i] >= '0' && nptr[i] <= '9')
			nbr = nbr * 10 + nptr[i ++] - '0';
		if (nptr[i] < '0' || nptr[i] > '9')
			return (nbr * sign);
	}
	return (nbr = 0);
}
