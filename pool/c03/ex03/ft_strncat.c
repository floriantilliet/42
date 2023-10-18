/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ftilliet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/10 16:03:30 by ftilliet          #+#    #+#             */
/*   Updated: 2023/09/10 19:32:12 by ftilliet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
/*
#include <stdio.h>
#include <string.h>
*/
char	*ft_strncat(char *dest, char *src, unsigned int nb)
{
	int				i;
	int				j;
	unsigned int	k;

	i = 0;
	j = 0;
	k = 0;
	while (dest[j] != '\0')
		j++;
	while (src[i] != '\0' && k < nb)
	{
		dest[j] = src[i];
		i++;
		j++;
		k++;
	}
	dest[j] = '\0';
	return (dest);
}
/*
int main(void) 
{
	char destination1[50] = "salut c ";
	char destination2[50] = "salut c ";
	char source[] = "florian";
	
	strncat(destination1, source,3);
	ft_strncat(destination2, source,3);
	
	printf("strncat : %s\n", destination1);
	printf("ft_strncat : %s\n", destination2);

}
*/
