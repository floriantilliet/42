/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ftilliet <ftilliet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/13 12:45:41 by ftilliet          #+#    #+#             */
/*   Updated: 2023/11/28 15:06:51 by ftilliet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_conversion(va_list args, const char format)
{
	int	count;

	count = 0;
	if (format == 'd' || format == 'i')
		count += ft_printnbr(va_arg(args, int));
	else if (format == 'c')
		count += ft_printchar(va_arg(args, int));
	else if (format == 'x')
		count += ft_printhex(va_arg(args, unsigned int), "0123456789abcdef");
	else if (format == 'X')
		count += ft_printhex(va_arg(args, unsigned int), "0123456789ABCDEF");
	else if (format == '%')
		count += ft_printchar('%');
	else if (format == 's')
		count += ft_printstr(va_arg(args, char *));
	else if (format == 'p')
		count += ft_printptr(va_arg(args, unsigned long int));
	else if (format == 'u')
		count += ft_printunbr(va_arg(args, unsigned int));
	return (count);
}

int	ft_printf(const char *format, ...)
{
	va_list	args;
	int		count;

	count = 0;
	va_start(args, format);
	if (!format)
		return (-1);
	while (*format)
	{
		if (*format == '%')
		{
			format++;
			while ((*format <= 13 && *format >= 9) || *format == ' ')
				count += ft_printchar(*format++);
			if (*format == '\0')
				return (-1);
			count += ft_conversion(args, *format);
		}
		else
			count += ft_printchar(*format);
		format++;
	}
	va_end(args);
	return (count);
}

/* #include <stdio.h>

int	main(void)
{
	int c = 0;
	int var = 42;
	int *ptr = &var;
	int d = 1245514;
	int i = 1432553;
	unsigned int u = 3147483647;
	unsigned int x = 42;

	c = ft_printf("%c%%%s %p %p %d % d %i %u %x %X %%", '?', "salut c florian",
			ptr, NULL, d, i, u, x, x);
	printf("\n");
	printf("%d", c);
	printf("\n");
	printf("\n");
	c = printf("%c%%%s %p %p %d % d %i %u %x %X %%", '?', "salut c florian", ptr,
			NULL, d, i, u, x, x);
	printf("\n");
	printf("%d", c);

	int c = 0;
	int d = 123;
	c = ft_printf("%d", d);
	printf("\n");
	printf("%d", c);
	printf("\n");

	return (0);
} */