/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcapitalize.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ftilliet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/08 11:40:49 by ftilliet          #+#    #+#             */
/*   Updated: 2023/09/09 18:35:15 by ftilliet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
/*
#include <stdio.h>
#include <string.h>
*/
char	*ft_strcapitalize(char *str)
{
	int		i;
	int		s;
	char	c;

	i = 0;
	s = 1;
	while (str[i] != '\0')
	{
		c = str[i];
		if (s == 1 && c >= 'a' && c <= 'z')
			str[i] -= 32;
		else if (s == 0 && c >= 'A' && c <= 'Z')
			str[i] += 32;
		if (c < '0' || (c > '9' && c < 'A'))
			s = 1;
		else if ((c > 'Z' && c < 'a') || c > 122)
			s = 1;
		else
			s = 0;
		i++;
	}
	return (str);
}
