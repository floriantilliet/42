/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_back.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ftilliet <ftilliet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/08 12:19:17 by ftilliet          #+#    #+#             */
/*   Updated: 2023/11/08 15:44:04 by ftilliet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void    ft_lstadd_back(t_list **head, t_list *new)
{
    t_list *last;

    if (head)
    {
        if (*head)
        { 
        last = ft_lstlast(*head);
        last->next = new;
        }
        else
            *head = new;
    }
}