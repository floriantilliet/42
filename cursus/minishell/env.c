/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: florian <florian@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/27 05:41:11 by ftilliet          #+#    #+#             */
/*   Updated: 2024/07/07 16:36:23 by florian          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/minishell.h"

t_env	*create_env_node(char *env_str)
{
	t_env	*new_node;
	char	*equal_signs;
	size_t	length;

	new_node = (t_env *)malloc(sizeof(t_env));
	if (!new_node)
		return (NULL);
	equal_signs = strchr(env_str, '=');
	length = equal_signs - env_str;
	new_node->key = (char *)malloc(length + 1);
	if (!new_node->key)
	{
		free(new_node);
		return (NULL);
	}
	strncpy(new_node->key, env_str, length);
	new_node->key[length] = '\0';
	new_node->value = ft_strdup(equal_signs + 1);
	new_node->next = NULL;
	new_node->exit_code = 0;
	return (new_node);
}

void	append_env_node(t_env **env, t_env *new_node)
{
	t_env	*current;

	if (*env == NULL)
		*env = new_node;
	else
	{
		current = *env;
		while (current->next != NULL)
			current = current->next;
		current->next = new_node;
	}
}

t_env	**store_env(char **envp)
{
	t_env	**env;
	t_env	*new_node;

	env = (t_env **)malloc(sizeof(t_env *));
	if (!env)
		return (NULL);
	*env = NULL;
	while (*envp)
	{
		new_node = create_env_node(*envp);
		if (!new_node)
			return (NULL);
		append_env_node(env, new_node);
		envp++;
	}
	return (env);
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

void	increment_shlvl(t_env *env)
{
	char	*tmp;
	int		shlvl;

	while (env && ft_strcmp(env->key, "SHLVL"))
		env = env->next;
	if (!env)
		return ;
	shlvl = ft_atoi(env->value);
	if (shlvl < 0)
		shlvl = 0;
	else
		shlvl++;
	tmp = ft_itoa(shlvl);
	free(env->value);
	env->value = tmp;
}
