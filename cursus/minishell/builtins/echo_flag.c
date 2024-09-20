/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo_flag.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ochetrit <ochetrit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/18 11:28:12 by ochetrit          #+#    #+#             */
/*   Updated: 2024/07/18 11:28:30 by ochetrit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	is_flag(char *str)
{
	int	i;

	i = 0;
	if (str[i] == '-')
	{
		i++;
		while (str[i] && str[i] == 'n')
			i++;
		if (!str[i])
			return (1);
	}
	return (0);
}

int	skip_flag(char	*str)
{
	int	i;

	i = 0;
	if (str[i] == '-')
	{
		i++;
		while (str[i] && str[i] == 'n')
			i++;
		if (!str[i])
			return (1);
	}
	return (0);
}
