/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ftilliet <ftilliet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/11 14:12:08 by ftilliet          #+#    #+#             */
/*   Updated: 2024/02/09 09:36:36 by ftilliet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

int	main(int ac, char **av)
{
	t_stack_node	**stack_a;
	t_stack_node	**stack_b;

	if (ac < 2)
	{
		return (0);
		ft_putendl_fd("Error", 2);
	}
	if (!check_args(ac, av))
		return (0);
	if (!check_duplicates(ac, av))
		return (0);
	if (!check_int_limits(ac, av))
		return (0);
	stack_a = malloc(sizeof(t_stack_node *));
	stack_b = malloc(sizeof(t_stack_node *));
	*stack_a = NULL;
	*stack_b = NULL;
	if (!init_stack(stack_a, ac, av))
		return (free_stack(stack_a), free(stack_b), 0);
	if (is_stack_sorted(stack_a))
		return (free_stack(stack_a), free(stack_b), 0);
	sort_stack(stack_a, stack_b);
	return (free_stack(stack_a), free(stack_b), 0);
}
