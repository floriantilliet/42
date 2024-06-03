/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   merge_tokens.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: florian <florian@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/03 18:12:49 by florian           #+#    #+#             */
/*   Updated: 2024/06/03 19:05:34 by florian          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	process_arg_cmd(t_token **current, t_token **new_list,
		t_token **last_new_node)
{
	char	*merged_value;
	int		has_cmd;

	merged_value = ft_strdup((*current)->value);
	has_cmd = 0;
	if ((*current)->type == CMD)
		has_cmd = 1;
	while ((*current)->next && ((*current)->next->type == ARG
			|| (*current)->next->type == CMD)
		&& (*current)->next->type != IS_SPACE)
	{
		merged_value = merge_values(merged_value, (*current)->next->value);
		*current = (*current)->next;
		if ((*current)->type == CMD)
			has_cmd = 1;
	}
	if (has_cmd)
		add_new_node(new_list, last_new_node, merged_value, CMD);
	else
		add_new_node(new_list, last_new_node, merged_value, ARG);
}

void	copy_non_arg_cmd(t_token **current, t_token **new_list,
		t_token **last_new_node)
{
	t_token	*new_node;

	new_node = malloc(sizeof(t_token));
	if (!new_node)
	{
		free_new_list(*new_list);
		return ;
	}
	new_node->value = ft_strdup((*current)->value);
	new_node->type = (*current)->type;
	new_node->prev = *last_new_node;
	new_node->next = NULL;
	if (*last_new_node)
		(*last_new_node)->next = new_node;
	else
		*new_list = new_node;
	*last_new_node = new_node;
}

void	process_current_token(t_token **current, t_token **new_list,
		t_token **last_new_node)
{
	if ((*current)->type == ARG || (*current)->type == CMD)
	{
		process_arg_cmd(current, new_list, last_new_node);
	}
	else if ((*current)->type != IS_SPACE)
	{
		copy_non_arg_cmd(current, new_list, last_new_node);
	}
}

t_token	**create_merged_list(t_token *new_list)
{
	t_token	**merged_list;

	merged_list = malloc(sizeof(t_token *));
	if (!merged_list)
	{
		free_new_list(new_list);
		return (NULL);
	}
	*merged_list = new_list;
	return (merged_list);
}

t_token	**merge_tokens(t_token **token_list)
{
	t_token	*current;
	t_token	*new_list;
	t_token	*last_new_node;

	current = *token_list;
	new_list = NULL;
	last_new_node = NULL;
	while (current)
	{
		process_current_token(&current, &new_list, &last_new_node);
		current = current->next;
	}
    free_token_list(token_list);
	return (create_merged_list(new_list));
}
