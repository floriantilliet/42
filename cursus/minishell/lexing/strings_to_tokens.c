/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   strings_to_tokens.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: florian <florian@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/05 18:22:38 by florian           #+#    #+#             */
/*   Updated: 2024/05/05 18:43:00 by florian          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

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

static t_token	*create_token_node(char *value)
{
	t_token	*new_node;

	new_node = malloc(sizeof(t_token));
	if (!new_node)
		return (NULL);
	new_node->value = ft_strdup(value);
	new_node->type = get_token_type(value);
	new_node->prev = NULL;
	new_node->next = NULL;
	return (new_node);
}

static void	add_token_to_list(t_token **token_list, t_token *new_node)
{
	t_token	*current;

	if (*token_list == NULL)
		*token_list = new_node;
	else
	{
		current = *token_list;
		while (current->next != NULL)
			current = current->next;
		current->next = new_node;
		new_node->prev = current;
	}
}

static void	update_flags(t_token *new_node, int *cmd_flag,
		int *redirection_flag)
{
	if (new_node->type == IN || new_node->type == OUT
		|| new_node->type == APPEND || new_node->type == HEREDOC)
		*redirection_flag = 1;
	else if (new_node->type == ARG)
	{
		if (*cmd_flag == 0 && *redirection_flag == 0)
		{
			new_node->type = CMD;
			*cmd_flag = 1;
		}
		*redirection_flag = 0;
	}
	else if (new_node->type == PIPE)
		*cmd_flag = 0;
}

t_token	**strings_to_tokens(char **tokens)
{
	t_token	**token_list;
	t_token	*new_node;
	int		cmd_flag;
	int		redirection_flag;
	int		i;

	token_list = malloc(sizeof(t_token *));
	if (!token_list)
		return (NULL);
	*token_list = NULL;
	cmd_flag = 0;
	redirection_flag = 0;
	i = 0;
	while (tokens[i])
	{
		new_node = create_token_node(tokens[i]);
		if (!new_node)
			return (NULL);
		update_flags(new_node, &cmd_flag, &redirection_flag);
		add_token_to_list(token_list, new_node);
		i++;
	}
	free_char_tab(tokens);
	return (token_list);
}
