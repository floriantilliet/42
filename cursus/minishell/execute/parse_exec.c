/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_exec.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ochetrit <ochetrit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/06 16:20:48 by ochetrit          #+#    #+#             */
/*   Updated: 2024/09/11 20:38:17 by ochetrit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	init_head(t_token **tokens)
{
	t_token	*lst;

	lst = *tokens;
	while (lst)
	{
		lst->head = *tokens;
		lst = lst->next;
	}
}

int	check_pipe(t_token **tokens)
{
	t_token	*lst;

	lst = *tokens;
	lst->if_pipe = 0;
	init_head(tokens);
	while (lst)
	{
		if (lst->type == PIPE && !lst->next)
			return (ft_printf(ERR_PIPE, STDERR_FILENO), FALSE);
		else if (lst->type >= OUT && !lst->next)
			return (ft_printf(ERR_REDIR, STDERR_FILENO), FALSE);
		else if (lst->type >= OUT && lst->next->type != ARG)
		{
			ft_printf(ERR_REDIRECT_2, STDERR_FILENO);
			return (ft_printf("'%s'\n", STDERR_FILENO, lst->next->value),
				FALSE);
		}
		else if (lst->type == PIPE)
			lst->head->if_pipe++;
		lst = lst->next;
	}
	return (TRUE);
}

void	parse_exec(t_token **tokens, t_env **env)
{
	t_token	*lst;

	lst = *tokens;
	while (lst->head->if_pipe && lst)
	{
		if (!do_cmd(tokens, lst, env))
			return ;
		lst->head->if_pipe--;
		while (lst && lst->type != PIPE)
			lst = lst->next;
		if (lst)
			lst = lst->next;
	}
	last_cmd(tokens, lst, env);
	signals(PROMPT);
	return ;
}
