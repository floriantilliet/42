/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ftilliet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/09 14:47:23 by ftilliet          #+#    #+#             */
/*   Updated: 2023/09/09 15:01:39 by ftilliet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
/*
#include <stdio.h>
#include <string.h>
*/
int	ft_strcmp(char *s1, char *s2)
{
	int	i;

	i = 0;
	while (s1[i] != '\0' && s2[i] != '\0' && s1[i] == s2[i])
		i++;
	return (s1[i] - s2[i]);
}
/*
int main(void)
{
	char str1[] = "abcd", str2[] = "abCd", str3[] = "abcd";
	
	printf("cmp(abcd/abcd) = %d\n", strcmp(str1,str3));
	printf("cmp(abcd/abCd) = %d\n", strcmp(str1,str2));
	printf("ft_cmp(abcd/abcd) = %d\n", ft_strcmp(str1,str3));
	printf("ft_cmp(abcd/abCd) = %d\n", ft_strcmp(str1,str2));
}
*/