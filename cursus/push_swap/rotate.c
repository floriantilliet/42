/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotate.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: florian <florian@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/22 13:39:06 by florian           #+#    #+#             */
/*   Updated: 2024/01/22 16:39:51 by florian          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	rotate(t_stack_node **head)
{
	t_stack_node	*tmp;

	if (*head && (*head)->next)
	{
		tmp = *head;
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = *head;
		*head = (*head)->next;
		tmp->next->next = NULL;
		tmp->next->prev = tmp;
	}
}

void	ra(t_stack_node **head)
{
	rotate(head);
	ft_putendl_fd("ra", 1);
}

void	rb(t_stack_node **head)
{
	rotate(head);
	ft_putendl_fd("rb", 1);
}

void	rr(t_stack_node **head, t_stack_node **head_b)
{
	rotate(head);
	rotate(head_b);
	ft_putendl_fd("rr", 1);
}
