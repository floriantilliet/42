/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ochetrit <ochetrit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/06 12:14:12 by ochetrit          #+#    #+#             */
/*   Updated: 2024/07/18 11:24:57 by ochetrit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	free_node(t_env *node)
{
	free(node->key);
	if (node->value)
		free(node->value);
	free(node);
}

void	remove_node(t_env **env, t_env *node)
{
	t_env	*lst1;
	t_env	*lst2;

	lst2 = *env;
	while (lst2 && lst2 != node)
	{
		lst1 = lst2;
		lst2 = lst2->next;
	}
	if (lst2 == *env)
		*env = lst2 ->next;
	else if (!lst2->next)
		lst1->next = NULL;
	else
		lst1->next = lst2->next;
	free_node(lst2);
	return ;
}

void	ft_unset(t_token *token, t_env **env)
{
	t_token		*lst;
	t_env		*l_env;

	lst = token;
	if (lst && lst->type == CMD)
		lst = lst->next;
	while (lst && lst->type == ARG)
	{
		l_env = *env;
		while (l_env)
		{
			if (!ft_strcmp(l_env->key, lst->value))
			{
				remove_node(env, l_env);
				break ;
			}
			l_env = l_env->next;
		}
		lst = lst->next;
	}
	exit_status(0, *env);
}
