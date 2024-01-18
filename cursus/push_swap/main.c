/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: florian <florian@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/11 14:12:08 by ftilliet          #+#    #+#             */
/*   Updated: 2024/01/18 12:25:17 by florian          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"
#include <stdio.h>

void	print_stack(t_stack_node *head)
{
	while (head != NULL)
	{
		printf("%d ", head->value);
		head = head->next;
	}
	printf("\n");
}

void	print_indexes(t_stack_node *head)
{
	while (head != NULL)
	{
		printf("%d ", head->index);
		head = head->next;
	}
	printf("\n");
}

int main(int ac, char **av)
{
    t_stack_node	**stack_a;
	t_stack_node	**stack_b;
	stack_a = (t_stack_node **)malloc(sizeof(t_stack_node));
	stack_b = (t_stack_node **)malloc(sizeof(t_stack_node));
	*stack_a = NULL;
	*stack_b = NULL;
    if (ac > 1)
    {
        while (ac > 1)
        {
            if (stack_a != NULL)
            {
                ft_double_lstadd_front(stack_a, ft_double_lstnew(ft_atoi(av[ac - 1])));
            }
            ac--;
        }
        assign_indexes(*stack_a);
        print_stack(*stack_a);
        radix_sort(stack_a, stack_b);
        print_stack(*stack_a);
    }
    else
        ft_putendl_fd("Error", 2);
    return (0);
}