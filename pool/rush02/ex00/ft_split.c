/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rdupeux <rdupeux@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/19 16:05:55 by ftilliet          #+#    #+#             */
/*   Updated: 2023/09/24 23:22:52 by rdupeux          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

<<<<<<< HEAD
#include <stdio.h>
=======
>>>>>>> c7873c1dbf191dc12b2aa6f2ed63e4a51c8515b6
#include <stdlib.h>

void	write_dic_split(char **tab, char *str)
{
	int	i;
	int	j;
	int	word;

	word = 0;
	i = 0;
	while (str[i])
	{
		if (str[i] == '\n')
			i++;
		else
		{
			j = 0;
			while (str[i + j] != ' ')
				j++;
			tab[word] = malloc(sizeof(char) * (j + 1));
			i += write_dic_word(tab[word++], str + i, " :");
			i += skip_spaces(str + i);
			j = 0;
			while (str[i + j] != '\n' && str[i + j])
				j++;
			tab[word] = malloc(sizeof(char) * (j + 1));
			i += write_dic_word(tab[word++], str + i, "\n");
		}
	}
}

int	count_dic_words(char *str)
{
	int	i;
	int	word_count;

	word_count = 0;
	i = 0;
	while (str[i] != '\0')
	{
		if (str[i] == '\n')
			i++;
		else
		{
			while (str[i] != ':' && str[i])
				i++;
			word_count++;
			while (str[i] == ' ')
				i++;
			while (str[i] != '\n' && str[i])
				i++;
			word_count++;
		}
	}
	return (word_count);
}

char	**ft_dic_split(char *str)
{
	char **res;
	int words;

	words = count_dic_words(str);
	res = malloc(sizeof(char *) * (words + 1));
	res[words] = 0;
	write_dic_split(res, str);
	return (res);
}