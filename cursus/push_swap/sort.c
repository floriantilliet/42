/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: florian <florian@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/12 12:33:27 by ftilliet          #+#    #+#             */
/*   Updated: 2024/01/22 16:39:56 by florian          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"
#include <stdio.h>

void	radix_sort(t_stack_node **stackA, t_stack_node **stackB)
{
	int	size;
	int	shift;
	int	bit_max;
	int	i;

	bit_max = 0;
	size = ft_double_lstsize(*stackA);
	while (size > 1)
	{
		size /= 2;
		bit_max++;
	}
	size = ft_double_lstsize(*stackA);
	shift = 0;
	while (shift <= bit_max)
	{
		i = 0;
		while (i < size)
		{
			if (((*stackA)->index >> shift) & 1)
				ra(stackA);
			else
				pb(stackA, stackB);
			i++;
		}
		shift++;
		while (*stackB)
			pa(stackA, stackB);
	}
}

void	sort_two(t_stack_node **stack_A)
{
	if ((*stack_A)->index > (*stack_A)->next->index)
		sa(stack_A);
}

void	sort_three(t_stack_node **stack_A)
{
	int	min;
	int	next_min;

	min = get_min(stack_A, -1);
	next_min = get_min(stack_A, min);
	if (is_stack_sorted(stack_A))
		return ;
	if ((*stack_A)->index == min && (*stack_A)->next->index != next_min)
	{
		ra(stack_A);
		sa(stack_A);
		rra(stack_A);
	}
	else if ((*stack_A)->index == next_min)
	{
		if ((*stack_A)->next->index == min)
			sa(stack_A);
		else
			rra(stack_A);
	}
	else
	{
		if ((*stack_A)->next->index == min)
			ra(stack_A);
		else
		{
			sa(stack_A);
			rra(stack_A);
		}
	}
}

void	sort_four(t_stack_node **stack_a, t_stack_node **stack_b)
{
	int	distance;

	if (is_stack_sorted(stack_a))
		return ;
	distance = get_distance(stack_a, get_min(stack_a, -1));
	if (distance == 1)
		ra(stack_a);
	else if (distance == 2)
	{
		ra(stack_a);
		ra(stack_a);
	}
	else if (distance == 3)
		rra(stack_a);
	if (is_stack_sorted(stack_a))
		return ;
	pb(stack_a, stack_b);
	sort_three(stack_a);
	pa(stack_a, stack_b);
}

void	sort_five(t_stack_node **stack_a, t_stack_node **stack_b)
{
	int	distance;

	distance = get_distance(stack_a, get_min(stack_a, -1));
	if (distance == 1)
		ra(stack_a);
	else if (distance == 2)
	{
		ra(stack_a);
		ra(stack_a);
	}
	else if (distance == 3)
	{
		rra(stack_a);
		rra(stack_a);
	}
	else if (distance == 4)
		rra(stack_a);
	if (is_stack_sorted(stack_a))
		return ;
	pb(stack_a, stack_b);
	sort_four(stack_a, stack_b);
	pa(stack_a, stack_b);
}

void	sort_stack(t_stack_node **stack_A, t_stack_node **stack_B)
{
	int	size;

	size = ft_double_lstsize(*stack_A);
	if (size == 2)
		sort_two(stack_A);
	else if (size == 3)
		sort_three(stack_A);
	else if (size == 4)
		sort_four(stack_A, stack_B);
	else if (size == 5)
		sort_five(stack_A, stack_B);
	else
		radix_sort(stack_A, stack_B);
}
