/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_val.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rdupeux <rdupeux@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/23 17:13:30 by rdupeux           #+#    #+#             */
/*   Updated: 2023/09/24 23:20:35 by rdupeux          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft.h"

char	*get(char *c, t_dict *dict)
{
	int	i;

	if (!c)
	{
		free(c);
		return (NULL);
	}
	i = 0;
	while (dict[i].key)
	{
		if (ft_strcmp(dict[i].key, c) == 0)
		{
			free(c);
			return (dict[i].value);
		}
		i++;
	}
	free(c);
	return (NULL);
}

char	*create_power(int len)
{
	char	*res;
	int		i;

	if (len < 3)
		return (NULL);
	i = 1;
	res = malloc(len + 1);
	if (!res)
		return (NULL);
	res[0] = '1';
	while (i <= len)
	{
		res[i] = '0';
		i++;
	}
	res[i] = 0;
	return (res);
}

char	*gen_res(t_dict *dict, char *str, char *res)
{
	int	len;
	int	i;
	int	j;

	i = 0;
	j = 0;
	len = ft_strlen(str);
	if (len == 1 && str[0] == '0')
	{
		free(res);
		return (get("0", dict));
	}
	res = set_hundred(res, str, dict);
	res = set_ten(res, str, dict);
	if (str[2] != '0')
		res = ft_update_res(res, get(create_power(len - 3), dict));
	if (len != 3)
	{
		res = gen_res(dict, &str[3], res);
	}
	return (res);
}

char	*normalyze_input(char *str)
{
	int		len;
	int		i;
	int		j;
	char	*res;
	int		to_add;

	to_add = get_len_to_add(str);
	len = ft_strlen(str);
	j = 0;
	i = 0;
	res = malloc(len + to_add);
	while (to_add > 0)
	{
		res[i] = '0';
		i++;
		to_add--;
	}
	while (str[j])
	{
		res[i] = str[j];
		i++;
		j++;
	}
	res[i] = 0;
	return (res);
}
