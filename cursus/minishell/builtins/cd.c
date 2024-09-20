/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ochetrit <ochetrit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/03 13:08:16 by ochetrit          #+#    #+#             */
/*   Updated: 2024/07/17 17:11:43 by ochetrit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	cd_home(t_env **env, t_env *lst)
{
	while (lst)
	{
		if (!ft_strcmp(lst->key, "HOME"))
			break ;
		lst = lst->next;
	}
	if (!lst)
		return (ft_printf(ERR_CD_NO_ARGS, STDERR_FILENO),
			exit_status(1, *env), FALSE);
	if (chdir(lst->value) != 0)
		return (ft_printf(ERR_CD, STDERR_FILENO,
				lst->value), exit_status(1, *env), FALSE);
	return (exit_status(0, *env), TRUE);
}

int	ft_cd(t_token *tokens, t_env **env)
{
	t_token	*lst;
	char	*pwd;
	char	*str;	

	lst = tokens;
	while (lst && lst->type != CMD)
		lst = lst->next;
	lst = lst->next;
	if (!lst || lst->type != ARG)
		return (cd_home(env, *env));
	else if (lst->next && lst->next->type == ARG)
		return (ft_printf(ERR_CD_NB_ARG, STDERR_FILENO),
			exit_status(1, *env), FALSE);
	if (chdir(lst->value) == 0)
		return (TRUE);
	pwd = getcwd(NULL, 0);
	str = ft_strjoin(pwd, lst->value);
	free(pwd);
	if (chdir(str) != 0)
	{
		ft_printf(ERR_CD, STDERR_FILENO, lst->value);
		return (free(str), exit_status(1, *env), FALSE);
	}
	free(str);
	return (exit_status(0, *env), TRUE);
}
