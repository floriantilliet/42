/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rdupeux <rdupeux@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/23 20:26:26 by rdupeux           #+#    #+#             */
/*   Updated: 2023/09/24 23:21:13 by rdupeux          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft.h"

char	*get_array(char a, char b, char c)
{
	char	*res;

	res = malloc(4);
	res[0] = a;
	res[1] = b;
	res[2] = c;
	res[3] = 0;
	return (res);
}

char	*set_hundred(char *res, char *str, t_dict *dict)
{
	if (str[0] != '0')
	{
		res = ft_update_res(res, get(get_array(str[0], 0, 0), dict));
		res = ft_update_res(res, get(get_array('1', '0', '0'), dict));
	}
	return (res);
}

char	*set_ten(char *res, char *str, t_dict *dict)
{
	if (get(get_array(str[1], str[2], 0), dict) != NULL)
		res = ft_update_res(res, get(get_array(str[1], str[2], 0), dict));
	else if (str[1] != '0')
	{
		res = ft_update_res(res, get(get_array(str[1], '0', 0), dict));
		res = ft_update_res(res, get(get_array(str[2], 0, 0), dict));
	}
	else if (str[2] != '0')
		res = ft_update_res(res, get(get_array(str[2], 0, 0), dict));
	return (res);
}

int	get_len_to_add(char *str)
{
	int	to_add;
	int	len;

	to_add = 0;
	len = ft_strlen(str);
	while (len % 3 != 0)
	{
		len++;
		to_add++;
	}
	return (to_add);
}

void	free_dict(t_dict *dict)
{
	int	i;

	i = 0;
	while (dict[i].key)
	{
		free(dict[i].key);
		free(dict[i].value);
		i++;
	}
	free(dict);
}
