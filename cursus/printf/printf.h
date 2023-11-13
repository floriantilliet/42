/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printf.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ftilliet <ftilliet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/13 17:12:05 by ftilliet          #+#    #+#             */
/*   Updated: 2023/11/13 18:42:26 by ftilliet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PRINTF_H
# define PRINTF_H

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