/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_is_uppercase.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ftilliet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/08 09:34:16 by ftilliet          #+#    #+#             */
/*   Updated: 2023/09/09 17:05:21 by ftilliet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
/*
#include <stdio.h>
#include <string.h>
*/
int	ft_str_is_uppercase(char *str)
{
	int	i;

	i = 0;
	while (str[i] != '\0')
	{
		if (!(str[i] >= 65 && str[i] <= 90))
			return (0);
		i++;
	}
	return (1);
}
/*
int	main(void)
{
	char	test1[20] = "SALUTCFLORIAN";
	char	test2[20] = "SalutcFlorian";
	char	test3[20] = "";

	printf("SALUTCFLORIAN %d",ft_str_is_uppercase(test1));
	printf("\n");
	printf("SalutcFlorian %d",ft_str_is_uppercase(test2));
	printf("\n");
        printf("%d",ft_str_is_uppercase(test3));

}
*/
