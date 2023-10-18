/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_str_is_printable.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ftilliet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/08 10:35:28 by ftilliet          #+#    #+#             */
/*   Updated: 2023/09/08 11:08:32 by ftilliet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
/*
#include <stdio.h>
#include <string.h>
*/
int	ft_str_is_printable(char *str)
{
	int	i;

	i = 0;
	while (str[i] != '\0')
	{
		if (!(str[i] >= 32 && str[i] <= 126))
			return (0);
		i++;
	}
	return (1);
}
/*
int	main(void)
{
	char	test1[20] = "Salut c Florian";
	char	test2[20] = "Salutc\nFlorian";
	char	test3[20] = "";

	printf("Salut c Florian effrite le caca %d",ft_str_is_printable(test1));
	printf("\n");
	printf("Salutc\nFlorian %d",ft_str_is_printable(test2));
	printf("\n");
        printf("%d",ft_str_is_printable(test3));

}
*/
