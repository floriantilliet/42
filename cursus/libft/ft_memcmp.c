/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ftilliet <ftilliet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/06 11:22:07 by ftilliet          #+#    #+#             */
/*   Updated: 2023/11/07 17:31:03 by ftilliet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int ft_memcmp(const void *s1, const void *s2, size_t n)
{
    size_t  i;

    i = 0;
    while (i < n)
    {
        if (*(char*)(s1 + i) != *(char*)(s2 + i))
			return (*(char*)(s1 + i) - *(char*)(s2 + i));
		i++;
	}
	return (0);
}