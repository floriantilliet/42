/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ftilliet <ftilliet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/11 14:12:08 by ftilliet          #+#    #+#             */
/*   Updated: 2024/01/16 18:13:38 by ftilliet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"
#include <stdio.h>

int main(int ac, char **av)
{
    t_stack_node	*stack;
	t_stack_node	*stack_b;

	stack = NULL;
	stack_b = NULL;

    if (ac > 1)
    {
        while (ac > 1)
        {
            if (stack_b != NULL)
            {
                (*stack_b).value = ft_atoi(av[ac - 1]);
            }
            push(&stack, &stack_b);
            ac--;
        }
        assign_indexes(stack);
        radix_sort(&stack, &stack_b);
    }
    else
        ft_putendl_fd("Error", 2);
    

    return (0);
}