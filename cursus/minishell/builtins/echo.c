/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ochetrit <ochetrit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/27 16:29:15 by ochetrit          #+#    #+#             */
/*   Updated: 2024/07/27 14:16:59 by ochetrit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

t_token	*print_word_echo(t_token *lst)
{
	int	i;

	i = 0;
	while (lst && lst->value[i])
	{
		write(STDOUT_FILENO, lst->value + i, 1);
		if (lst->value[i] == '\\' && lst->value[i + 1] == '\\')
			i++;
		if (lst->value[i])
			i++;
	}
	if (lst)
		return (lst->next);
	return (lst);
}

t_token	*skip_redirect(t_token *lst, int flag[2])
{
	if (lst)
		lst = lst->next;
	if (lst)
		lst = lst->next;
	if (flag)
		flag[0]--;
	return (lst);
}

int	ft_echo(t_token *lst, t_env **env)
{
	int		flag[2];

	if (lst && lst->type == CMD)
		lst = lst->next;
	if (!lst)
		return (write(STDOUT_FILENO, "\n", 1));
	flag[1] = is_flag(lst->value);
	flag[0] = 0;
	while (lst && skip_flag(lst->value))
		lst = lst->next;
	while (lst && lst->type != PIPE)
	{
		if (lst->type > PIPE)
			lst = skip_redirect(lst, flag);
		else
		{
			lst = print_word_echo(lst);
			flag[0] = 1000;
		}
		if (lst && lst->type == ARG && flag[0] > -1)
			write(STDOUT_FILENO, " ", 1);
	}
	if (!flag[1])
		ft_printf("\n", STDOUT_FILENO);
	return (exit_status(0, *env), TRUE);
}
