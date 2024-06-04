/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   merge_flags.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: florian <florian@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/04 13:31:07 by florian           #+#    #+#             */
/*   Updated: 2024/06/04 13:31:14 by florian          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	update_arg_cmd_flags(t_token *new_node, t_flags *flags)
{
	if (flags->redirection_flag == 1)
	{
		new_node->type = ARG;
		flags->redirection_flag = 2;
	}
	else if (flags->redirection_flag == 2)
	{
		if (flags->cmd_flag == 0)
			new_node->type = CMD;
		else
			new_node->type = ARG;
		flags->cmd_flag = 1;
		flags->redirection_flag = 0;
	}
	else if (flags->cmd_flag == 0)
	{
		new_node->type = CMD;
		flags->cmd_flag = 1;
	}
	else
	{
		new_node->type = ARG;
	}
}

void	update_token_flags(t_token *new_node, t_flags *flags)
{
	if (new_node->type == IN || new_node->type == OUT
		|| new_node->type == APPEND || new_node->type == HEREDOC)
	{
		flags->redirection_flag = 1;
	}
	else if (new_node->type == ARG || new_node->type == CMD)
	{
		update_arg_cmd_flags(new_node, flags);
	}
	else if (new_node->type == PIPE)
	{
		flags->cmd_flag = 0;
		flags->redirection_flag = 0;
		flags->pipe_flag = 1;
	}
	else
	{
		flags->pipe_flag = 0;
	}
}
