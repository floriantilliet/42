/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ftilliet <ftilliet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/06 11:22:10 by ftilliet          #+#    #+#             */
/*   Updated: 2023/11/07 15:33:07 by ftilliet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void *ft_memcpy(void *dest, const void *src, size_t n)
{
    size_t  i;

    if (!dest || !src)
        return (NULL);
    i = 0;
    while (i < n)
    {
        *(char*)(dest+i) = (char)(src+i);
        i++;
    }
    return (dest);
}