/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strupcase.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ftilliet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/08 11:09:56 by ftilliet          #+#    #+#             */
/*   Updated: 2023/09/08 11:32:45 by ftilliet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
/*
#include <stdio.h>
#include <string.h>
*/
char	*ft_strupcase(char *str)
{
	int	i;

	i = 0;
	while (str[i] != '\0')
	{
		if (str[i] >= 97 && str[i] <= 122)
				str[i] = str [i] - 32;
		i++;
	}
	return (str);
}
/*
int main(void)
{
		char	test1[20] = "Salut c Florian !";

	printf("Salut c Florian !:  %s",ft_strupcase(test1));
}
*/
