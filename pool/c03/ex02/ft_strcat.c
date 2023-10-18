/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcat.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ftilliet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/10 14:46:12 by ftilliet          #+#    #+#             */
/*   Updated: 2023/09/10 15:22:45 by ftilliet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
/*
#include <stdio.h>
#include <string.h>
*/
char	*ft_strcat(char *dest, char *src)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (dest[j] != '\0')
		j++;
	while (src[i] != '\0')
	{
		dest[j] = src[i];
		i++;
		j++;
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
    
    strcat(destination1, source);
    ft_strcat(destination2, source);
    
    printf("strcat : %s\n", destination1);
    printf("ft_strcat : %s\n", destination2);

}
*/
