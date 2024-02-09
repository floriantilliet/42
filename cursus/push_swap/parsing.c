/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ftilliet <ftilliet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/22 16:29:53 by florian           #+#    #+#             */
/*   Updated: 2024/02/09 09:55:19 by ftilliet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

int	init_stack(t_stack_node **stack, int ac, char **av)
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
		ft_double_lstadd_back(stack, ft_double_lstnew(ft_atoi(args[i++])));
	assign_indexes(*stack);
	if (ac == 2)
		free_tab(args);
	return (1);
}

int	check_args(int ac, char **av)
{
	int	i;
	int	j;

	i = 1;
	while (i < ac)
	{
		j = 1;
		while (av[i][j])
		{
			if (!ft_isdigit(av[i][j]) && av[i][j] != ' ' && av[i][j] != '-'
				&& av[i][j] != '+')
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

int	check_duplicates(int ac, char **av)
{
	char	**args;
	int		i;
	int		j;

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
		j = i + 1;
		while (args[j])
		{
			if (ft_atoi(args[i]) == ft_atoi(args[j]))
				return (ft_putendl_fd("Error", 2), 0);
			j++;
		}
		i++;
	}
	return (1);
}

int	check_int_limits(int ac, char **av)
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
		if (ft_strncmp(args[i], ft_itoa(ft_atoi(args[i])),
				ft_strlen(args[i])) != 0)
			return (ft_putendl_fd("Error", 2), 0);
		i++;
	}
	return (1);
}
