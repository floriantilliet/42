/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: florian <florian@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/31 18:16:32 by florian           #+#    #+#             */
/*   Updated: 2024/04/01 16:45:22 by florian          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int check_quote_problems(char *line)
{
	int i;
	int current_quote;

	i = 0;
	current_quote = 0;
	while (line[i])
	{
		if (line[i] == '\'' || line[i] == '"')
		{
			if (current_quote == '\0')
			{
				current_quote = line[i];
			}
			else if (current_quote == line[i])
			{
				current_quote = '\0';
			}
		}
		i++;
	}
	if (current_quote != '\0')
			return (0);
	return (1);
}

int count_tokens(char *line)
{
	int i;
	int j;
	int k;
	int quote;
	
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
			while (line[i+k] != quote)
				k++;
			k++;
			j++;
			i+=k;
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
		if (line[i] == ' ')
			i++;
		else
		{
			k = 0;
			while (line[i + k] && line[i + k] != ' ' && line[i + k] != '\'' && line[i + k] != '"' && line[i + k] != '|' && line[i + k] != '>' && line[i + k] != '<')
				k++;
			j++;
			i += k;
		}
	}
	return (j);
}

char **lexer(char *line)
{
	char **tokens;
	int i;
	int j;
	int k;
	int quote;
	int len;

	len = count_tokens(line);
	tokens = malloc(sizeof(char *) * (len + 1));
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
			while (line[i+k] != quote)
				k++;
			k++;
			tokens[j] = ft_substr(line, i, k);
			j++;
			i+=k;
		}
		else if(line[i] == '|' || line[i] == '>' || line[i] == '<')
		{
			if(line[i + 1] == line[i])
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
		else if (line[i] == ' ')
			i++;
		else
		{
			if (line[i] == '\0')
				break;
			k = 0;
			while (line[i + k] && line[i + k] != ' ' && line[i + k] != '\'' && line[i + k] != '"' && line[i + k] != '|' && line[i + k] != '>' && line[i + k] != '<')
				k++;
			tokens[j] = ft_substr(line, i, k);
			i += k;
			j++;
		}
	}
	tokens[j] = NULL;
	return (tokens);
}

void print_tokens(char **tokens)
{
	int i;

	i = 0;
	while (tokens[i])
	{
		printf("Token %d: %s\n", i, tokens[i]);
		i++;
	}
}