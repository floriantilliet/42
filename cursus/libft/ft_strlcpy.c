/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ftilliet <ftilliet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/06 11:22:25 by ftilliet          #+#    #+#             */
/*   Updated: 2023/11/07 14:53:01 by ftilliet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>

size_t	*ft_strlcpy(char *dest, char *src, size_t n)
{
	unsigned int	i;
    int res;

    res = 0;
    while (src[res] != '\0')
		res++;

	i = 0;
	while ((src[i] != '\0') && (i < n))
	{
		dest[i] = src [i];
		i++;
	}
	dest[i] = '\0';
	return (res);
}