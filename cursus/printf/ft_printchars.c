/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printchars.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ftilliet <ftilliet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/13 15:22:01 by ftilliet          #+#    #+#             */
/*   Updated: 2023/11/15 16:47:55 by ftilliet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_printchar(int c)
{
	write(1, &c, 1);
	return (1);
}

int	ft_printstr(char *str)
{
	int	count;

	count = 0;
	if (!str)
	{
		count += ft_printstr("(null)");
		return (count);
	}
	while (*str != '\0')
	{
		count += ft_printchar(*str);
		str++;
	}
	return (count);
}

int	ft_printptr(unsigned long int ptr)
{
	int	count;

	count = 0;
	if (ptr == 0)
	{
		count += ft_printstr("(nil)");
	}
	else
	{
		count += ft_printstr("0x");
		count += ft_printhex(ptr, "0123456789abcdef");
	}
	return (count);
}

/* #include <stdio.h>

int	main(void) {
	int var = 42;
	int *ptr = &var;

	printf("L'adresse de var est %p\n", (void *)ptr);
	return (0);
}
 */