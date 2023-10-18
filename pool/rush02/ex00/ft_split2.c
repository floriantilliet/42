#include "ft.h"

int	is_sep(char c, char *charset)
{
	int	j;

	j = 0;
	while (charset[j])
	{
		if (c == charset[j])
			return (1);
		j++;
	}
	if (c == '\0')
		return (1);
	return (0);
}

int	write_dic_word(char *dest, char *from, char *charset)
{
	int	i;
	int j;

	i = 0;
	j=0;
	while (is_sep(from[i], charset) == 0)
	{
		dest[i] = from[i];
		i++;
		j++;
	}
	dest[i] = '\0';
	return(j+1);
}

int	skip_spaces(char *str)
{	
	int i;
	i =0;
	
	while(*str == ' ')
	{
		str++;
		i++;
	}
	return (i);
}