#include "graphics.h"

int	get_opposite(int trgb)
{
	unsigned char	t;
	unsigned char	r;
	unsigned char	g;
	unsigned char	b;

	t = 255 - get_t(trgb);
	r = 255 - get_r(trgb);
	g = 255 - get_g(trgb);
	b = 255 - get_b(trgb);
	return (*(int *)(unsigned char [4]){b, g, r, t});
}

int	add_shade(double distance, int trgb)
{
	unsigned char	t;
	unsigned char	r;
	unsigned char	g;
	unsigned char	b;

	t = get_t(trgb) * (1 - distance);
	r = get_r(trgb) * (1 - distance);
	g = get_g(trgb) * (1 - distance);
	b = get_b(trgb) * (1 - distance);
	return (*(int *)(unsigned char [4]){b, g, r, t});
}

