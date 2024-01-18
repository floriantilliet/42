/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: florian <florian@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/12 12:33:27 by ftilliet          #+#    #+#             */
/*   Updated: 2024/01/18 18:38:52 by florian          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"
#include <stdio.h>

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

void	radix_sort(t_stack_node **stackA, t_stack_node **stackB)
{
	int	size;
	int	shift;
	int	bit_max;
	int	i;

	// Calculer bit_max en fonction de la taille de la liste
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
			// Effectue une rotation si le bit correspondant est 1
			else
				pb(stackA, stackB);
			// Pousse sur stackB si le bit correspondant est 0
			i++;
		}
		shift++;
		while (*stackB)
			pa(stackA, stackB);
		// Remet tous les éléments de stackB dans stackA
	}
}

void	sort_two(t_stack_node **stack_A)
{
	if ((*stack_A)->index > (*stack_A)->next->index)
		sa(stack_A);
}

void	sort_three(t_stack_node **stack_A)
{
	if ((*stack_A)->index == 0 && (*stack_A)->next->index == 2
		&& (*stack_A)->next->next->index == 1)
	{
		sa(stack_A);
		ra(stack_A);
	}
	else if ((*stack_A)->index == 1)
	{
		if ((*stack_A)->next->index == 0)
			sa(stack_A);
		else
			rra(stack_A);
	}
	else if ((*stack_A)->index == 2)
	{
		if ((*stack_A)->next->index == 0)
			ra(stack_A);
		else
		{
			sa(stack_A);
			rra(stack_A);
		}
	}
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
#include <stdio.h>
#include <time.h>

// void	print_stack(t_stack_node *head)
// {
// 	while (head != NULL)
// 	{
// 		printf("%d ", head->value);
// 		head = head->next;
// 	}
// 	printf("\n");
// }

// void	print_indexes(t_stack_node *head)
// {
// 	while (head != NULL)
// 	{
// 		printf("%d ", head->index);
// 		head = head->next;
// 	}
// 	printf("\n");
// }

void	add_random_numbers(t_stack_node **stack, int count)
{
	t_stack_node	*new_node;
	int				random_number;

	srand(time(NULL));
	int numbers[2001] = {0}; // Array to track the generated numbers
	int generated_count = 0; // Counter for generated numbers
	while (generated_count < count)
	{
		random_number = rand() % 2001 - 1000;
		// Generate a random number between -1000 and 1000
		if (numbers[random_number + 1000] == 0)
		{
			// Check if the number has not been generated already
			new_node = malloc(sizeof(t_stack_node));
			new_node->value = random_number;
			new_node->next = *stack;
			new_node->prev = NULL;
			if (*stack)
				(*stack)->prev = new_node;
			*stack = new_node;
			numbers[random_number + 1000] = 1; // Mark the number as generated
			generated_count++;
		}
	}
}

// int	main(void)
// {
// 	t_stack_node	*stack;
// 	t_stack_node	*stack_b;

// 	stack = NULL;
// 	stack_b = NULL;
// 	add_random_numbers(&stack, 500);
// 	// Modifier ici pour spécifier le nombre de nombres aléatoires à ajouter
// 	assign_indexes(stack);
// 	// print_stack(stack);
// 	// print_stack(stack_b);
// 	// print_indexes(stack);
// 	// printf("\n");
// 	// pb(&stack, &stack_b);
// 	radix_sort(&stack, &stack_b);
// 	// sort_two(&stack);
// 	// sort_three(&stack);
// 	// print_stack(stack);
// 	// print_stack(stack_b);
// 	// print_indexes(stack);
// 	return (0);
// }
