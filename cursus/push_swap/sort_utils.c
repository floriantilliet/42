/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: florian <florian@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/22 16:30:37 by florian           #+#    #+#             */
/*   Updated: 2024/01/22 16:31:32 by florian          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

int	is_stack_sorted(t_stack_node **head)
{
	t_stack_node	*tmp;

	tmp = *head;
	while (tmp->next)
	{
		if (tmp->value > tmp->next->value)
			return (0);
		tmp = tmp->next;
	}
	return (1);
}

int	get_distance(t_stack_node **stack, int val)
{
	t_stack_node	*head;
	int				distance;

	head = *stack;
	distance = 0;
	while (head->index != val)
	{
		head = head->next;
		distance++;
	}
	return (distance);
}

int	get_min(t_stack_node **stack, int val)
{
	t_stack_node	*head;
	int				min;

	head = *stack;
	min = head->index;
	while (head->next)
	{
		head = head->next;
		if ((head->index < min) && head->index != val)
			min = head->index;
	}
	return (min);
}

void	assign_indexes(t_stack_node *head)
{
	t_stack_node	*current;
	t_stack_node	*iterator;
	int				index;

	current = head;
	while (current != NULL)
	{
		index = 0;
		iterator = head;
		while (iterator != NULL)
		{
			if (iterator->value < current->value)
				index++;
			iterator = iterator->next;
		}
		current->index = index;
		current = current->next;
	}
}
