/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: florian <florian@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/27 05:41:11 by ftilliet          #+#    #+#             */
/*   Updated: 2024/04/12 20:37:46 by florian          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_env	**store_env(char **envp)
{
	t_env	**env;
	t_env	*current;
	t_env	*new_node;
	char	*equals_sign;
	size_t	length;

	env = (t_env **)malloc(sizeof(t_env *));
	if (!env)
		return (NULL);
	*env = NULL;
	while (*envp)
	{
		current = *env;
		new_node = (t_env *)malloc(sizeof(t_env));
		if (!new_node)
			return (NULL);
		equals_sign = strchr(*envp, '=');
		length = equals_sign - *envp;
		new_node->key = malloc(length + 1);
		if (!new_node->key)
			return (NULL);
		strncpy(new_node->key, *envp, length);
		new_node->key[length] = '\0';
		new_node->value = ft_strdup(ft_strchr(*envp, '=') + 1);
		new_node->next = NULL;
		if (current == NULL)
			*env = new_node;
		else
		{
			while (current->next != NULL)
				current = current->next;
			current->next = new_node;
		}
		envp++;
	}
	return (env);
}

void	printenv(t_env **env)
{
	t_env	*current;

	current = *env;
	while (current)
	{
		printf("%s=%s\n", current->key, current->value);
		current = current->next;
	}
}

char	*get_env_value(char *key, t_env **env)
{
	t_env	*current;

	current = *env;
	if (ft_strlen(key) == 0)
		return ("");
	while (current)
	{
		if (ft_strncmp(current->key, key, ft_strlen(key)) == 0
			&& current->key[ft_strlen(key)] == '\0')
			return (current->value);
		current = current->next;
	}
	return ("");
}
