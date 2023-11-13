/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printchars.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ftilliet <ftilliet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/13 15:22:01 by ftilliet          #+#    #+#             */
/*   Updated: 2023/11/13 15:37:33 by ftilliet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int ft_printchar(int c)
{
    write(1, &c, 1);
    return (1);
}

int ft_printstr(char* str)
{
    int count;

    while (*str != '\0')
	{
		count += ft_printchar(*str);
		str++;
	}
    return (count);
}

/* #include <stdio.h>

int main() {
    int var = 42;
    int *ptr = &var;

    printf("L'adresse de var est %p\n", (void *)ptr);
    return 0;
}
 */