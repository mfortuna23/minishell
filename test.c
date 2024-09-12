#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "mandatory/minishell.h"

int	word_count(char *s, int i, int j)
{
	int	words;

	words = 0;
	while (s[i])
	{
		while ((s[i] <= ' ') && s[i])
			i++;
		if (s[i] > ' ')
		{
			words ++;
			if (s[i] == 34 || s[i] == 39)
			{
				j = i;
				i++;
				while ((s[i] != s[j]) && s[i])
					i++;
			}
			while ((s[i] > ' ') && s[i])
				i++;
		}
	}
	return (words);
}
char	*get_word(char *s, int i)
{
	int		j;

	j = 0;
	while (s[i] <= ' ' && s[i])
		i++;
	if (s[i] > ' ' && s[i])
	{
		if (s[i] == 34 || s[i] == 39)
		{
			j = i;
			i++;
			while ((s[i] != s[j]) && s[i])
				i++;
			return (ft_substr(s, j, (i - j) + 1));
		}
		j = i;
		while (s[i] > ' ')
		{
			i++;
			if (s[i] <= ' ' || s[i] == 0)
				return (ft_substr(s, j, i - j));
		}
	}
	return (NULL);
}

char	**split_cmd(char *s)
{
	int		i;
	int		x;
	int		words;
	char	**arr;

	words = word_count(s, 0, 0);
	arr = malloc((words + 1) * sizeof(char *));
	i = 0;
	arr[0] = get_word(s, 0);
	x = 1;
	while (x < words && s[i])
	{
		i += ft_strlen(arr[x - 1]);
		while(s[i] <= ' ')
		i++;
		arr[x] = get_word(s, i);
		x++;
	}
	return (arr);
}

int main (int argc, char **argv)
{
	char **arr;
	int x = 0;

	if (argc == 1)
		return(1);
	arr = split_cmd(argv[1]);
	while (arr[x])
	{
		printf("%s\n", arr[x]);
		x++;
	}
	printf("it has %i many words \n", word_count(argv[1], 0, 0));
	return (0);
}