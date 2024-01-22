/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_three_cases.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: florian <florian@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/22 16:51:20 by florian           #+#    #+#             */
/*   Updated: 2024/01/22 17:30:53 by florian          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	special_case_one(t_stack_node **stack_A)
{
	ra(stack_A);
	sa(stack_A);
	rra(stack_A);
}

void	special_case_two(t_stack_node **stack_A)
{
	sa(stack_A);
	rra(stack_A);
}
