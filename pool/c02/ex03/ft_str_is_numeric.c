/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_str_is_numeric.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ftilliet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/08 10:00:20 by ftilliet          #+#    #+#             */
/*   Updated: 2023/09/08 10:32:29 by ftilliet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
/*
#include <stdio.h>
#include <string.h>
*/
int	ft_str_is_numeric(char *str)
{
	int	i;

	i = 0;
	while (str[i] != '\0')
	{
		if (!(str[i] >= 48 && str[i] <= 57))
			return (0);
		i++;
	}
	return (1);
}
/*
int	main(void)
{
	char	test1[20] = "0123456789";
	char	test2[20] = "Salut c Florian";
	char	test3[20] = "";
	
	printf("0123456789  %d",ft_str_is_numeric(test1));
	printf("\n");
	printf("Salut c Florian %d",ft_str_is_numeric(test2));
	printf("\n");
        printf("%d",ft_str_is_numeric(test3));
}
*/
