/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialise_cmd.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ochetrit <ochetrit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/18 16:11:27 by ochetrit          #+#    #+#             */
/*   Updated: 2024/07/27 14:16:36 by ochetrit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	free_smth(t_cmd *cmd)
{
	free_char_tab(cmd->cmd);
	free(cmd);
	ft_printf(ERR_MALLOC, STDERR_FILENO);
}

char	**initialise_cmd_cmd(t_token *lst, t_cmd *cmd, int len)
{
	int	i;

	cmd->cmd = malloc(sizeof(char *) * (len + 1));
	if (!cmd->cmd)
		return (ft_printf(ERR_MALLOC, STDERR_FILENO), NULL);
	cmd->cmd[len] = NULL;
	i = 0;
	while (lst && lst->type != CMD)
		lst = lst->next;
	while (lst && i < len)
	{
		if (lst->type < PIPE)
		{
			cmd->cmd[i] = ft_strdup(lst->value);
			lst = lst->next;
			if (!cmd->cmd[i])
				return (free_smth(cmd), NULL);
			i++;
		}
		else if (lst->type > PIPE)
			lst = skip_redirect(lst, NULL);
		else
			break ;
	}
	return (cmd->cmd);
}

char	*build_env(char *key, char *value)
{
	char	*tmp;
	char	*built;

	if (!value)
	{
		built = ft_strdup(key);
		if (!built)
			return (NULL);
		return (built);
	}
	tmp = ft_strjoin(key, "=");
	if (!tmp)
		return (ft_printf(ERR_MALLOC, STDIN_FILENO), NULL);
	built = ft_strjoin(tmp, value);
	free(tmp);
	return (built);
}

char	**initialise_cmd_env(t_env **env)
{
	char	**tab;
	int		len;
	t_env	*lst;

	lst = *env;
	len = 0;
	while (lst)
	{
		len++;
		lst = lst->next;
	}
	tab = malloc(sizeof(char *) * (len + 1));
	if (!tab)
		return (ft_printf(ERR_MALLOC, STDERR_FILENO), NULL);
	lst = *env;
	tab[len] = NULL;
	len = -1;
	while (lst && len++ > -2)
	{
		tab[len] = build_env(lst->key, lst->value);
		lst = lst->next;
		if (!tab[len])
			return (ft_printf(ERR_MALLOC, STDERR), free_char_tab(tab), NULL);
	}
	return (tab);
}

t_cmd	*initialise_cmd(t_token **tokens, t_env **env)
{
	t_cmd	*cmd;

	cmd = malloc(sizeof(t_cmd));
	if (!cmd)
		return (ft_printf(ERR_MALLOC, STDERR_FILENO), NULL);
	cmd->free_path = 0;
	cmd->path = NULL;
	cmd->len = 0;
	cmd->is_pipe = 0;
	cmd->cmd = NULL;
	cmd->env = NULL;
	if (!count_len(tokens, cmd))
		return (free(cmd), NULL);
	if (cmd->len)
	{
		cmd->cmd = initialise_cmd_cmd(*tokens, cmd, cmd->len);
		cmd->env = initialise_cmd_env(env);
		if (!cmd->cmd || !cmd->env)
			return (free(cmd), NULL);
	}
	return (cmd);
}
