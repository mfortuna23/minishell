/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfortuna <mfortuna@student.42.pt>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/29 13:03:24 by mfortuna          #+#    #+#             */
/*   Updated: 2024/09/03 11:28:29 by mfortuna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	*ft_rest(char *rest)
{
	char	*line;
	int		i;
	int		j;

	i = check_char(rest, '\n');
	if (i < 0)
	{
		free(rest);
		return (0);
	}
	if (!rest[0])
	{
		free(rest);
		return (0);
	}
	line = malloc(len_str(rest) - i);
	i++;
	j = -1;
	while (rest[i + (++j)] != 0)
		line[j] = rest[i + j];
	line[j] = 0;
	free(rest);
	rest = 0;
	return (line);
}

static char	*join_str(char *rest, char *line)
{
	char	*tmp;
	int		i;
	int		j;

	tmp = malloc(len_str(rest) + len_str(line) + 1);
	if (!tmp || !(rest) || !line)
		return (0);
	i = 0;
	j = 0;
	while ((rest)[i] != 0)
	{
		tmp[i] = (rest)[i];
		i++;
	}
	while (line[j] != 0)
	{
		tmp[i + j] = line[j];
		j++;
	}
	tmp[i + j] = 0;
	free(rest);
	rest = 0;
	return (tmp);
}

static char	*cut(char *rest)
{
	char	*line;
	int		i;
	int		j;

	j = 0;
	if (!rest[0])
		return (0);
	i = check_char(rest, '\n');
	if (i == -1)
		i = len_str(rest);
	line = malloc(i + 2);
	if (!line)
		return (0);
	while (i >= j)
	{
		line[j] = rest[j];
		j ++;
	}
	line[j] = 0;
	return (line);
}

static char	*read_file(int fd, char *rest)
{
	char	*line;
	int		size;

	if (!rest)
	{
		rest = malloc(1);
		rest[0] = 0;
	}
	size = 1;
	line = NULL;
	while (check_char(rest, '\n') < 0 && size > 0)
	{
		line = malloc(BUFFER_SIZE + 1);
		size = read(fd, line, BUFFER_SIZE);
		if (size <= 0)
			return (ft_erro(rest, line, size));
		line[size] = 0;
		rest = join_str(rest, line);
		free(line);
		line = 0;
	}
	return (rest);
}

char	*get_next_line(int fd)
{
	static char	*rest[FOPEN_MAX];
	char		*line;

	if (fd < 0 || BUFFER_SIZE <= 0 || fd > FOPEN_MAX)
		return (0);
	rest[fd] = read_file(fd, rest[fd]);
	if (!rest[fd])
		return (0);
	line = cut(rest[fd]);
	rest[fd] = ft_rest(rest[fd]);
	return (line);
}
/*
#include <stdio.h>
int	main (void)
{
	int fd = open("./read_error.txt", O_RDONLY);
	char 	*str;

	str = get_next_line(fd);
	while (str != NULL)
	{
		printf("%s", str);
		free(str);
		str = get_next_line(fd);
	}
	printf("%s", str);
	str = get_next_line(fd);
	printf("%s", str);
	close(fd);
	str = get_next_line(fd);
	printf("%s", str);
	fd = open("./read_error.txt", O_RDONLY);
	str = get_next_line(fd);
	printf("%s..", str);
	str = get_next_line(fd);
	printf("%s..", str);
	close(fd);
	return(0);
}
*/
