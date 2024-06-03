/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   merging_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: florian <florian@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/03 19:02:39 by florian           #+#    #+#             */
/*   Updated: 2024/06/03 19:04:47 by florian          ###   ########.fr       */
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
