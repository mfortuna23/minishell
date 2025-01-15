/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmds_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfortuna <mfortuna@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/15 00:37:31 by mfortuna          #+#    #+#             */
/*   Updated: 2025/01/15 00:43:13 by mfortuna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

//create and init iter struct
t_iter	*init_iter(void)
{
	t_iter	*iter;

	iter = malloc(1 * sizeof(t_iter));
	iter->c = 0;
	iter->i = 0;
	iter->j = 0;
	iter->x = 0;
	iter->y = 0;
	iter->exp = true;
	return (iter);
}

bool	true_false(bool exp)
{
	if (exp == false)
		return (true);
	return (false);
}

//if is valid return 0
int	valid_varchars(char c)
{
	if (ft_isalnum(c) == 1 || c == '_')
		return (0);
	return (1);
}

int	data_check(t_data *data, int check, int r_value)
{
	data->check = check;
	return (r_value);
}

int	check_chars(char c)
{
	if (c == '|' || c == '<' || c == '>' )
		return (1);
	if (c == '&' || c == ';' || c == '\\')
		return (2);
	return (0);
}
