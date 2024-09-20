/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ftilliet <ftilliet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/27 05:41:57 by ftilliet          #+#    #+#             */
/*   Updated: 2024/09/11 21:09:53 by ftilliet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	handle_exp_quotes(char *line, char *current_quote, int *expand, int *i)
{
	if (*current_quote == '\0')
	{
		*current_quote = line[*i];
		*expand = (line[*i] == '"');
	}
	else if (*current_quote == line[*i])
	{
		*current_quote = '\0';
		*expand = 1;
	}
	(*i)++;
}

void	append_char(char **res, char *line, int *i)
{
	char	*sub;
	char	*tmp;

	sub = ft_substr(line, *i, 1);
	tmp = ft_strjoin(*res, sub);
	free(*res);
	free(sub);
	*res = tmp;
	(*i)++;
}

void	expand_variable(char **res, char *sub, int j, t_env **env)
{
	char	*exit;
	char	*sub2;
	char	*tmp;
	char	*tmp2;

	if (sub[0] == '?')
	{
		exit = ft_itoa((*env)->exit_code);
		sub2 = ft_substr(sub, 1, j - 1);
		tmp2 = ft_strjoin(exit, sub2);
		tmp = ft_strjoin(*res, tmp2);
		free(tmp2);
		free(exit);
		free(sub2);
	}
	else
		tmp = ft_strjoin(*res, get_env_value(sub, env));
	free(*res);
	free(sub);
	*res = tmp;
}

void	handle_expansion(char **res, char *line, int *i, t_env **env)
{
	int		j;
	char	*sub;
	char	*tmp;

	j = 0;
	(*i)++;
	while (line[*i + j] != ' ' && line[*i + j] != '\0' && line[*i + j] != '$'
		&& line[*i + j] != '\'' && line[*i + j] != '"')
		j++;
	if (j == 0)
	{
		tmp = ft_strjoin(*res, "$");
		free(*res);
		*res = tmp;
	}
	else
	{
		sub = ft_substr(line, *i, j);
		expand_variable(res, sub, j, env);
		*i += j;
	}
}

char	*expander(char *line, t_env **env)
{
	char	*res;
	int		i;
	char	current_quote;
	int		expand;

	res = ft_strdup("");
	i = 0;
	current_quote = '\0';
	expand = 1;
	while (line[i])
	{
		if (line[i] == '\'' || line[i] == '"')
		{
			if (current_quote == '\0' || current_quote == line[i])
				handle_exp_quotes(line, &current_quote, &expand, &i);
			else
				append_char(&res, line, &i);
		}
		else if (line[i] == '$' && expand)
			handle_expansion(&res, line, &i, env);
		else
			append_char(&res, line, &i);
	}
	return (res);
}
