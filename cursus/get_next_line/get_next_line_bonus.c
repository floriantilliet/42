/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ftilliet <ftilliet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/28 13:09:10 by ftilliet          #+#    #+#             */
/*   Updated: 2023/12/05 14:05:56 by ftilliet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

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
	if (*line == NULL)
	{
		free(*stash);
		*stash = NULL;
	}
}

char	*get_next_line(int fd)
{
	static char	*stash[FD_MAX];
	char		*buffer;
	ssize_t		bytes_read;
	char		*temp;
	char		*line;

	buffer = malloc(sizeof(char) * BUFFER_SIZE + 1);
	if (!stash[fd])
	{
		stash[fd] = malloc(sizeof(char));
		if (stash[fd])
			stash[fd][0] = '\0';
	}
	while (!new_line(stash[fd]))
	{
		bytes_read = read(fd, buffer, BUFFER_SIZE);
		if (bytes_read <= 0)
			break ;
		buffer[bytes_read] = '\0';
		temp = stash[fd];
		stash[fd] = ft_strjoin(stash[fd], buffer);
		free(temp);
	}
	return_new_line(&line, &temp, &stash[fd]);
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