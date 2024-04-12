/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: florian <florian@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/31 18:16:32 by florian           #+#    #+#             */
/*   Updated: 2024/04/12 20:37:22 by florian          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

char	**lexer(char *line)
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

t_token	**tokenizer(char **tokens)
{
	t_token	**token_list;
	t_token	*current;
	t_token	*new_node;
	int		i;
	int		cmd_flag;
	int		redirection_flag;

	token_list = malloc(sizeof(t_token *));
	if (!token_list)
		return (NULL);
	*token_list = NULL;
	i = 0;
	cmd_flag = 0;
	redirection_flag = 0;
	while (tokens[i])
	{
		current = *token_list;
		new_node = malloc(sizeof(t_token));
		if (!new_node)
			return (NULL);
		if (i == 0)
			new_node->prev = NULL;
		new_node->value = ft_strdup(tokens[i]);
		new_node->type = get_token_type(tokens[i]);
		if (new_node->type == IN || new_node->type == OUT
			|| new_node->type == APPEND || new_node->type == HEREDOC)
			redirection_flag = 1;
		if (new_node->type == ARG)
		{
			if (cmd_flag == 0 && redirection_flag == 0)
			{
				new_node->type = CMD;
				cmd_flag = 1;
				;
			}
			redirection_flag = 0;
		}
		else if (new_node->type == PIPE)
			cmd_flag = 0;
		new_node->next = NULL;
		if (current == NULL)
			*token_list = new_node;
		else
		{
			while (current->next != NULL)
				current = current->next;
			current->prev = current;
			current->next = new_node;
		}
		i++;
	}
	free_char_tab(tokens);
	return (token_list);
}

void	print_tokens(char **tokens)
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
	t_token *current;
	int i;

	current = *token_list;
	i = 0;
	while (current)
	{
		printf("Token %d: %s\n", i, current->value);
		printf("Type: %d\n", current->type);
		current = current->next;
		i++;
	}
	free_token_list(token_list);
}