/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   count_tokens.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: florian <florian@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/05 19:08:09 by florian           #+#    #+#             */
/*   Updated: 2024/06/03 17:08:14 by florian          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	handle_token_quotes(char *line, int *i)
{
	int	k;
	int	quote;

	k = 0;
	quote = line[*i];
	k++;
	while (line[*i + k] != quote)
		k++;
	k++;
	*i += k;
	return (1);
}

int	handle_special_chars(char *line, int *i)
{
	if (line[*i + 1] == line[*i])
	{
		*i += 2;
	}
	else
	{
		(*i)++;
	}
	return (1);
}

int	handle_normal_chars(char *line, int *i)
{
	int	k;

	k = 0;
	while (line[*i + k] && !is_space(line[*i + k]) && line[*i + k] != '\''
		&& line[*i + k] != '"' && line[*i + k] != '|' && line[*i + k] != '>'
		&& line[*i + k] != '<')
		k++;
	*i += k;
	return (1);
}

int	handle_spaces(char *line, int *i)
{
	while (line[*i] && is_space(line[*i]))
		(*i)++;
	return (1);
}

int	count_tokens(char *line)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (line[i])
	{
		if (line[i] == '\'' || line[i] == '"')
			j += handle_token_quotes(line, &i);
		else if (line[i] == '|' || line[i] == '>' || line[i] == '<')
			j += handle_special_chars(line, &i);
		else if (is_space(line[i]))
			j += handle_spaces(line, &i);
		else
			j += handle_normal_chars(line, &i);
	}
	return (j);
}
