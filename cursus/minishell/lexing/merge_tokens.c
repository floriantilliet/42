/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   merge_tokens.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: florian <florian@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/03 18:12:49 by florian           #+#    #+#             */
/*   Updated: 2024/06/04 11:37:30 by florian          ###   ########.fr       */
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

void	add_new_node(t_token **new_list, t_token **last_new_node, char *value, int type)
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

void	update_token_flags(t_token *new_node, int *cmd_flag, int *redirection_flag, int *pipe_flag)
{
	if (new_node->type == IN || new_node->type == OUT
		|| new_node->type == APPEND || new_node->type == HEREDOC)
	{
		*redirection_flag = 1;
	}
	else if (new_node->type == ARG || new_node->type == CMD)
	{
		if (*redirection_flag == 1)
		{
			new_node->type = ARG;  // First token after redirection is ARG
			*redirection_flag = 2;  // Set to 2 to indicate the next one should be CMD
		}
		else if (*redirection_flag == 2)
		{
			new_node->type = (*cmd_flag == 0) ? CMD : ARG;  // Second token after redirection is CMD if no CMD in the section
			*cmd_flag = 1;  // Ensure that subsequent tokens are not converted to CMD
			*redirection_flag = 0;  // Reset the redirection flag
		}
		else if (*cmd_flag == 0)
		{
			new_node->type = CMD;  // First token in the section is CMD if no CMD has been set
			*cmd_flag = 1;
		}
		else
		{
			new_node->type = ARG;  // Any subsequent tokens are ARG
		}
	}
	else if (new_node->type == PIPE)
	{
		*cmd_flag = 0;  // Reset cmd_flag for the new section
		*redirection_flag = 0;
		*pipe_flag = 1;  // Set pipe_flag to indicate a pipe has been encountered
	}
	else
	{
		*pipe_flag = 0;  // Reset pipe_flag if the token is not a PIPE
	}
}

void	process_arg_cmd(t_token **current, t_token **new_list, t_token **last_new_node, int *cmd_flag, int *redirection_flag, int *pipe_flag)
{
	char	*merged_value;

	merged_value = ft_strdup((*current)->value);
	while ((*current)->next && ((*current)->next->type == ARG || (*current)->next->type == CMD))
	{
		merged_value = merge_values(merged_value, (*current)->next->value);
		*current = (*current)->next;
	}
	add_new_node(new_list, last_new_node, merged_value, (*cmd_flag == 0 && *redirection_flag != 2 && *pipe_flag == 0) ? CMD : ARG);
	update_token_flags(*last_new_node, cmd_flag, redirection_flag, pipe_flag);
}

void	copy_non_arg_cmd(t_token **current, t_token **new_list, t_token **last_new_node, int *cmd_flag, int *redirection_flag, int *pipe_flag)
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
	update_token_flags(new_node, cmd_flag, redirection_flag, pipe_flag);
}

void	process_current_token(t_token **current, t_token **new_list, t_token **last_new_node, int *cmd_flag, int *redirection_flag, int *pipe_flag)
{
	if ((*current)->type == IS_SPACE)
		return;

	if ((*current)->type == ARG || (*current)->type == CMD)
	{
		process_arg_cmd(current, new_list, last_new_node, cmd_flag, redirection_flag, pipe_flag);
	}
	else
	{
		copy_non_arg_cmd(current, new_list, last_new_node, cmd_flag, redirection_flag, pipe_flag);
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
	if (!token_list || !*token_list)
		return NULL;

	t_token	*current;
	t_token	*new_list;
	t_token	*last_new_node;
	int		cmd_flag;
	int		redirection_flag;
	int		pipe_flag;

	current = *token_list;
	new_list = NULL;
	last_new_node = NULL;
	cmd_flag = 0;
	redirection_flag = 0;
	pipe_flag = 0;

	while (current)
	{
		process_current_token(&current, &new_list, &last_new_node, &cmd_flag, &redirection_flag, &pipe_flag);
		current = current ? current->next : NULL;
	}
	free_token_list(token_list);
	return (create_merged_list(new_list));
}
