/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ftilliet <ftilliet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/06 11:22:32 by ftilliet          #+#    #+#             */
/*   Updated: 2023/11/09 12:47:33 by ftilliet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *big, const char *little, size_t len)
{
	size_t	i;
	int		j;
	int		l;

	if (!little[0])
		return ((char *)big);
	l = 0;
	while (little[l] != '\0')
		l++;
	if (len <= 1)
		len++;
	i = 0;
	while (big[i] != '\0' && i < len - 1)
	{
		if (big[i] == little[0])
		{
			j = 0;
			while (big[i + j] == little[j] && j < l)
				j++;
			if (j == l)
				return ((char *)&big[i]);
		}
		i++;
	}
	return (NULL);
}
/*
#include <stdio.h>

int	main(void)
{
	char haystack[30] = "aaabcabcd";
	printf("%s\n",ft_strnstr(haystack, "cd", 8));

} */