/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ftilliet <ftilliet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/06 11:22:25 by ftilliet          #+#    #+#             */
/*   Updated: 2023/11/06 15:15:12 by ftilliet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

char	*ft_strlcpy(char *dest, char *src, unsigned int n)
{
	unsigned int	i;
    int res;

    res = 0;
    while (src[res] != '\0')
		res++;

	i = 0;
	while ((src[i] != '\0') && (i < n))
	{
		dest[i] = src [i];
		i++;
	}
	dest[i] = '\0';
	return (res);
}