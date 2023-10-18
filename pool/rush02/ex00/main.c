/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rdupeux <rdupeux@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/22 21:21:52 by dferrari          #+#    #+#             */
/*   Updated: 2023/09/24 23:19:44 by rdupeux          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft.h"

void	display(char *str)
{
	if (str[0] == ' ')
		write(1, &str[1], ft_strlen(str) - 1);
	else
		write(1, str, ft_strlen(str));
	write(1, "\n", 1);
	free(str);
}

int	check_str(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] < '0' || str[i] > '9')
			return (0);
		i++;
	}
	return (1);
}

t_dict	*check_input(int argc, char **argv)
{
	t_dict	*dict;

	if (!(argc == 2 || argc == 3))
	{
		ft_print_error();
		return (NULL);
	}
	if (argc == 2)
	{
		if (!check_str(argv[1]))
			return (NULL);
		else
			dict = get_dict(NULL);
	}
	if (argc == 3)
	{
		dict = get_dict(argv[1]);
		if (!check_str(argv[2]) || !dict)
			return (NULL);
	}
	return (dict);
}

int	main(int argc, char **argv)
{
	t_dict	*dict;
	char	*res;
	int		i;

	dict = check_input(argc, argv);
	i = argc - 1;
	if (!dict)
		return (0);
	if (argv[i][0] == '0' && ft_strlen(argv[i]) == 1)
	{
		display(get("0", dict));
		free_dict(dict);
		return (0);
	}
	argv[i] = normalyze_input(argv[i]);
	res = malloc(1);
	res[0] = 0;
	res = gen_res(dict, argv[i], res);
	free(argv[i]);
	if (!res)
	{
		return (0);
	}
	display(res);
	free_dict(dict);
}
