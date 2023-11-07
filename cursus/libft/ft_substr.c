/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ftilliet <ftilliet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/07 09:29:01 by ftilliet          #+#    #+#             */
/*   Updated: 2023/11/07 15:31:56 by ftilliet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int get_malloc(char const *s, unsigned int start, size_t len)
{
    while (s[start] != '\0' || start < len)
    {
        start++;
    }
    return(start);
}

char *ft_substr(char const *s, unsigned int start, size_t len)
{
    char	*res;
    size_t  i;
    
    res = malloc(sizeof(char) * get_malloc(s, start, len) + 1);
    i = 0;
    while (s[start] != '\0' && i < len)
    {
        res[i] = s[start];
        i++;
        start++;
    }
    res[i] = '\0';
    return(res);
}