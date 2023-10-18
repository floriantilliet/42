/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ftilliet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/10 21:06:14 by ftilliet          #+#    #+#             */
/*   Updated: 2023/09/11 09:51:50 by ftilliet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
/*
#include <stdio.h>
#include <string.h>
*/
unsigned int	ft_strlcat(char *dest, char *src, unsigned int size)
{
	unsigned int	i;
	unsigned int	j;
	unsigned int	res;

	i = 0;
	j = 0;
	res = 0;
	while (dest[i] != '\0')
		i++;
	while (src[res] != '\0')
		res++;
	if (size <= i)
		res += size;
	else
		res += i;
	while (src[j] != '\0' && (i + 1) < size)
	{
		dest[i] = src[j];
		i++;
		j++;
	}
	dest[i] = '\0';
	return (res);
}	
/*
int main()
{
    char dest1[20] = "salut c ";
    char dest2[20] = "salut c ";

    char src[] = "florian";

    unsigned int result1 = strlcat(dest1, src, 8);
    unsigned int result2 = ft_strlcat(dest2, src, 8);

    printf("Concatenated string: %s\n", dest1);
    printf("Total length after concatenation: %u\n", result1);

    printf("Concatenated string: %s\n", dest2);
    printf("Total length after concatenation: %u\n", result2);

}
*/
