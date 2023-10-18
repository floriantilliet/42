/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_comb2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ftilliet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/20 11:54:32 by ftilliet          #+#    #+#             */
/*   Updated: 2023/09/20 11:54:33 by ftilliet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>

void	ft_putnbr(int nb)
{
	long int		nbr;
	char			temp;

	nbr = nb;
	if (nbr < 0)
	{
		nbr *= -1;
		write(1, "-", 1);
	}
	if (nbr > 9)
		ft_putnbr(nbr / 10);
	temp = '0' + (char)(nbr % 10);
	write(1, &temp, 1);
}

void	ft_print_comb2(void)
{	
	int	x;
	int	y;

	x = 0;
	while (x <= 98)
	{
		y = x + 1;
		while (y <= 99)
		{
			if (x < 10)
				write(1, "0", 1);
			ft_putnbr(x);
			write(1, " ", 2);
			if (y < 10)
				write(1, "0", 1);
			ft_putnbr(y);
			if (!(x == 98 && y == 99))
			{
				write(1, ", ", 2);
			}
			y++;
		}
		x++;
	}
}
/*
int main()
{
    ft_print_comb2();
    return 0;
}
*/
