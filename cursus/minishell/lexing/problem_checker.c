/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   problem_checker.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: florian <florian@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/02 11:37:41 by florian           #+#    #+#             */
/*   Updated: 2024/07/26 13:47:55 by florian          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	check_quote_problems(char *line)
{
	int		i;
	char	current_quote;

	i = 0;
	current_quote = '\0';
	while (line[i])
	{
		if (line[i] == '\'' || line[i] == '"')
		{
			if (current_quote == '\0')
				current_quote = line[i];
			else if (current_quote == line[i])
				current_quote = '\0';
		}
		i++;
	}
	if (current_quote != '\0')
		return (0);
	return (1);
}

int	redirection_flag_updater(char *line, int *i, int len)
{
	int	flag;

	flag = 0;
	while (line[*i] && *i < len - 1)
	{
		if (!is_space(line[*i]) && line[*i] != '|')
			flag = 1;
		if (line[*i] == '|')
		{
			if (flag == 0)
				return (0);
			else
				break ;
		}
		(*i)++;
	}
	return (flag);
}

int	check_redirection_problems(char *line)
{
	int	i;
	int	flag;
	int	len;

	len = ft_strlen(line);
	i = 0;
	while (line[i])
	{
		if ((line[i] == '>' || line[i] == '<'))
		{
			flag = 0;
			i++;
			flag = redirection_flag_updater(line, &i, len);
			if (flag == 0)
				return (0);
		}
		i++;
	}
	return (1);
}

int	check_pipe_problems(char *line)
{
	int		i;
	int		flag;
	char	quote;

	i = 0;
	flag = 0;
	quote = '\0';
	while (line[i])
	{
		if (line[i] == '\'' || line[i] == '"')
		{
			quote = line[i];
			i++;
			while (line[i] && line[i] != quote)
				i++;
		}
		if (!is_space(line[i]) && line[i] != '|')
			flag = 1;
		if (line[i] == '|' && flag == 0)
			return (0);
		else if (line[i] == '|' && flag == 1)
			flag = 0;
		i++;
	}
	return (1);
}

int	check_problems(char *line, t_env **env)
{
	size_t	i;

	i = 0;
	while (line[i])
	{
		if (!is_space(line[i]))
			break ;
		i++;
	}
	if (i == ft_strlen(line))
		return (0);
	if (!check_quote_problems(line))
		return (exit_status(2, *env), ft_printf("Error: unclosed quote\n",
				STDERR_FILENO), 0);
	if (!check_pipe_problems(line))
		return (exit_status(2, *env), ft_printf(ERR_PIPE, STDERR_FILENO), 0);
	if (!check_redirection_problems(line))
		return (exit_status(2, *env), ft_printf(ERR_REDIR, STDERR_FILENO),
			0);
	return (1);
}
