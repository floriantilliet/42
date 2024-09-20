/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ochetrit <ochetrit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/03 16:08:44 by ochetrit          #+#    #+#             */
/*   Updated: 2024/09/11 19:44:06 by ochetrit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	concatenate_value(char *tab[2], t_env *lst, t_env **env)
{
	char	*tmp;

	while (lst && ft_strcmp(tab[0], lst->key))
		lst = lst->next;
	if (!lst)
		add_new_env_node(tab[0], tab[1], env);
	if (!lst->value || !*lst->value)
	{
		if (!*lst->value)
			free(lst->value);
		lst->value = ft_strdup(tab[1]);
	}
	else
	{
		tmp = lst->value;
		lst->value = ft_strjoin(lst->value, tab[1]);
		free(tmp);
	}
	if (lst && !lst->value)
		ft_printf(ERR_MALLOC, STDERR_FILENO);
	if (tab[0])
		free(tab[0]);
	if (tab[1])
		free(tab[1]);
}

void	replace_value(char *key, char *value, t_env *lst, t_env **env)
{
	while (lst && ft_strcmp(key, lst->key))
		lst = lst->next;
	if (!lst)
		add_new_env_node(key, value, env);
	else
	{
		free(lst->value);
		lst->value = ft_strdup(value);
		if (!lst->value)
			ft_printf(ERR_MALLOC, STDERR_FILENO);
	}
	if (key)
		free(key);
	if (value)
		free(value);
}

int	is_new_node(char *value, t_env **env)
{
	t_env	*lst;

	lst = *env;
	while (lst && ft_strcmp(value, lst->key))
		lst = lst->next;
	if (lst)
		return (FALSE);
	return (TRUE);
}

int	ft_export_bis(char *value, t_env **env)
{
	char	*tab[2];
	int		len;

	len = ft_strchr2(value, '+');
	tab[0] = NULL;
	tab[1] = NULL;
	if (len == ft_strchr2(value, '=') - 1 && value[len + 2])
	{
		tab[0] = ft_substr(value, 0, len);
		tab[1] = ft_substr(value, len + 2, ft_strlen(value));
		concatenate_value(tab, *env, env);
	}
	else if (ft_strchr2(value, '=') != -1)
	{
		tab[0] = ft_substr(value, 0, ft_strchr2(value, '='));
		len = ft_strchr2(value, '=');
		if (!value[len + 1])
			tab[1] = ft_strdup("");
		else
			tab[1] = ft_substr(value, len + 1, ft_strlen(value));
		replace_value(tab[0], tab[1], *env, env);
	}
	else if (is_new_node(value, env))
		add_new_env_node(value, NULL, env);
	return (TRUE);
}

int	ft_export(t_token *tokens, t_env **env)
{
	t_token		*lst;
	int			exit_code;

	lst = tokens;
	exit_code = 0;
	if (lst->type == CMD)
		lst = lst->next;
	if (!lst || lst->type != ARG)
		return (print_env_in_order(env), exit_status(0, *env), TRUE);
	while (lst && lst->type == ARG)
	{
		if (!parsing_export(lst->value))
			exit_code = 1;
		else if (!ft_export_bis(lst->value, env))
			exit_code = 1;
		lst = lst->next;
	}
	if (exit_code)
		exit_status(exit_code, *env);
	return (TRUE);
}
