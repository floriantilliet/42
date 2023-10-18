/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_convert_base2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ftilliet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/18 09:46:42 by ftilliet          #+#    #+#             */
/*   Updated: 2023/09/19 15:50:02 by ftilliet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <stdio.h>
#include <malloc.h>

int	ft_atoi_base_error(char *base);
int	ft_atoi_base_test(char str, char *base);
int	ft_atoi_base_search(char *str, int *i);
int	ft_atoi_base(char *str, char *base);

int	get_malloc(int nbr, int len_base)
{
	int	i;

	i = 0;
	if (nbr < 0)
	{
		nbr = -nbr;
		i++;
	}
	if (nbr == 0)
		return (0);
	while (nbr < len_base)
	{
		nbr /= len_base;
		i++;
	}
	return (i);
}

void	ft_getnbr_base(int nbr, char *base, char *nb, int *i)
{
	int					len_base;
	int					s;

	s = 1;
	len_base = ft_atoi_base_error(base);
	if (nbr < 0)
	{
		s = -1;
		nb[*i] = '-';
		*i = *i + 1;
		nbr = -nbr;
	}
	if (nbr >= len_base)
		ft_getnbr_base(nbr / len_base, base, nb, &(*i));
	nb[*i] = base[(nbr % len_base)];
	*i = *i + 1;
}

char	*ft_convert_base(char *nbr, char *base_from, char *base_to)
{
	char	*nb;
	int		temp;
	int		i;
	int		len_from;
	int		len_to;

	len_from = ft_atoi_base_error(base_from);
	len_to = ft_atoi_base_error(base_to);
	i = 0;
	if (len_from == 0 || len_to == 0)
	{
		return (0);
	}
	temp = ft_atoi_base(nbr, base_from);
	nb = malloc(sizeof(char) * (get_malloc(temp, len_to) + 1));
	ft_getnbr_base(temp, base_to, nb, &i);
	nb[i + 1] = '\0';
	return (nb);
}
/* int	main(void)
{
	printf("42: %s\n", ft_convert_base("--2a", "0123456789abcdef", "0123456789"));
	printf("-2a: %s\n", ft_convert_base("-42", "0123456789", "0123456789abcdef"));
	printf("-10000000: %s\n", ft_convert_base("-128", "0123456789", "01"));
	printf("-1e: %s\n", ft_convert_base(" -+--0030", "0123456789"
									, "0123456789abcdef"));
	printf("0: %s\n", ft_convert_base("-0", "0123456789", "01"));
} */