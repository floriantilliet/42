/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ftilliet <ftilliet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/07 09:28:57 by ftilliet          #+#    #+#             */
/*   Updated: 2023/11/07 18:31:24 by ftilliet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmapi(char const *s, void (*f)(unsigned int, char *))
{
	size_t	i;
	char	*res;

	res = ft_strdup(s);
	i = 0;
	while (res[i] && f)
	{
		f(i, &res[i]);
		i++;
	}
	return (res);
}

/*
void	test(unsigned int i , char* s)
{
	*s = '!';
}

#include <stdio.h>

int	main(int argc, char** argv)
{
	argc++;
	char *res;

	printf("%s\n", argv[1]);
	res = ft_strmapi(argv[1], test);
	printf("%s\n", res);
} */