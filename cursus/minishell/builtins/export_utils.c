/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ochetrit <ochetrit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/06 11:40:03 by ochetrit          #+#    #+#             */
/*   Updated: 2024/07/18 11:24:08 by ochetrit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	ft_strcmp(const char *s1, const char *s2)
{
	if (!s1 || !s2)
		return (FALSE);
	while (*s1 && *s2 && *s1 == *s2)
	{
		s1++;
		s2++;
	}
	return (*s2 - *s1);
}

void	put_env_in_order(char **tab)
{
	int		i;
	int		j;
	char	*tmp;

	i = 0;
	while (tab[i])
	{
		j = i + 1;
		while (tab[j])
		{
			if (ft_strcmp(tab[i], tab[j]) < 0)
			{
				tmp = tab[i];
				tab[i] = tab[j];
				tab[j] = tmp;
			}
			j++;
		}
		i++;
	}
}

void	print_one_line(char *str)
{
	int	len;

	write(STDOUT_FILENO, "declare -x ", ft_strlen("declare -x "));
	len = ft_strchr2(str, '=');
	if (len != -1)
	{
		write(STDOUT_FILENO, str, len);
		write(STDOUT_FILENO, "=\"", 2);
		if (str[len + 1])
			write(STDOUT_FILENO, &str[len + 1], ft_strlen(str) - len);
		write(STDOUT_FILENO, "\"", 1);
	}
	else
		write(STDOUT_FILENO, str, ft_strlen(str));
	write(STDOUT_FILENO, "\n", 1);
}

void	print_env_in_order(t_env **env)
{
	char	**tab;
	int		i;

	tab = initialise_cmd_env(env);
	if (!tab)
	{
		ft_printf(ERR_MALLOC, STDERR_FILENO);
		return ;
	}
	put_env_in_order(tab);
	i = 0;
	while (tab[i])
	{
		print_one_line(tab[i]);
		i++;
	}
	free_char_tab(tab);
}

void	add_new_env_node(char *key, char *value, t_env **env)
{
	t_env	*lst;

	lst = *env;
	while (lst->next)
		lst = lst->next;
	lst->next = malloc(sizeof(t_env));
	if (!lst->next)
		return ;
	lst->next->key = ft_strdup(key);
	if (!lst->next->key)
		free(lst->next);
	if (value && key)
	{
		lst->next->value = ft_strdup(value);
		if (!lst->next->value)
		{
			free(lst->next->key);
			free(lst->next);
		}
	}
	else
		lst->next->value = NULL;
	if (lst->next)
		lst->next->next = NULL;
}
