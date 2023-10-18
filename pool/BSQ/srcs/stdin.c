/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stdin.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: udumas <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/27 22:43:04 by udumas            #+#    #+#             */
/*   Updated: 2023/09/27 22:43:06 by udumas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_libr.h"

void	clean_str(char *str)
{
	int	i;

	i = 0;
	while (i < TEST)
	{
		str[i] = 0;
		i++;
	}
}

char	*ft_stdin(void)
{
	char	*buffer;
	int		size;
	int		i;

	i = 0;
	buffer = (char *)malloc(sizeof(char) * TEST + 1);
	clean_str(buffer);
	size = TEST;
	while (size == TEST)
	{
		size = read(0, buffer, TEST);
		i = size;
	}
	if (i == 0)
	{
		free(buffer);
		return (NULL);
	}
	buffer[i] = '\0';
	return (buffer);
}
