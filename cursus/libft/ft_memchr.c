/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ftilliet <ftilliet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/06 11:22:05 by ftilliet          #+#    #+#             */
/*   Updated: 2023/11/08 10:55:39 by ftilliet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	size_t	i;
	void	*ptr;

	if (!s)
		return (NULL);
	i = 0;
	ptr = NULL;
	while (i < n)
	{
		if (*(char *)(s + i) == c)
			ptr = (void *)(s + i);
		return (ptr);
		i++;
	}
	return (ptr);
}
