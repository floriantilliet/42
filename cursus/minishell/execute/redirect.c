/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ochetrit <ochetrit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/24 15:11:05 by ochetrit          #+#    #+#             */
/*   Updated: 2024/07/27 15:17:29 by ochetrit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	ft_redirect(int type, t_token *lst)
{
	if (!lst || lst->type != ARG)
		return (FALSE);
	if (type == IN)
	{
		lst->fd = open(lst->value, O_RDONLY);
		if (lst->fd == -1)
			return (ft_printf(ERROR_OPEN, STDERR_FILENO), FALSE);
		if (dup2(lst->fd, STDIN_FILENO) == -1)
			return (ft_printf(ERROR_DUP, STDERR_FILENO), FALSE);
	}
	else
	{
		if (type == APPEND)
			lst->fd = open(lst->value, O_WRONLY | O_CREAT | O_APPEND, 0000644);
		else
			lst->fd = open(lst->value, O_CREAT | O_RDWR | O_TRUNC, 0000644);
		if (lst->fd == -1)
			return (ft_printf(ERROR_OPEN, STDERR_FILENO), FALSE);
		if (dup2(lst->fd, STDOUT_FILENO) == -1)
			return (ft_printf(ERROR_DUP, STDERR_FILENO), FALSE);
	}
	return (TRUE);
}

int	heredoc(t_token *lst, t_env **env)
{
	lst->fd = open(lst->file_n, O_RDWR);
	if (lst->fd == -1)
	{
		ft_printf(ERROR_OPEN, STDERR_FILENO);
		return (exit_status(1, *env), FALSE);
	}
	if (dup2(lst->fd, STDIN_FILENO) == -1)
	{
		ft_printf(ERROR_DUP, STDERR_FILENO);
		return (exit_status(1, *env), FALSE);
	}
	return (TRUE);
}

int	count_len(t_token **tokens, t_cmd *cmd)
{
	t_token	*lst;

	lst = *tokens;
	cmd->len = 0;
	while (lst)
	{
		if (lst->type == ARG)
			cmd->len++;
		else if (lst->type == PIPE)
			return (cmd->is_pipe = 1, TRUE);
		else if (lst->type == CMD)
			cmd->len = 1;
		else if (lst->type == OUT || lst->type == APPEND || lst->type == IN)
			lst = lst->next;
		else
			lst = lst->next;
		lst = lst->next;
	}
	return (TRUE);
}
