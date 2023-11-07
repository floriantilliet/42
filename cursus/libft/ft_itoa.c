/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ftilliet <ftilliet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/07 09:28:53 by ftilliet          #+#    #+#             */
/*   Updated: 2023/11/07 15:33:17 by ftilliet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	get_malloc(int nbr)
{
	int	i;

	i = 1;
	if (nbr < 0)
	{
		nbr = -nbr;
		i++;
	}
	if (nbr == 0)
		return (0);
	while (nbr > 10)
	{
		nbr /= 10;
		i++;
	}
	return (i);
}

void	getnbr(int nbr, char *nb, int *i)
{
	int					len_base;
	int					s;

	s = 1;
	if (nbr < 0)
	{
		s = -1;
		nb[*i] = '-';
		*i = *i + 1;
		nbr = -nbr;
	}
	if (nbr >= 10)
		getnbr(nbr / 10, nb, &(*i));
	nb[*i] = "0123456789"[(nbr % 10)];
	*i = *i + 1;
}

char	*ft_itoa(int nbr)
{
	char	*nb;
	int		i;

	i = 0;

	nb = malloc(sizeof(char) * (get_malloc(nbr) + 1));
	getnbr(nbr, nb, &i);
	nb[i + 1] = '\0';
	return (nb);
}