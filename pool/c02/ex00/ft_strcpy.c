/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ftilliet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/07 18:46:20 by ftilliet          #+#    #+#             */
/*   Updated: 2023/09/08 09:35:54 by ftilliet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*#include <stdio.h>
#include <string.h>
*/

char	*ft_strcpy(char *dest, char *src)
{
	int	i;

	i = 0;
	while (src[i] != '\0')
	{
		dest[i] = src [i];
		i++;
	}
	dest[i] = '\0';
	return (dest);
}

/*
 * int	main(void)
{
	char	orig [20] = "C programming";
	char	dest1 [20];
	char	dest2 [20];
	
	strcpy(dest1, orig);
	ft_strcpy(dest2, orig);

	printf("copy, %s  \n", dest1);
	printf("ftcopy, %s  \n", dest2);
}
*/
