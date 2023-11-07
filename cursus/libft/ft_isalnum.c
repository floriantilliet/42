/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isalnum.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ftilliet <ftilliet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/06 11:21:50 by ftilliet          #+#    #+#             */
/*   Updated: 2023/11/07 18:30:29 by ftilliet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	ft_isalnum(int c)
{
	if (c < 30 || (c > 57 && c < 65) || (c > 90 && c < 97) || c > 122)
	{
		return (0);
	}
	return (1);
}
