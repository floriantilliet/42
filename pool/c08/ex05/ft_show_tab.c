#include <unistd.h>
#include "ft_stock_str.h"

void	ft_putchar(char c)
{
	write(1, &c, 1);
}

void	ft_putstr(char *str)
{
	while (*str != '\0')
	{
		ft_putchar(*str);
		str++;
	}	
}

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

void    ft_show_tab(struct s_stock_str *par)
{
    int i;

    i = 0;
    
    while(par[i].str)
    {  
        ft_putstr(par[i].str);
        write(1, "\n", 1);
        ft_putnbr(par[i].size);
        write(1, "\n", 1);
        ft_putstr(par[i].copy);
        write(1, "\n", 1);
        i++;
    }
}
/*
#include <stdlib.h>

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

char	*ft_strcpy(char *dest, char *src)
{
	int	i;

	i = 0;
	while (src[i] != '\0')
	{
		dest[i] = src [i];
		i++;
	}
	dest[i] = '\0';
	return (dest);
}


struct s_stock_str *ft_strs_to_tab(int ac, char **av)
{
    t_stock_str *tab;
    int i;
    int len;

    i = 0;
    tab = malloc(sizeof(t_stock_str) * (ac + 1));
    while (i < ac)
    {   
        len = ft_strlen(av[i]);
        tab[i].size = len;
        tab[i].str = malloc(sizeof(char) * (len + 1));
        tab[i].copy = malloc(sizeof(char) * (len + 1));
        ft_strcpy(tab[i].str, av[i]);
        ft_strcpy(tab[i].copy, tab[i].str);
        i++;
    }
    tab[i].size = 0;
    tab[i].str = 0;
    tab[i].copy = 0;
    return(tab);
}

int main(int argc, char **argv)
{
    t_stock_str *tab;

    tab = ft_strs_to_tab(argc - 1, &argv[1]);
    ft_show_tab(tab);
}
*/