/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   merge_tokens.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: florian <florian@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/03 18:12:49 by florian           #+#    #+#             */
/*   Updated: 2024/06/04 13:30:56 by florian          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	process_arg_cmd(t_token **current, t_token **new_list,
		t_token **last_new_node, t_flags *flags)
{
	char	*merged_value;
	int		type;

	merged_value = ft_strdup((*current)->value);
	while ((*current)->next && ((*current)->next->type == ARG
			|| (*current)->next->type == CMD))
	{
		merged_value = merge_values(merged_value, (*current)->next->value);
		*current = (*current)->next;
	}
	if (flags->cmd_flag == 0 && flags->redirection_flag != 2
		&& flags->pipe_flag == 0)
		type = CMD;
	else
		type = ARG;
	add_new_node(new_list, last_new_node, merged_value, type);
	update_token_flags(*last_new_node, flags);
}

void	copy_non_arg_cmd(t_token **current, t_token **new_list,
		t_token **last_new_node, t_flags *flags)
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
	update_token_flags(new_node, flags);
}

void	process_current_token(t_token **current, t_token **new_list,
		t_token **last_new_node, t_flags *flags)
{
	if ((*current)->type == IS_SPACE)
		return ;
	if ((*current)->type == ARG || (*current)->type == CMD)
	{
		process_arg_cmd(current, new_list, last_new_node, flags);
	}
	else
	{
		copy_non_arg_cmd(current, new_list, last_new_node, flags);
	}
}

t_token	**merge_tokens(t_token **token_list)
{
	t_token	*current;
	t_token	*new_list;
	t_token	*last_new_node;
	t_flags	flags;

	if (!token_list || !*token_list)
		return (NULL);
	initialize_merge_vars(&current, token_list, &flags);
	last_new_node = NULL;
	new_list = NULL;
	while (current)
	{
		process_current_token(&current, &new_list, &last_new_node, &flags);
		if (current)
			current = current->next;
	}
	free_token_list(token_list);
	return (create_merged_list(new_list));
}
