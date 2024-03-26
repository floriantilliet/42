/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ftilliet <ftilliet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/26 15:26:56 by ftilliet          #+#    #+#             */
/*   Updated: 2024/03/26 16:08:51 by ftilliet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_env	*ft_envnew(char* content)
{
	t_env	*new;

	new = malloc(sizeof(t_env));
	if (!new)
	{
		return (NULL);
	}
	new->value = content;
	new->key = NULL;
	new->next = NULL;
	return (new);
}

t_env	*ft_envlast(t_env *lst)
{
	t_env	*current;

	if (!lst)
		return (NULL);
	current = lst;
	while (current->next)
	{
		current = current->next;
	}
	return (current);
}

void	ft_envadd_back(t_env **head, t_env *new)
{
	t_env	*last;

	if (head)
	{
		if (*head)
		{
			last = ft_envlast(*head);
			last->next = new;
		}
		else
			*head = new;
	}
}

void	ft_envadd_front(t_env **head, t_env *new)
{
	if (head)
	{
		new->next = *head;
		*head = new;
	}
}

int	ft_envsize(t_env *lst)
{
	size_t			size;
	t_env	*current;

	if (!lst)
		return (0);
	current = lst;
	size = 0;
	while (current)
	{
		size++;
		current = current->next;
	}
	return (size);
}
