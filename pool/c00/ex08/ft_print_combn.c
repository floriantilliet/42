#include <stdio.h>
#include <unistd.h>

void	ft_putnbr(int nb)
{
	long int		nbr;
	char			temp;

	nbr = nb;
	if (nbr < 0)
	{
		nbr *= -1;
		write(1, "-", 1);
	}
	if (nbr > 9)
		ft_putnbr(nbr / 10);
	temp = '0' + (char)(nbr % 10);
	write(1, &temp, 1);
}

int	ft_iterative_power(int nb, int power)
{
	int	result;

	if (power < 0)
		return (0);
	if (power == 0)
		return (1);
	result = nb;
	while (power != 1)
	{
		result *= (nb);
		power--;
	}
	return (result);
}

int is_valid(int nbr, int n)
{
	int i;
	int temp;

	i = 1;
	temp = 10;
	while  (i < nbr)
	{
		if (nbr / i % 10 < temp)
		{
			temp = nbr / i % 10;
			i *= 10;
		}
		else
			return (0);
	}
	if ((nbr / ft_iterative_power(10, n - 1) == (9 - n + 1)) && (nbr % 10 == 9))
		{
			return (-1);
		}
	return (1);
}

void	ft_print_combn(int n)
{	
	int	nbr;

	nbr = ft_iterative_power(10, n-2);
	while (nbr < ft_iterative_power(10, n))
	{	
		if (is_valid(nbr, n) == -1)
		{
			ft_putnbr(nbr);
			break ;
		}
		if (is_valid(nbr, n) == 1)
		{
			if (nbr < ft_iterative_power (10, n - 1))
				write(1, "0", 1);
			ft_putnbr(nbr);
			write(1, ", ", 2);
		}
		nbr++;
	}
	
}

int main(int argc, char **argv)
{
	argc++;
	/* argv++; */
	ft_print_combn(*argv[1] - '0');
	/* printf("%d\n", 123456789/ft_iterative_power(10, 8));
	printf("%d\n", 23456789/ft_iterative_power(10, 7));
	printf("%d\n", 789/ft_iterative_power(10, 2));
	printf("%d\n", 2345789%10);
	printf("%d\n", ft_iterative_power(10, 8));
	printf("%d\n", 123456789); */
}