/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_env_var_utils_2.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ftilliet <ftilliet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/10 17:30:13 by ftilliet          #+#    #+#             */
/*   Updated: 2024/09/12 11:15:21 by ftilliet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	handle_quotes(char *str, int *len, int *quote_flag)
{
	remove_quotes(str, *len);
	*quote_flag = 1;
}

void	handle_dollar_question(char *str, int *i, t_env **env, int *len)
{
	char	*exit;
	char	*sub;
	char	*tmp;

	exit = ft_itoa((*env)->exit_code);
	sub = ft_substr(str, *i + 1, 1);
	tmp = ft_strjoin(exit, sub);
	*len = ft_strlen(str);
	free(tmp);
	free(exit);
	free(sub);
}
