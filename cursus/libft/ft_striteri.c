/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_striteri.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ftilliet <ftilliet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/07 09:28:35 by ftilliet          #+#    #+#             */
/*   Updated: 2023/11/07 15:31:27 by ftilliet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void ft_striteri(char *s, void (*f)(unsigned int, char*))
{
    size_t  i;

    while (s[i])
    {
        f(i, s);
    }
}

void caca(unsigned int i , char* s)
{
    s[i] = '!';
}

#include <stdio.h>

int main(int argc, char** argv)
{
    argc++;
    printf("%s\n%s\n", argv[1], ft_striteri(argv[1], caca));
}