/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstlast.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ftilliet <ftilliet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/08 12:19:27 by ftilliet          #+#    #+#             */
/*   Updated: 2023/11/08 14:58:58 by ftilliet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list *ft_lstlast(t_list *lst)
{
    t_list *current;

    if (!lst)
        return (NULL);
    current = lst;
    while(current->next)
    {
        current = current->next;
    }
    return (current);
}
