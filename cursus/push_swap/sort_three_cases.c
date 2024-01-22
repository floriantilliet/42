/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_three_cases.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: florian <florian@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/22 16:51:20 by florian           #+#    #+#             */
/*   Updated: 2024/01/22 16:56:42 by florian          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	sort_case_1(t_stack_node **stack_A, int min, int next_min)
{
	if ((*stack_A)->index == min && (*stack_A)->next->index != next_min)
	{
		sa(stack_A);
		ra(stack_A);
	}
}

void	sort_case_2(t_stack_node **stack_A, int min)
{
	if ((*stack_A)->index == min)
		sa(stack_A);
	else
		rra(stack_A);
}

void	sort_case_3(t_stack_node **stack_A, int min)
{
	if ((*stack_A)->next->index == min)
		ra(stack_A);
	else
	{
		sa(stack_A);
		rra(stack_A);
	}
}
