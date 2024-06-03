/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_types.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: florian <florian@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/03 17:44:16 by florian           #+#    #+#             */
/*   Updated: 2024/06/03 17:44:18 by florian          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	check_token_chars(char *token, int len)
{
	if (len == 1)
	{
		if (token[0] == '|')
			return (PIPE);
		if (token[0] == '>')
			return (OUT);
		if (token[0] == '<')
			return (IN);
	}
	else if (len == 2)
	{
		if (token[0] == '>' && token[1] == '>')
			return (APPEND);
		if (token[0] == '<' && token[1] == '<')
			return (HEREDOC);
	}
	return (ARG);
}

int	get_token_type(char *token)
{
	int	len;

	len = ft_strlen(token);
	if (is_space(token[0]))
		return (IS_SPACE);
	else
		return (check_token_chars(token, len));
}
