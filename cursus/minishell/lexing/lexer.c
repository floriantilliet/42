/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: florian <florian@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/31 18:16:32 by florian           #+#    #+#             */
/*   Updated: 2024/05/05 18:22:21 by florian          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	is_space(char c)
{
	if (c == ' ' || (c >= 9 && c <= 13))
		return (1);
	return (0);
}

int	check_quote_problems(char *line)
{
	int	i;
	int	current_quote;

	i = 0;
	current_quote = 0;
	while (line[i])
	{
		if (line[i] == '\'' || line[i] == '"')
		{
			if (current_quote == '\0')
				current_quote = line[i];
			else if (current_quote == line[i])
				current_quote = '\0';
		}
		i++;
	}
	if (current_quote != '\0')
		return (0);
	return (1);
}

int	count_tokens(char *line)
{
	int	i;
	int	j;
	int	k;
	int	quote;

	i = 0;
	j = 0;
	quote = 0;
	while (line[i])
	{
		if (line[i] == '\'' || line[i] == '"')
		{
			k = 0;
			quote = line[i];
			k++;
			while (line[i + k] != quote)
				k++;
			k++;
			j++;
			i += k;
		}
		if (line[i] == '|' || line[i] == '>' || line[i] == '<')
		{
			if (line[i + 1] == line[i])
			{
				j++;
				i += 2;
			}
			else
			{
				j++;
				i++;
			}
		}
		if (is_space(line[i]))
			i++;
		else
		{
			k = 0;
			while (line[i + k] && !is_space(line[i + k]) && line[i + k] != '\''
				&& line[i + k] != '"' && line[i + k] != '|' && line[i
				+ k] != '>' && line[i + k] != '<')
				k++;
			j++;
			i += k;
		}
	}
	return (j);
}

char	**line_to_strings(char *line)
{
	char	**tokens;
	int		i;
	int		j;
	int		k;
	int		quote;
	int		len;

	len = count_tokens(line);
	tokens = malloc(sizeof(char *) * (len + 1));
	if (!tokens)
		return (NULL);
	i = 0;
	j = 0;
	quote = 0;
	while (line[i])
	{
		if (line[i] == '\'' || line[i] == '"')
		{
			k = 0;
			quote = line[i];
			k++;
			while (line[i + k] != quote)
				k++;
			k++;
			tokens[j] = ft_substr(line, i, k);
			j++;
			i += k;
		}
		else if (line[i] == '|' || line[i] == '>' || line[i] == '<')
		{
			if (line[i + 1] == line[i] && line[i] != '|')
			{
				tokens[j] = ft_substr(line, i, 2);
				j++;
				i += 2;
			}
			else
			{
				tokens[j] = ft_substr(line, i, 1);
				j++;
				i++;
			}
		}
		else if (is_space(line[i]))
			i++;
		else
		{
			if (line[i] == '\0')
				break ;
			k = 0;
			while (line[i + k] && !is_space(line[i + k]) && line[i + k] != '\''
				&& line[i + k] != '"' && line[i + k] != '|' && line[i
				+ k] != '>' && line[i + k] != '<')
				k++;
			tokens[j] = ft_substr(line, i, k);
			i += k;
			j++;
		}
	}
	tokens[j] = NULL;
	return (tokens);
}

int	get_token_type(char *token)
{
	int	len;

	len = ft_strlen(token);
	if (len == 1)
	{
		if (token[0] == '|')
			return (PIPE);
		if (token[0] == '>')
			return (OUT);
		if (token[0] == '<')
			return (IN);
		else
			return (ARG);
	}
	else if (len == 2)
	{
		if (token[0] == '>' && token[1] == '>')
			return (APPEND);
		if (token[0] == '<' && token[1] == '<')
			return (HEREDOC);
		else
			return (ARG);
	}
	else
		return (ARG);
}

void	print_strings(char **tokens)
{
	int	i;

	i = 0;
	while (tokens[i])
	{
		printf("Token %d: %s\n", i, tokens[i]);
		i++;
	}
}

void	print_token_list(t_token **token_list)
{
	t_token	*current;
	int		i;

	current = *token_list;
	i = 0;
	while (current)
	{
		printf("Token %d: %s\n", i, current->value);
		printf("Type: %d\n", current->type);
		current = current->next;
		i++;
	}
}
