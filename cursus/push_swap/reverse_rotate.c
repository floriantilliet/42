/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reverse_rotate.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: florian <florian@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/22 13:39:55 by florian           #+#    #+#             */
/*   Updated: 2024/01/22 15:42:35 by florian          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void reverse_rotate(t_stack_node **head)
{
    t_stack_node *last;
    t_stack_node *before_last;

    if (*head && (*head)->next)
    {
        last = *head;
        before_last = NULL;

        // Trouver le dernier et l'avant-dernier nœud
        while (last->next)
        {
            before_last = last;
            last = last->next;
        }

        // Mettre à jour les liens pour la rotation
        if (before_last)
            before_last->next = NULL; // Détacher l'avant-dernier du dernier
        last->next = *head; // Ajouter le dernier au début
        *head = last; // Mettre à jour la tête de la liste
    }
}


void rra(t_stack_node **head)
{
    reverse_rotate(head);
    ft_putendl_fd("rra", 1);
}

void rrb(t_stack_node **head)
{
    reverse_rotate(head);
    ft_putendl_fd("rrb", 1);
}

void rrr(t_stack_node **head, t_stack_node **head_b)
{
    reverse_rotate(head);
    reverse_rotate(head_b);
    ft_putendl_fd("rrr", 1);
}