/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ftilliet <ftilliet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/06 11:22:32 by ftilliet          #+#    #+#             */
/*   Updated: 2023/11/07 17:55:52 by ftilliet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *big, const char *little, size_t len)
{
	size_t			i;
	int			j;
	int			l;
	char		*ptr;

	ptr = NULL;
	l = 0;
	while (little[l] != '\0')
		l++;
	i = 0;
	while (big[i] != '\0' && i < len)
	{
		if (big[i] == little[0])
		{
			j = 0;
			while (big[i + j] == little[j] && j < l)
				j++;
			if (j == l)
				ptr = (char*)&big[i];
			return (ptr);
		}
		i++;
	}
	return (NULL);
}