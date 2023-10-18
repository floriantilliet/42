/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_iterative_power.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ftilliet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/12 20:36:10 by ftilliet          #+#    #+#             */
/*   Updated: 2023/09/14 18:16:46 by ftilliet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	ft_iterative_power(int nb, int power)
{
	int	result;

	if (power < 0)
		return (0);
	if (power == 0)
		return (1);
	result = nb;
	while (power != 1)
	{
		result *= (nb);
		power--;
	}
	return (result);
}

/*
#include<stdio.h>
int main()
{
        printf("%d",ft_iterative_power(2,1));
}
*/
