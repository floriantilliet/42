/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: florian <florian@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/27 05:41:57 by ftilliet          #+#    #+#             */
/*   Updated: 2024/05/05 16:13:19 by florian          ###   ########.fr       */
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
	char	*sub;
	char	*tmp;

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
                sub = ft_substr(line, i, 1);
                tmp = ft_strjoin(res, sub);
                free(res);
                free(sub);
                res = tmp;
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
                {
                    tmp = ft_strjoin(res, "$");
                    free(res);
                    res = tmp;
                }
				else
				{
                    sub = ft_substr(line, i, j);
                    tmp = ft_strjoin(res, get_env_value(sub, env));
                    free(res);
                    free(sub);
                    res = tmp;
                    i += j;
				}
			}
			if (line[i] != current_quote)
			{
                sub = ft_substr(line, i, 1);
                tmp = ft_strjoin(res, sub);
                free(res);
                free(sub);
                res = tmp;
			}
			i++;
		}
	}
	return (res);
}
