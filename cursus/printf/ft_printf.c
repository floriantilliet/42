/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ftilliet <ftilliet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/13 12:45:41 by ftilliet          #+#    #+#             */
/*   Updated: 2023/11/13 15:35:01 by ftilliet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdarg.h>

int ft_conversion(va_list args, const char format)
{   
    int count;

    if(format == 'd' || format == 'i')
        count += ft_printnbr(va_arg(args, int));
    else if(format == 'c')
        count += ft_printchar(va_arg(args, char));
    else if(format == 'x')
        count += ft_printnbrbase(va_arg(args, unsigned int), "0123456789abcdef");
    else if(format == 'X')
        count += ft_printbrbase(va_arg(args, unsigned int), "0123456789ABCDEF");
    else if(format == '%')
        count += ft_printchar('%');
    else if(format == 's')
        count += ft_printstr(va_arg(args, char*));
    else if(format == 'p')
        count += ft_printvoid(va_arg(args, void*));
    else if(format == 'u')
        count += ft_prinutnbr(va_arg(args, unsigned int));
    return (count);
}

int ft_printf(const char *format, ...)
{
        va_list args;
        int count;
        char *conv;

        va_start(args, format);
        while(*format)
        {

            if (*format == '%')
            {
                format++;
                count += ft_conversion(args, *format);
            }
            else 
                count += printchar(*format);
            format++;
        }

        va_end(args);
        return(count);
}