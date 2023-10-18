/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_sqrt.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ftilliet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/13 09:55:56 by ftilliet          #+#    #+#             */
/*   Updated: 2023/09/14 18:15:55 by ftilliet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	ft_sqrt(int nb)
{
	unsigned int	i;

	i = 1;
	while (i <= (nb / i))
	{
		if (i * i == (unsigned int)nb)
			return (i);
		i++;
	}
	return (0);
}

/*
#include<stdio.h>
int main()
{
	printf("%d", ft_sqrt(1102500));
}
*/
