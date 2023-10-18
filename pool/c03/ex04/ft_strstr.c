/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strstr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ftilliet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/10 19:43:54 by ftilliet          #+#    #+#             */
/*   Updated: 2023/09/11 15:23:05 by ftilliet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <string.h>

char	*ft_strstr(char *str, char *to_find)
{
	int			i;
	int			j;
	int			l;
	char		*ptr;

	ptr = NULL;
	l = 0;
	while (to_find[l] != '\0')
		l++;
	i = 0;
	while (str[i] != '\0')
	{
		if (str[i] == to_find[0])
		{
			j = 0;
			while (str[i + j] == to_find[j] && j < l)
				j++;
			if (j == l)
				ptr = &str[i];
			return (ptr);
		}
		i++;
	}
	return (NULL);
}
/*
int main(void) 
{
	char chain[50] = "salut c florian";
	char subchain[50] = "flo";	
	
	printf("strstr : %s\n", strstr(chain, subchain));
	printf("ft_strstr : %s\n", ft_strstr(chain, subchain));
}
*/
