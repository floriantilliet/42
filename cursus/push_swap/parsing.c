/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ftilliet <ftilliet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/22 16:29:53 by florian           #+#    #+#             */
/*   Updated: 2024/01/31 18:09:22 by ftilliet         ###   ########.fr       */
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
	// if (!check_duplicates(args))
	// {
	// 	if (ac == 2)
	// 		free_tab(args);
	// 	return (0);
	// }
	// if (!check_int_limits(args))
	// {
	// 	if (ac == 2)
	// 		free_tab(args);
	// 	return (0);
	// }
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

// int	check_duplicates(char **args)
// {
// 	int	i;
// 	int	j;

// 	i = 0;
// 	while (args[i])
// 	{
// 		j = i + 1;
// 		while (args[j])
// 		{
// 			if (ft_atoi(args[i]) == ft_atoi(args[j]))
// 			{
// 				ft_putendl_fd("Error", 2);
// 				return (0);
// 			}
// 			j++;
// 		}
// 		i++;
// 	}
// 	return (1);
// }

int check_duplicates(int ac, char **av)
{
	char **args;
	int i;
	int j;

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

long long int	ft_atoll(const char *str)
{
	int				signe;
	long long int	result;

	signe = 1;
	result = 0;
	while ((*str <= 13 && *str >= 9) || *str == ' ')
		str++;
	if (*str == '+' || *str == '-')
	{
		if (*str == '-')
			signe *= -1;
		str++;
	}
	while (*str >= '0' && *str <= '9')
	{
		result = result * 10 + *str - '0';
		str++;
	}
	return (result * signe);
}

// int	check_int_limits(char **args)
// {
// 	int i;
// 	long long int num;

// 	i = 0;
// 	while (args[i])
// 	{
// 		if (ft_strlen(args[i]) > 11)
// 		{
// 			ft_putendl_fd("Error", 2);
// 			return (0);
// 		}
// 		else
// 		{
// 			num = ft_atoll(args[i]);
// 			if (num < INT_MIN || num > INT_MAX)
// 			{
// 				ft_putendl_fd("Error", 2);
// 				return (0);
// 			}
// 			i++;
// 		}
// 	}
// 	return (1);
// }

int check_int_limits(int ac, char **av)
{
	char **args;
	int i;
	long long int num;
	
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
		if (ft_strlen(args[i]) > 11)
		{
			ft_putendl_fd("Error", 2);
			return (0);
		}
		else
		{
			num = ft_atoll(args[i]);
			if (num < INT_MIN || num > INT_MAX)
			{
				ft_putendl_fd("Error", 2);
				return (0);
			}
			i++;
		}
	}
	return (1);
}