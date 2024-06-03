/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   line_to_strings.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: florian <florian@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/05 18:57:09 by florian           #+#    #+#             */
/*   Updated: 2024/06/03 16:29:13 by florian          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	handle_string_quotes(char *line, char **tokens, int *i, int *j)
{
	int	k;
	int	quote;

	quote = line[*i];
	k = 1;
	while (line[*i + k] != quote)
		k++;
	k++;
	tokens[*j] = ft_substr(line, *i, k);
	(*j)++;
	*i += k;
}

void	handle_redirection(char *line, char **tokens, int *i, int *j)
{
	if (line[*i + 1] == line[*i] && line[*i] != '|')
	{
		tokens[*j] = ft_substr(line, *i, 2);
		*i += 2;
	}
	else
	{
		tokens[*j] = ft_substr(line, *i, 1);
		(*i)++;
	}
	(*j)++;
}

void	handle_general(char *line, char **tokens, int *i, int *j)
{
	int	k;

	k = 0;
	while (line[*i + k] && !is_space(line[*i + k]) && line[*i + k] != '\''
		&& line[*i + k] != '"' && line[*i + k] != '|' && line[*i + k] != '>'
		&& line[*i + k] != '<')
		k++;
	tokens[*j] = ft_substr(line, *i, k);
	*i += k;
	(*j)++;
}

char	**line_to_strings(char *line)
{
	char	**tokens;
	int		i;
	int		j;
	int		len;

	len = count_tokens(line);
	tokens = malloc(sizeof(char *) * (len + 1));
	if (!tokens)
		return (NULL);
	i = 0;
	j = 0;
	while (line[i])
	{
		if (line[i] == '\'' || line[i] == '"')
			handle_string_quotes(line, tokens, &i, &j);
		else if (line[i] == '|' || line[i] == '>' || line[i] == '<')
			handle_redirection(line, tokens, &i, &j);
		else if (is_space(line[i]))
			i++;
		else
			handle_general(line, tokens, &i, &j);
	}
	tokens[j] = NULL;
	return (tokens);
}
