/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ftilliet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/09 15:05:29 by ftilliet          #+#    #+#             */
/*   Updated: 2023/09/09 15:40:19 by ftilliet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
/*
#include <stdio.h>
#include <string.h>
*/
int	ft_strncmp(char *s1, char *s2, unsigned int n)
{
	unsigned int	i;

	if (n == 0)
		return (0);
	i = 0;
	while (s1[i] == s2[i] && s1[i] != '\0' && s2[i] != '\0' && i < n)
		i++;
	if (i == n)
		i--;
	return (s1[i] - s2[i]);
}
/*
int main(void)
{
	char str1[] = "abcd", str2[] = "abCd", str3[] = "abcdEFG";
	
	printf("ncmp(abcd/abcdEFG) = %d\n", strncmp(str1,str3,7));
	printf("ncmp(abcd/abCd) = %d\n", strncmp(str1,str2,7));
	printf("ncmp(abcd/abCd) = %d\n", strncmp(str1,str2,2));
	printf("ft_ncmp(abcd/abcdEFG) = %d\n", ft_strncmp(str1,str3,7));
	printf("ft_ncmp(abcd/abCd) = %d\n", ft_strncmp(str1,str2,7));
	printf("ncmp(abcd/abCd) = %d\n", ft_strncmp(str1,str2,2));
}
*/