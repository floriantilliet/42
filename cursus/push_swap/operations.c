/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   operations.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ftilliet <ftilliet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/11 14:39:50 by ftilliet          #+#    #+#             */
/*   Updated: 2024/01/11 17:24:26 by ftilliet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void    swap(t_stack_node **head)
{
    t_stack_node    *tmp;

    if (*head && (*head)->next)
    {
        tmp = (*head)->next;
        (*head)->next = tmp->next;
        (*head)->prev = tmp;
        tmp->next = *head;
        tmp->prev = NULL;
        *head = tmp;
    }
}

void    push(t_stack_node **head, t_stack_node **head_b)
{
    t_stack_node    *tmp;

    if (*head)
    {
        tmp = (*head)->next;
        (*head)->next = *head_b;
        *head_b = *head;
        *head = tmp;
    }
}

void    rotate(t_stack_node **head)
{
    t_stack_node    *tmp;

    if (*head && (*head)->next)
    {
        tmp = *head;
        while (tmp->next)
            tmp = tmp->next;
        tmp->next = *head;
        *head = (*head)->next;
        tmp->next->next = NULL;
        tmp->next->prev = tmp;
    }
}