/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printnbrs.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ftilliet <ftilliet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/13 15:22:06 by ftilliet          #+#    #+#             */
/*   Updated: 2023/11/15 16:47:49 by ftilliet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

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
		count += ft_printchar('-');
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
