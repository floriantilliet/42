/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ftilliet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/07 20:28:44 by ftilliet          #+#    #+#             */
/*   Updated: 2023/09/09 16:33:13 by ftilliet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
#include <stdio.h>
#include <string.h>
*/
char	*ft_strncpy(char *dest, char *src, unsigned int n)
{
	unsigned int	i;

	i = 0;
	while ((src[i] != '\0') && (i < n))
	{
		dest[i] = src [i];
		i++;
	}
	dest[i] = '\0';
	return (dest);
}
/*
int	main(void)
{
	char	orig [20] = "salut c florian";
	char	dest1 [20];
	char	dest2 [20];
	int size = 4;
	
	strncpy(dest1, orig, size);
	ft_strncpy(dest2, orig, size);

	printf("copy, %s  \n", dest1);
	printf("ftcopy, %s  \n", dest2);
}
*/
