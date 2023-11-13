/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printnbrs.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ftilliet <ftilliet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/13 15:22:06 by ftilliet          #+#    #+#             */
/*   Updated: 2023/11/13 18:45:25 by ftilliet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "printf.h"

int	ft_printnbr(int nb)
{
	long int		nbr;
	unsigned char	temp;
	int				count;

	count = 0;
	nbr = nb;
	if (nbr < 0)
	{
		nbr *= -1;
		write(1, "-", 1);
	}
	if (nbr > 9)
		count += ft_printnbr(nbr / 10);
	temp = '0' + (char)(nbr % 10);
	count += ft_printchar(temp);
	return (count);
}

int	ft_printunbr(unsigned int nb)
{
	unsigned long int	nbr;
	unsigned char		temp;
	int					count;

	count = 0;
	nbr = nb;
	if (nbr > 9)
		count += ft_printunbr(nbr / 10);
	temp = '0' + (char)(nbr % 10);
	count += ft_printchar(temp);
	return (count);
}

#include <stdio.h>

int	ft_printhex(unsigned long int nbr, char *base)
{
	char		temp;
	int			count;

	count = 0;
	if (nbr > 15)
		count += ft_printhex(nbr / 16, base);
	temp = (char)base[(nbr % 16)];
	count += ft_printchar(temp);
	return (count);
}
