/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   double_lists_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: florian <florian@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/22 16:32:02 by florian           #+#    #+#             */
/*   Updated: 2024/01/22 16:32:45 by florian          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

t_stack_node	*ft_double_lstnew(int content)
{
	t_stack_node	*new;

	new = malloc(sizeof(t_stack_node));
	if (!new)
	{
		return (NULL);
	}
	new->value = content;
	new->next = NULL;
	new->prev = NULL;
	return (new);
}

t_stack_node	*ft_double_lstlast(t_stack_node *lst)
{
	t_stack_node	*current;

	if (!lst)
		return (NULL);
	current = lst;
	while (current->next)
	{
		current = current->next;
	}
	return (current);
}

void	ft_double_lstadd_back(t_stack_node **head, t_stack_node *new)
{
	t_stack_node	*last;

	if (head)
	{
		if (*head)
		{
			last = ft_double_lstlast(*head);
			last->next = new;
		}
		else
			*head = new;
	}
}

void	ft_double_lstadd_front(t_stack_node **head, t_stack_node *new)
{
	if (head)
	{
		new->next = *head;
		*head = new;
	}
}

int	ft_double_lstsize(t_stack_node *lst)
{
	size_t			size;
	t_stack_node	*current;

	if (!lst)
		return (0);
	current = lst;
	size = 0;
	while (current)
	{
		size++;
		current = current->next;
	}
	return (size);
}
