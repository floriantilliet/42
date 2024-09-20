/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   strings_to_tokens_utils.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ftilliet <ftilliet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/10 17:30:13 by ftilliet          #+#    #+#             */
/*   Updated: 2024/09/11 21:30:38 by ftilliet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

t_token	**initialize_token_list(void)
{
	t_token	**token_list;

	token_list = malloc(sizeof(t_token *));
	if (!token_list)
		return (NULL);
	*token_list = NULL;
	return (token_list);
}

int	process_token(char **tokens, int *i, t_env **env)
{
	check_env_var(tokens[*i], env);
	while (tokens[*i] && tokens[*i][0] == '\0')
		(*i)++;
	if (!tokens[*i])
		return (0);
	return (1);
}
