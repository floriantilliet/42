/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ftilliet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/19 16:05:55 by ftilliet          #+#    #+#             */
/*   Updated: 2023/09/20 12:03:46 by ftilliet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <stdio.h>

int	is_sep(char c, char *charset)
{
	int	j;

	j = 0;
	while (charset[j])
	{
		if (c == charset[j])
			return (1);
		j++;
	}
	if (c == '\0')
		return (1);
	return (0);
}

int	count_words(char *str, char *charset)
{
	int	i;
	int	c;

	i = 0;
	c = 0;
	while (str[i])
	{
		if (is_sep(str[i + 1], charset) == 1 && is_sep(str[i], charset) == 0)
			c++;
		i++;
	}
	return (c);
}

void	write_word(char *dest, char *from, char *charset)
{
	int	i;

	i = 0;
	while (is_sep(from[i], charset) == 0)
	{
		dest[i] = from[i];
		i++;
	}
	dest[i] = '\0';
}

void	write_split(char **tab, char *str, char *charset)
{
	int		i;
	int		j;
	int		word;

	word = 0;
	i = 0;
	while (str[i] != '\0')
	{
		if (is_sep(str[i], charset) == 1)
			i++;
		else
		{
			j = 0;
			while (is_sep(str[i + j], charset) == 0)
				j++;
			tab[word] = malloc(sizeof(char) * (j + 1));
			write_word(tab[word], str + i, charset);
			i += j;
			word++;
		}
	}
}

char	**ft_split(char *str, char *charset)
{
	char	**res;
	int		words;

	words = count_words(str, charset);
	res = malloc(sizeof(char *) * (words + 1));
	res[words] = 0;
	write_split(res, str, charset);
	return (res);
}
/*
int	main(int argc, char **argv)
{
	char **tab;
	int i;

	i = 0;
	argc++;
	tab = ft_split(argv[1], argv[2]);
	while(tab[i])
	{
		printf("%s\n", tab[i]);
		i++;
	}
}
*/
