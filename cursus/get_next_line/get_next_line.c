/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ftilliet <ftilliet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/26 15:00:58 by florian           #+#    #+#             */
/*   Updated: 2023/11/28 12:57:26 by ftilliet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

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
		i++;
	}
	if (str[i] == '\n')
		i++;
	j = ft_strlen(str + i);
	stash = malloc(sizeof(char) * (j + 1));
	if (!stash)
		return (NULL);
	j = 0;
	while (str[i + j])
	{
		stash[j] = str[i + j];
		j++;
	}
	stash[j] = '\0';
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
	line = malloc(sizeof(char) * (i + 2));
	if (!line)
		return (NULL);
	if (i == 0)
	{
		if (str[i] == '\n')
			return (just_new_line(line));
		else
		{
			free(line);
			return (NULL);
		}
	}
	copy_until_new_line(&line, &str, &i);
	return (line);
}

void	return_new_line(char **line, char **temp, char **stash)
{
	*line = get_new_line(*stash);
	*temp = *stash;
	*stash = clean(*stash);
}

char	*get_next_line(int fd)
{
	static char	*stash;
	char		*buffer;
	ssize_t		bytes_read;
	char		*temp;
	char		*line;

	buffer = malloc(sizeof(char) * BUFFER_SIZE + 1);
	if (!stash)
	{
		stash = malloc(sizeof(char));
		if (stash)
			stash[0] = '\0';
	}
	while (!new_line(stash))
	{
		bytes_read = read(fd, buffer, BUFFER_SIZE);
		if (bytes_read <= 0)
			break ;
		buffer[bytes_read] = '\0';
		temp = stash;
		stash = ft_strjoin(stash, buffer);
		free(temp);
	}
	return_new_line(&line, &temp, &stash);
	return (free(temp), free(buffer), line);
}

/* #include <fcntl.h>
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
		printf("%s", line);
		free(line);
	}
	close(fd);
} */