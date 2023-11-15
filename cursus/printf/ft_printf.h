/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ftilliet <ftilliet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/13 17:12:05 by ftilliet          #+#    #+#             */
/*   Updated: 2023/11/15 14:57:03 by ftilliet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <stdlib.h>
# include <unistd.h>
#include <stdarg.h>

int ft_conversion(va_list args, const char format);

int ft_printf(const char *format, ...);

int ft_printchar(int c);

int ft_printstr(char* str);

int ft_printptr(unsigned long int ptr);

int	ft_printnbr(int nb);

int	ft_printunbr(unsigned int nb);

int	ft_printhex(unsigned long int nbr, char* base);

#endif