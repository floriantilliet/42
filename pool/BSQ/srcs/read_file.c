/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_file.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: udumas <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/27 14:18:45 by udumas            #+#    #+#             */
/*   Updated: 2023/09/27 14:18:47 by udumas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_libr.h"

int	ft_open(char *path)
{
	int	file_descriptor;

	file_descriptor = open(path, O_RDONLY);
	return (file_descriptor);
}

/*int	get_file_size(int fd)
{
	int		total_size;
	int		bytes_read;
	char	buffer[2048];

	total_size = 0;
	while (1)
	{
		bytes_read = read(fd, buffer, sizeof(buffer));
		if (bytes_read <= 0)
		{
			break ;
		}
		total_size += bytes_read;
	}
	return (total_size);
}

char	*read_file_content(const char *path, int file_size)
{
	int		fd;
	char	*str;
	int		bytes_read;

	fd = open(path, O_RDONLY);
	if (fd == -1)
		return (NULL);
	str = malloc(file_size + 1);
	if (str == NULL)
	{
		close(fd);
		return (NULL);
	}
	bytes_read = read(fd, str, file_size);
	if (bytes_read == -1)
	{
		free(str);
		close(fd);
		return (NULL);
	}
	close(fd);
	str[file_size] = '\0';
	return (str);
}*/

char	*ft_read(const char *path)
{
	char	*buffer;
	int		size;
	int		i;
	int		fd;

	i = 0;
	buffer = (char *)malloc(sizeof(char) * TEST + 1);
	clean_str(buffer);
	size = TEST;
	fd = open(path, O_RDONLY);
	while (size == TEST)
	{
		size = read(fd, buffer, TEST);
		i = size;
	}
	if (i == 0)
	{
		free(buffer);
		return (NULL);
	}
	buffer[i] = '\0';
	return (buffer);
}

int	get_cell_value(char c, char *str)
{
	if (c == str[0])
		return (1);
	if (c == str[1])
		return (0);
	else
		return (0);
}

/*
void	print_matrix(int **tab, int line_len, int col_len)
{
	int		i;
	int		j;
	char	c;

	i = 0;
	while (i < col_len)
	{
		j = 0;
		while (j < line_len)
		{
			c = tab[i][j] + '0';
			write(1, &c, 1);
			if (j < line_len - 1)
				write(1, " ", 1);
			j++;
		}
		write(1, "\n", 1);
		i++;
	}
}

int	main(void)
{
	char	*str;
	int		**tab;
	int		line_len;
	int		col_len;

	str = "map_example2";
	str = ft_read(str);
	str = ft_update_res(str, "\0");
	col_len = check_line2(str,take_sep(str));
	line_len = ft_linelen(str + check_first_line(str) + 1); // len fline
	tab = def_matrix(line_len, col_len);
	tab = get_matrix(tab, str, take_sep(str));
	printf("%s\n", str);
	print_matrix(tab, line_len, col_len);
}
*/
