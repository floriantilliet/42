/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ftilliet <ftilliet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/22 16:29:53 by florian           #+#    #+#             */
/*   Updated: 2024/02/09 12:23:07 by ftilliet         ###   ########.fr       */
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
				return (ft_putendl_fd("Error", 2), 0);
			j++;
		}
		i++;
	}
	return (1);
}

int	check_args_for_duplicates(char **args, int ac)
{
	int	i;
	int	j;

	i = 0;
	while (args[i])
	{
		j = i + 1;
		while (args[j])
		{
			if (ft_atoi(args[i]) == ft_atoi(args[j]))
				return (free_tab_and_print_error(args, ac), 0);
			j++;
		}
		i++;
	}
	return (1);
}

int	check_duplicates(int ac, char **av)
{
	char	**args;

	if (ac == 2)
		args = ft_split(av[1], ' ');
	else
	{
		args = av + 1;
	}
	if (!check_args_for_duplicates(args, ac))
		return (0);
	if (ac == 2)
		free_tab(args);
	return (1);
}

int	check_int_limits(int ac, char **av)
{
	char	**args;
	int		i;
	char	*str;

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
		str = ft_itoa(ft_atoi(args[i]));
		if (ft_strncmp(args[i], str, ft_strlen(args[i])) != 0)
			return (free_tab_and_print_error(args, ac), free(str), 0);
		free(str);
		i++;
	}
	if (ac == 2)
		free_tab(args);
	return (1);
}
