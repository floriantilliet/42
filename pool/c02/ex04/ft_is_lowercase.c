/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_is_lowercase.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ftilliet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/08 09:34:16 by ftilliet          #+#    #+#             */
/*   Updated: 2023/09/09 17:02:59 by ftilliet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
/*
#include <stdio.h>
#include <string.h>
*/
int	ft_str_is_lowercase(char *str)
{
	int	i;

	i = 0;
	while (str[i] != '\0')
	{
		if (!(str[i] >= 97 && str[i] <= 122))
			return (0);
		i++;
	}
	return (1);
}
/*
int	main(void)
{
	char	test1[20] = "salutcflorian";
	char	test2[20] = "SalutcFlorian";
	char	test3[20] = "";

	printf("salutcflorian %d",ft_str_is_lowercase(test1));
	printf("\n");
	printf("SalutcFlorian %d",ft_str_is_lowercase(test2));
	printf("\n");
        printf("%d",ft_str_is_lowercase(test3));

}
*/
