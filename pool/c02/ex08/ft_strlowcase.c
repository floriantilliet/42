/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlowcase.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ftilliet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/08 11:09:56 by ftilliet          #+#    #+#             */
/*   Updated: 2023/09/08 11:36:07 by ftilliet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
/*
#include <stdio.h>
#include <string.h>
*/
char	*ft_strlowcase(char *str)
{
	int	i;

	i = 0;
	while (str[i] != '\0')
	{
		if (str[i] >= 65 && str[i] <= 90)
				str[i] = str [i] + 32;
		i++;
	}
	return (str);
}
/*
int main(void)
{
		char	test1[20] = "SALUT C FLORIAN !";

	printf("SALUT C FLORIAN !:  %s",ft_strlowcase(test1));
}
*/
