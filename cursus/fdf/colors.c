#include "graphics.h"

int	ft_create_trgb(unsigned char t, unsigned char r, unsigned char g, unsigned char b)
{
	return (*(int *)(unsigned char [4]){b, g, r, t});
}

unsigned char	ft_get_t(int trgb)
{
	return (((unsigned char *)&trgb)[3]);
}

unsigned char	ft_get_r(int trgb)
{
	return (((unsigned char *)&trgb)[2]);
}

unsigned char	ft_get_g(int trgb)
{
	return (((unsigned char *)&trgb)[1]);
}

unsigned char	ft_get_b(int trgb)
{
	return (((unsigned char *)&trgb)[0]);
}

