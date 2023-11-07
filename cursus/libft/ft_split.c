/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ftilliet <ftilliet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/07 09:28:37 by ftilliet          #+#    #+#             */
/*   Updated: 2023/11/07 15:32:39 by ftilliet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	count_words(char *str, char c)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (str[i])
	{
		if (str[i + 1] == c && str[i] != c)
			count++;
		i++;
	}
	return (count);
}

void	write_word(char *dest, char *from, char c)
{
	int	i;

	i = 0;
	while (from[i] != c)
	{
		dest[i] = from[i];
		i++;
	}
	dest[i] = '\0';
}

void	write_split(char **tab, char *str, char c)
{
	int		i;
	int		j;
	int		word;

	word = 0;
	i = 0;
	while (str[i] != '\0')
	{
		if (str[i] == c)
			i++;
		else
		{
			j = 0;
			while (str[i + j] != c)
				j++;
			tab[word] = malloc(sizeof(char) * (j + 1));
			write_word(tab[word], str + i, c);
			i += j;
			word++;
		}
	}
}

char	**ft_split(char *str, char c)
{
	char	**res;
	int		words;

	words = count_words(str, c);
	res = malloc(sizeof(char *) * (words + 1));
	res[words] = 0;
	write_split(res, str, c);
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
