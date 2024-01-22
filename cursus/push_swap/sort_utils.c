/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: florian <florian@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/22 16:30:37 by florian           #+#    #+#             */
/*   Updated: 2024/01/22 16:54:24 by florian          ###   ########.fr       */
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
