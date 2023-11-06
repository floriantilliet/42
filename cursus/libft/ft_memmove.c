/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ftilliet <ftilliet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/06 11:22:12 by ftilliet          #+#    #+#             */
/*   Updated: 2023/11/06 17:40:59 by ftilliet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>

void *ft_memmove(void *dest, const void *src, size_t n)
{
    size_t  i;

    if (!dest || !src)
        return (NULL);
    if (dest < src)
    {
        i = 0;
        while (i < n)
        {
            *(char*)(dest+i) = (char)(src+i);
            i++;
        }
    }
    else
    {
        i = n;
        while (i < 0)
        {
            *(char*)(dest+i) = (char)(src+i);
            i--;
        }
    }
    return (dest);
}