/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ftilliet <ftilliet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/26 15:00:58 by florian           #+#    #+#             */
/*   Updated: 2023/11/27 11:57:55 by ftilliet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <unistd.h>

size_t	ft_strlen(char *str)
{
	size_t	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

size_t	ft_strlcat(char *dest, char *src, size_t dstsize)
{
	size_t	c;
	size_t	d;

	if (!dest && dstsize == 0)
		return (0);
	if (dstsize <= ft_strlen(dest))
		return (dstsize + ft_strlen(src));
	c = ft_strlen(dest);
	d = 0;
	while (src[d] && c + 1 < dstsize)
	{
		dest[c] = src[d];
		c++;
		d++;
	}
	dest[c] = '\0';
	return (ft_strlen(dest) + ft_strlen(&src[d]));
}

int	new_line(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '\n')
			return (1);
		i++;
	}
	return (0);
}

char	*clean(char *str)
{
	int		i;
	int		j;
	char	*stash;

	i = 0;
	while (str[i] != '\n' && str[i])
	{
		if (!str[i])
			return (str);
		i++;
	}
	i++;
	j = 0;
	while (str[i + j])
	{
		j++;
	}
	stash = malloc(sizeof(char) * (j));
	j = 0;
	while (str[i + j])
	{
		stash[j] = str[i + j];
		j++;
	}
	return (stash);
}

char	*get_new_line(char *str)
{
	char	*line;
	int		i;

	i = 0;
	while (str[i] != '\n' && str[i])
	{
		i++;
	}
	if (i == 0)
		return(NULL);
	line = malloc(sizeof(char) * i);
	if (!line)
		return(NULL);
	i = 0;
	while (str[i] != '\n' && str[i])
	{
		line[i] = str[i];
		i++;
	}
	line[i] = '\0';
	return (line);
}

char	*get_next_line(int fd)
{
	static char	*stash;
	char		*line;
	char		*buffer;
	ssize_t		bytes_read;

	buffer = malloc(sizeof(char) * 5);
	if (!stash)
		stash = malloc(sizeof(char) * 50);
	while (!new_line(stash))
	{
		bytes_read = read(fd, buffer, 5);
		if (bytes_read <= 0)
			break;
		buffer[bytes_read] = '\0';
		ft_strlcat(stash, buffer, ft_strlen(stash) + ft_strlen(buffer) + 1);
	}
	line = get_new_line(stash);
	stash = clean(stash);
	return (line);
}

#include <fcntl.h>
#include <stdio.h>

int	main(void)
{
	int fd;
	char *line;

	fd = open("test/simple", O_RDONLY);
	while (1)
	{
		line = get_next_line(fd);
		if (line == NULL)
			break ;
		printf("%s\n", line);
	}
}