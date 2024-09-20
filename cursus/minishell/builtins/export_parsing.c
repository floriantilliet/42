/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_parsing.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ochetrit <ochetrit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/18 11:19:22 by ochetrit          #+#    #+#             */
/*   Updated: 2024/07/18 11:20:03 by ochetrit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	parsing_export(char *str)
{
	if (*str != '_' && !ft_isalpha(*str) && *str)
	{
		ft_printf(ERR_EXPORT, STDERR_FILENO, str);
		return (FALSE);
	}
	str++;
	while (*str)
	{
		if (*str == '=' || (*str == '+' && *(str + 1) == '='))
			break ;
		else if (*str != '_' && !ft_isalnum(*str))
		{
			ft_printf(ERR_EXPORT, STDERR_FILENO, str);
			return (FALSE);
		}
		str++;
	}
	return (TRUE);
}
