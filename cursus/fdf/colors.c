#include "graphics.h"

int ft_create_trgb(unsigned char t, unsigned char r, unsigned char g, unsigned char b)
{
    return (t << 24) | (r << 16) | (g << 8) | b;
}

unsigned char ft_get_t(int trgb)
{
    return (trgb >> 24) & 0xFF;
}

unsigned char ft_get_r(int trgb)
{
    return (trgb >> 16) & 0xFF;
}

unsigned char ft_get_g(int trgb)
{
    return (trgb >> 8) & 0xFF;
}

unsigned char ft_get_b(int trgb)
{
    return trgb & 0xFF;
}