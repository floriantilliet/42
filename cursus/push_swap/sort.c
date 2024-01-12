/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ftilliet <ftilliet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/12 12:33:27 by ftilliet          #+#    #+#             */
/*   Updated: 2024/01/12 14:05:47 by ftilliet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"
#include <stdio.h>

int	ft_lstsize(t_stack_node *lst)
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
	size = ft_lstsize(*stackA);
	while (size > 1)
	{
		size /= 2;
		bit_max++;
	}
	size = ft_lstsize(*stackA);
	shift = 0;
	while (shift <= bit_max)
	{
		i = 0;
		while (i < size)
		{
			if (((*stackA)->index >> shift) & 1)
				rotate(stackA);
					// Effectue une rotation si le bit correspondant est 1
			else
				push(stackA, stackB);
					// Pousse sur stackB si le bit correspondant est 0
			i++;
		}
		shift++;
		while (*stackB)
			push(stackB, stackA);
				// Remet tous les éléments de stackB dans stackA
	}
}

// #include <time.h>
// #include <stdio.h>

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

// void	add_random_numbers(t_stack_node **stack, int count)
// {
// 	t_stack_node	*new_node;

// 	srand(time(NULL));
// 	int numbers[21] = {0};   // Tableau pour suivre les nombres déjà générés
// 	int generated_count = 0; // Compteur pour les nombres générés
// 	while (generated_count < count)
// 	{
// 		int random_number = rand() % 21 - 10;
// 			// Génère un nombre aléatoire entre -10 et 10
// 		if (numbers[random_number + 10] == 0)
// 			// Vérifie si le nombre n'a pas déjà été généré
// 		{
// 			new_node = malloc(sizeof(t_stack_node));
// 			new_node->value = random_number;
// 			new_node->next = *stack;
// 			new_node->prev = NULL;
// 			if (*stack)
// 				(*stack)->prev = new_node;
// 			*stack = new_node;
// 			numbers[random_number + 10] = 1; // Marque le nombre comme généré
// 			generated_count++;
// 		}
// 	}
// }

// int	main(void)
// {
// 	t_stack_node	*stack;
// 	t_stack_node	*stack_b;

// 	stack = NULL;
// 	stack_b = NULL;
// 	add_random_numbers(&stack, 10);
// 		// Modifier ici pour spécifier le nombre de nombres aléatoires à ajouter
// 	assign_indexes(stack);
// 	print_stack(stack);
// 	print_indexes(stack);
// 	printf("\n");
// 	radix_sort(&stack, &stack_b);
// 	print_stack(stack);
// 	print_indexes(stack);
// 	return (0);
// }
