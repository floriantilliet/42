/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: florian <florian@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/22 13:37:47 by florian           #+#    #+#             */
/*   Updated: 2024/01/22 16:42:23 by florian          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	push(t_stack_node **head_start, t_stack_node **head_end)
{
	t_stack_node	*tmp;

	if (*head_start)
	{
		tmp = *head_start;
		*head_start = (*head_start)->next;
		tmp->next = *head_end;
		*head_end = tmp;
	}
}

void	pa(t_stack_node **head_a, t_stack_node **head_b)
{
	push(head_b, head_a);
	ft_putendl_fd("pa", 1);
}

void	pb(t_stack_node **head_a, t_stack_node **head_b)
{
	push(head_a, head_b);
	ft_putendl_fd("pb", 1);
}
