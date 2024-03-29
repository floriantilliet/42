/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hard_coded_sorts.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: florian <florian@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/22 16:44:55 by florian           #+#    #+#             */
/*   Updated: 2024/01/22 17:30:50 by florian          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

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
	if ((*stack_A)->index == min && (*stack_A)->next->index != next_min)
		special_case_one(stack_A);
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
			special_case_two(stack_A);
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
