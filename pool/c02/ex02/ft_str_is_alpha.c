/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_str_is_alpha.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ftilliet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/08 09:34:16 by ftilliet          #+#    #+#             */
/*   Updated: 2023/09/09 17:59:51 by ftilliet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
/*
#include <stdio.h>
#include <string.h>
*/
int	ft_str_is_alpha(char *str)
{
	int		i;
	int		o;
	char	c;

	i = 0;
	o = 1;
	while (str[i] != '\0')
	{
		c = str[i];
		if (c < 65 || (c > 90 && c < 97) || c > 122)
		{
			o = 0;
		}
		i++;
	}
	return (o);
}
/*
int	main(void)
{
	char	test1[20] = "Salut c Florian";
	char	test2[20] = "SalutcFlorian";
	char	test3[20] = "";

	printf("Salut c Florian %d",ft_str_is_alpha(test1));
	printf("\n");
	printf("SalutcFlorian %d",ft_str_is_alpha(test2));
	printf("\n");
        printf("%d",ft_str_is_alpha(test3));

}
*/
