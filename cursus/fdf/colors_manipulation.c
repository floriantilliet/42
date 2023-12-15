#include "graphics.h"

int	ft_get_opposite(int trgb)
{
	unsigned char	t;
	unsigned char	r;
	unsigned char	g;
	unsigned char	b;

	t = 255 - ft_get_t(trgb);
	r = 255 - ft_get_r(trgb);
	g = 255 - ft_get_g(trgb);
	b = 255 - ft_get_b(trgb);
	return (*(int *)(unsigned char [4]){b, g, r, t});
}

int	ft_add_shade(double distance, int trgb)
{
	unsigned char	t;
	unsigned char	r;
	unsigned char	g;
	unsigned char	b;

	t = ft_get_t(trgb) * (1 - distance);
	r = ft_get_r(trgb) * (1 - distance);
	g = ft_get_g(trgb) * (1 - distance);
	b = ft_get_b(trgb) * (1 - distance);
	return (*(int *)(unsigned char [4]){b, g, r, t});
}

int get_altitude_color(double z)
{
	int color;

	if (z < 0)
		color = ft_create_trgb(0,0,0,0);
	else if (z < 10)
		color = ft_create_trgb(0,0,0,255);
	else if (z < 20)
		color = ft_create_trgb(0,0,255,0);
	else if (z < 30)
		color = ft_create_trgb(0,255,255,0);
	else if (z < 40)
		color = ft_create_trgb(0,255,0,0);
	else
		color = ft_create_trgb(0,255,0,255);
	return (color);
}

