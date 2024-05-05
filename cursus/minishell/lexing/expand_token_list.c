/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_token_list.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: florian <florian@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/05 18:13:10 by florian           #+#    #+#             */
/*   Updated: 2024/05/05 18:13:21 by florian          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

char	*trimmer(char *str)
{
	int		i;
	int		j;
	char	*res;
	int		len;

	len = ft_strlen(str);
	res = malloc(sizeof(char) * (len + 1));
	if (!res)
		return (NULL);
	i = 0;
	j = 0;
	if (str[0] == '"' || str[0] == '\'')
	{
		i++;
		len--;
	}
	while (i < len)
	{
		res[j] = str[i];
		i++;
		j++;
	}
	res[j] = '\0';
	return (res);
}

void	expand_token(t_token *current, t_env **env)
{
	char	*tmp;

	tmp = expander(current->value, env);
	free(current->value);
	current->value = tmp;
}

void	trim_token(t_token *current)
{
	char	*tmp;

	tmp = trimmer(current->value);
	free(current->value);
	current->value = tmp;
}

void	expand_token_list(t_token **token_list, t_env **env)
{
	t_token	*current;
	int		flag;

	flag = 0;
	current = *token_list;
	while (current)
	{
		if (current->type == HEREDOC)
		{
			flag = 1;
			current = current->next;
		}
		if (flag == 0)
			expand_token(current, env);
		else
			trim_token(current);
		flag = 0;
		current = current->next;
	}
}