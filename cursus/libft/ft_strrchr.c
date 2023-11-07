/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ftilliet <ftilliet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/06 11:22:35 by ftilliet          #+#    #+#             */
/*   Updated: 2023/11/07 18:31:30 by ftilliet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *s, int c)
{
	int i;
	char *ptr;

	ptr = NULL;

	i = 0;
	while (s[i] != '\0')
	{
		if (s[i] == c)
		{
			ptr = (char *)&s[i];
		}
		i++;
	}
	return (ptr);
}