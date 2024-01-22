/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   swap.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: florian <florian@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/22 13:38:31 by florian           #+#    #+#             */
/*   Updated: 2024/01/22 16:42:49 by florian          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	swap(t_stack_node **head)
{
	t_stack_node	*tmp;

	if (*head && (*head)->next)
	{
		tmp = (*head)->next;
		(*head)->next = tmp->next;
		(*head)->prev = tmp;
		tmp->next = *head;
		tmp->prev = NULL;
		*head = tmp;
	}
}

void	sa(t_stack_node **head)
{
	swap(head);
	ft_putendl_fd("sa", 1);
}

void	sb(t_stack_node **head)
{
	swap(head);
	ft_putendl_fd("sb", 1);
}

void	ss(t_stack_node **head, t_stack_node **head_b)
{
	swap(head);
	swap(head_b);
	ft_putendl_fd("ss", 1);
}
