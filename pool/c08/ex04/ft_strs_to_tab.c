/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strs_to_tab.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ftilliet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/21 17:48:08 by ftilliet          #+#    #+#             */
/*   Updated: 2023/09/24 09:59:01 by ftilliet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_stock_str.h"
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

char	*ft_strcpy(char *dest, char *src)
{
	int	i;

	i = 0;
	while (src[i] != '\0')
	{
		dest[i] = src [i];
		i++;
	}
	dest[i] = '\0';
	return (dest);
}

struct s_stock_str	*ft_strs_to_tab(int ac, char **av)
{
	t_stock_str	*tab;
	int			i;
	int			len;

	i = 0;
	tab = malloc(sizeof(t_stock_str) * (ac + 1));
	while (i < ac)
	{
		len = ft_strlen(av[i]);
		tab[i].size = len;
		tab[i].str = malloc(sizeof(char) * (len + 1));
		tab[i].copy = malloc(sizeof(char) * (len + 1));
		ft_strcpy(tab[i].str, av[i]);
		ft_strcpy(tab[i].copy, tab[i].str);
		i++;
	}
	tab[i].size = 0;
	tab[i].str = 0;
	tab[i].copy = 0;
	return (tab);
}

/*
#include <stdio.h>
int main(int argc, char **argv)
{
    t_stock_str *tab;
    int i = 0;
    tab = ft_strs_to_tab(argc - 1, &argv[1]);
    
    while(i < 3)
    {
        printf("%d, %s, %s\n", tab[i].size, tab[i].str, tab[i].copy);
        i++;
    }
}
*/