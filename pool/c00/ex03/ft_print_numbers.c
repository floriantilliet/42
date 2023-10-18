/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_numbers.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ftilliet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/06 15:27:14 by ftilliet          #+#    #+#             */
/*   Updated: 2023/09/06 15:47:50 by ftilliet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>

void	ft_print_numbers(void)
{
	int	chiffre;

	chiffre = 48;
	while (chiffre <= 57)
	{
		write(1, &chiffre, 1);
		chiffre++;
	}	
}
