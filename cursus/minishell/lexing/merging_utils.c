/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   merging_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ochetrit <ochetrit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/03 19:02:39 by florian           #+#    #+#             */
/*   Updated: 2024/07/25 13:38:08 by ochetrit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	free_new_list(t_token *new_list)
{
	t_token	*tmp;

	while (new_list)
	{
		tmp = new_list;
		new_list = new_list->next;
		free(tmp->value);
		free(tmp);
	}
}

char	*merge_values(char *merged_value, char *next_value)
{
	char	*temp;

	temp = ft_strjoin(merged_value, next_value);
	free(merged_value);
	return (temp);
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

void	initialize_merge_vars(t_token **current, t_token **token_list,
		t_flags *flags)
{
	*current = *token_list;
	flags->cmd_flag = 0;
	flags->redirection_flag = 0;
	flags->pipe_flag = 0;
}

void	add_new_node(t_token **new_list, t_token **last_new_node, char *value,
		int type)
{
	t_token	*new_node;

	new_node = malloc(sizeof(t_token));
	if (!new_node)
	{
		free(value);
		free_new_list(*new_list);
		return ;
	}
	new_node->value = value;
	new_node->type = type;
	new_node->prev = *last_new_node;
	new_node->next = NULL;
	if (*last_new_node)
		(*last_new_node)->next = new_node;
	else
		*new_list = new_node;
	*last_new_node = new_node;
}
