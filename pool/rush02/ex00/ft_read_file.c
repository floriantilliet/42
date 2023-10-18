/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_read_file.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rdupeux <rdupeux@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/24 14:59:42 by rdupeux           #+#    #+#             */
/*   Updated: 2023/09/24 23:22:09 by rdupeux          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft.h"

int	ft_open(char *path)
{
	int	file_descriptor;

	file_descriptor = open(path, O_RDONLY);
	return (file_descriptor);
}

char	*ft_read(char *path)
{
	char	*str;
	int		file_descriptor;

	file_descriptor = ft_open(path);
	if (file_descriptor == -1)
	{
		ft_print_error();
		return (NULL);
	}
	str = malloc(1024);
	clean_str(str);
	if (read(file_descriptor, str, 1024) == -1)
	{
		ft_print_dict_error();
		free(str);
		str = NULL;
		return (NULL);
	}
	close(file_descriptor);
	return (str);
}

t_dict	*set_tab(char **tab)
{
	int		len;
	int		i;
	int		j;
	t_dict	*res;

	len = 0;
	j = 0;
	i = 0;
	while (tab[len])
		len++;
	res = malloc(len * sizeof(t_dict *));
	while (tab[i])
	{
		res[j].key = tab[i];
		i++;
		res[j].value = tab[i];
		i++;
		j++;
	}
	res[j].key = 0;
	free(tab);
	return (res);
}

t_dict	*get_dict(char *str)
{
	t_dict	*dict_base;
	t_dict	*dict_add;
	char	*res;

	dict_add = NULL;
	res = ft_read("numbers.dict");
	if (!res)
	{
		ft_print_error();
		return (NULL);
	}
	dict_base = set_tab(ft_dic_split(res));
	if (str)
	{
		free(res);
		res = ft_read(str);
		if (!res)
		{
			ft_print_error();
			return (NULL);
		}
		dict_add = set_tab(ft_dic_split(res));
	}
	free(res);
	return (merge_dict(dict_base, dict_add));
}
