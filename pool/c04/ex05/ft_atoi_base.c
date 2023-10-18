/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi_base.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ftilliet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/11 10:38:37 by ftilliet          #+#    #+#             */
/*   Updated: 2023/09/13 16:38:32 by ftilliet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include<stdio.h>


int	ft_check_double(char *str)
{
	int	i;
	int	j;

	i = 0;
	while (str[i] != '\0')
	{
		if (str[i] == '+' || str[i] == '-' || str[i] == '%')
			return (0);
		else if (str[i] == '/' || str[i] == '*' || str[i] == '=')
			return (0);
		else if (str[i] == ',' || str[i] == '.' || str[i] < 33 || str[i] > 126)
			return (0);
		j = i + 1;
		while (str[j] != '\0')
		{
			if (str[j] == str[i])
				return (0);
			j++;
		}
	i++;
	}
	return (1);
}

int	ft_strlen(char *str)
{
	int	len;

	len = 0;
	while (*str != '\0')
	{
		str++;
		len++;
	}
	return (len);
}

int	ft_putnbr_base(int nbr, char *base)
{
	long int		nb;
	char			temp;
	int				len_base;

	len_base = ft_strlen(base);
	nb = nbr;
	if (len_base < 2)
		return (0);
	if (!ft_check_double(base))
		return (0);	
	if (nbr > 9)
		ft_putnbr_base(nbr / len_base, base);
	temp = (char)base[(nbr % len_base)];
	return (temp);
}

int	ft_atoi_base(char *str, char *base)
{
	int	signe;
	int	result;

	signe = 1;
	result = 0;
	while ((*str <= 13 && *str >= 9) || *str == ' ')
		str++;
	while (*str == '+' || *str == '-')
	{
		if (*str == '-')
	signe *= -1;
		str++;
	}
	while (*str >= '0' && *str <= '9')
	{
		result = result * 10 + *str - '0';
		str++;
	}
	result = ft_putnbr_base(result, base);
	return (result * signe);
}


int	main(void)
{
	printf("42:%d\n", ft_atoi_base("2a", "0123456789abcdef"));
	printf("-42:%d\n", ft_atoi_base("   --------+-2a", "0123456789abcdef"));
	printf("42:%d\n", ft_atoi_base("   -+-2a", "0123456789abcdef"));
	printf("0:%d\n", ft_atoi_base("   --------+- 2a", "0123456789abcdef"));
	printf("0:%d\n", ft_atoi_base("   --------+-z", "0123456789abcdef"));
	printf("0:%d\n", ft_atoi_base("   --------+-2a", ""));
	printf("0:%d\n", ft_atoi_base("   --------+-2a", "0"));
	printf("0:%d\n", ft_atoi_base("   --------+-2a", "+-0"));
	printf("0:%d\n", ft_atoi_base("   --------+-2a", "\t01"));
}
