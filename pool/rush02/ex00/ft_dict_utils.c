/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dict_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rdupeux <rdupeux@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/24 20:25:19 by rdupeux           #+#    #+#             */
/*   Updated: 2023/09/24 23:19:44 by rdupeux          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft.h"

int	match_string(char *s1, char *s2)
{
	int	i;

	i = 0;
	while (s1[i] || s2[i])
	{
		if (s1[i] != s2[i])
			return (0);
		i++;
	}
	return (1);
}

t_dict	*merge_dict(t_dict *dict_base, t_dict *dict_add)
{
	int	i;
	int	j;

	i = 0;
	if (!dict_add)
		return (dict_base);
	while (dict_add[i].key)
	{
		j = 0;
		while (dict_base[j].key)
		{
			if (match_string(dict_add[i].key, dict_base[j].key))
			{
				free(dict_base[j].value);
				dict_base[j].value = dict_add[i].value;
				dict_add[i].value = NULL;
			}
			j++;
		}
		i++;
	}
	free_dict(dict_add);
	return (dict_base);
}
