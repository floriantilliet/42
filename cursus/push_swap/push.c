/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: florian <florian@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/22 13:37:47 by florian           #+#    #+#             */
/*   Updated: 2024/01/22 16:39:51 by florian          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void push(t_stack_node **head_start, t_stack_node **head_end)
{
    t_stack_node *tmp;

    if (*head_start)
    {
        tmp = *head_start; // Sauvegarder le nœud à déplacer
        *head_start = (*head_start)->next; // Mettre à jour le sommet de head_start
        tmp->next = *head_end; // Ajouter l'élément sauvegardé au sommet de head_end
        *head_end = tmp; // Mettre à jour le sommet de head_end
    }
}


void	pa(t_stack_node **head_a, t_stack_node **head_b)
{
	push(head_b, head_a);
	ft_putendl_fd("pa", 1);
}

void	pb(t_stack_node **head_a, t_stack_node **head_b)
{
	push(head_a, head_b);
	ft_putendl_fd("pb", 1);
}
