/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   radix_sort.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: florian <florian@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/22 16:44:13 by florian           #+#    #+#             */
/*   Updated: 2024/01/22 17:33:38 by florian          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	sort_by_bit(t_stack_node **stackA, t_stack_node **stackB, int size,
		int shift)
{
	int	i;

	i = 0;
	while (i < size)
	{
		if (((*stackA)->index >> shift) & 1)
			ra(stackA);
		else
			pb(stackA, stackB);
		i++;
	}
}

void	radix_sort(t_stack_node **stackA, t_stack_node **stackB)
{
	int	size;
	int	shift;
	int	bit_max;

	bit_max = 0;
	size = ft_double_lstsize(*stackA);
	while (size > 1)
	{
		size /= 2;
		bit_max++;
	}
	shift = 0;
	while (shift <= bit_max)
	{
		size = ft_double_lstsize(*stackA);
		sort_by_bit(stackA, stackB, size, shift);
		shift++;
		while (*stackB)
			pa(stackA, stackB);
	}
}
