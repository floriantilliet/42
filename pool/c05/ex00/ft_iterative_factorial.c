/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_iterative_factorial.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ftilliet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/12 20:26:40 by ftilliet          #+#    #+#             */
/*   Updated: 2023/09/14 18:06:44 by ftilliet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	ft_iterative_factorial(int nb)
{
	int	result;

	if (nb < 0)
		return (0);
	if (nb == 0)
		return (1);
	result = nb;
	while (nb != 1)
	{
		result *= (nb - 1);
		nb--;
	}
	return (result);
}

/*
#include<stdio.h>
int main()
{
        int n = 10;
        printf("%d",ft_iterative_factorial(15));
}
*/
