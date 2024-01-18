/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: florian <florian@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/11 14:12:08 by ftilliet          #+#    #+#             */
/*   Updated: 2024/01/18 16:46:49 by florian          ###   ########.fr       */
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

static void	init_stack(t_stack_node **stack, int ac, char **av)
{
	char	**args;
	int		i;

	i = 0;
	if (ac == 2)
		args = ft_split(av[1], ' ');
	else
	{
		i = 1;
		args = av;
	}
	while (args[i])
	{
		ft_double_lstadd_back(stack, ft_double_lstnew(ft_atoi(args[i])));
		i++;
	}
	assign_indexes(*stack);
	// if (ac == 2)
	// 	ft_free(args);
}

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

int check_args(int ac, char **av)
{
    int i;
    int j;

    i = 1;
    while (i < ac)
    {
        j = 0;
        while (av[i][j])
        {
            if (!ft_isdigit(av[i][j]) && av[i][j] != ' ')
            {
                ft_putendl_fd("Error", 2);
                return (0);
            }
            j++;
        }
        i++;
    }
    return (1);
}

int	main(int ac, char **av)
{
	t_stack_node **stack_a;
	t_stack_node **stack_b;

	if (ac < 2)
		ft_putendl_fd("Error", 2);
    if (!check_args(ac, av))
    {
        return (0);
    }
	stack_a = (t_stack_node **)malloc(sizeof(t_stack_node));
	stack_b = (t_stack_node **)malloc(sizeof(t_stack_node));
	*stack_a = NULL;
	*stack_b = NULL;
	init_stack(stack_a, ac, av);
	if (is_stack_sorted(stack_a))
		return (0);
	sort_stack(stack_a, stack_b);
	print_stack(*stack_a);
	return (0);
}