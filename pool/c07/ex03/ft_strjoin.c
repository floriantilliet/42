/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ftilliet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/18 09:29:27 by ftilliet          #+#    #+#             */
/*   Updated: 2023/09/18 19:58:17 by ftilliet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

int	ft_strlen(char *str)
{
	int	len;

	len = 0;
	while (*str != '\0')
	{
		str++;
		len++;
	}
	return (len);
}

int	ft_getlen(int size, char **strs, char *sep)
{	
	int	i;
	int	c;

	i = 0;
	c = 0;
	while (i < size)
	{
		c += ft_strlen(strs[i]);
		if (i < size - 1)
			c += ft_strlen(sep);
		i++;
	}
	return (c);
}

char	*ft_strjoin(int size, char **strs, char *sep)
{
	char		*s;
	int			i;
	int			j;
	int			c;

	c = 0;
	i = 0;
	c = ft_getlen(size, strs, sep);
	s = malloc(sizeof(char) * (c + 1));
	if (s == NULL)
		return (NULL);
	i = 0;
	c = 0;
	while (i < size)
	{
		j = 0;
		while (strs[i][j] != '\0')
			s[c++] = strs[i][j++];
		j = 0;
		while (sep[j] != '\0' && i != size - 1)
			s[c++] = sep[j++];
		i++;
	}
	s[c] = '\0';
	return (s);
}
/*
#include <stdio.h>
int	main(void)
{
	char	*tab[4];
	tab[0] = "salut";
	tab[1] = "c";
	tab[2] = "florian";
	tab[3] = "!";
	printf("%s", ft_strjoin(4, tab, "+++++++++"));
	return (0);
}
*/