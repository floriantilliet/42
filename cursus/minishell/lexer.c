/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ftilliet <ftilliet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/27 05:41:57 by ftilliet          #+#    #+#             */
/*   Updated: 2024/03/27 05:44:23 by ftilliet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*expander(char *line, t_env **env)
{
	char	*res;
	int		i;
	int		j;
	char	current_quote;
	int		expand;

	expand = 1;
	res = ft_strdup("");
	i = 0;
	current_quote = '\0';
	while (line[i])
	{
		if (line[i] == '\'' || line[i] == '"')
		{
			if (current_quote == '\0')
			{
				current_quote = line[i];
				expand = (line[i] == '"');
				i++;
			}
			else if (current_quote == line[i])
			{
				current_quote = '\0';
				expand = 1;
				i++;
			}
			else
			{
				res = ft_strjoin(res, ft_substr(line, i, 1));
				i++;
			}
		}
		else
		{
			if (line[i] == '$' && expand)
			{
				i++;
				j = 0;
				while (line[i + j] != ' ' && line[i + j] != '\0' && line[i
					+ j] != '$' && line[i + j] != '\'' && line[i + j] != '"')
					j++;
				if (j == 0)
					res = ft_strjoin(res, "$");
				else
				{
					res = ft_strjoin(res, get_env_value(ft_substr(line, i, j),
								env));
					i += j;
				}
			}
			if (line[i] != current_quote)
			{
				res = ft_strjoin(res, ft_substr(line, i, 1));
			}
			i++;
		}
	}
	if (current_quote != '\0')
		return ("Error: unclosed quote");
	return (res);
}

void	lexer(char *line, t_env **env)
{
	expander(line, env);
}
