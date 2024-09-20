/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ochetrit <ochetrit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/20 18:46:29 by ochetrit          #+#    #+#             */
/*   Updated: 2024/09/11 19:21:18 by ochetrit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	free_cmd(t_cmd *cmd)
{
	if (cmd->cmd)
		free_char_tab(cmd->cmd);
	if (cmd->env)
		free_char_tab(cmd->env);
	if (cmd->path)
		free(cmd->path);
	free(cmd);
}

void	get_access(t_cmd *cmd, char *str, t_env *lst_env)
{
	char	**tab;
	char	*tmp;
	int		i;

	while (lst_env->next && ft_strcmp(lst_env->key, "PATH"))
		lst_env = lst_env->next;
	if (ft_strcmp(lst_env->key, "PATH"))
		return ;
	i = -1;
	tab = ft_split(lst_env->value, ':');
	while (tab[++i])
	{
		tmp = ft_strjoin(tab[i], "/");
		cmd->path = ft_strjoin(tmp, str);
		free(tmp);
		if (access(cmd->path, F_OK) != -1)
		{
			free_char_tab(tab);
			cmd->free_path = 1;
			return ;
		}
		free(cmd->path);
	}
	free_char_tab(tab);
	cmd->path = NULL;
}

void	path_cmd(char *value, t_cmd *cmd, t_env **env, t_token **tokens)
{
	struct stat	path_stat;

	if (access(value, F_OK) != -1)
		cmd->path = ft_strdup(value);
	else
		get_access(cmd, value, *env);
	if (stat(cmd->path, &path_stat) != 0)
	{
		ft_printf(ERR_CMD, STDERR, value);
		free_cmd(cmd);
		free_everything(env, tokens, 127);
	}
	else if (S_ISDIR(path_stat.st_mode))
	{
		ft_printf(ERR_IS_DIR, STDERR, value);
		free_cmd(cmd);
		free_everything(env, tokens, 126);
	}
	else if (!(path_stat.st_mode & S_IXUSR))
	{
		ft_printf(ERR_PERM, STDERR, value);
		free_cmd(cmd);
		free_everything(env, tokens, 126);
	}
}

int	access_cmd(t_token *lst, t_token **tokens, t_env **env)
{
	t_cmd	*cmd;

	cmd = initialise_cmd(&lst, env);
	if (!cmd)
		return (0);
	close_redirect(&lst);
	while (lst->type != CMD && lst->next)
		lst = lst->next;
	close_dup(env);
	path_cmd(lst->value, cmd, env, tokens);
	if (!cmd || !cmd->path || execve(cmd->path, cmd->cmd, cmd->env) == -1)
		ft_printf("Error execve\n", STDERR_FILENO);
	free_char_tab(cmd->cmd);
	free_char_tab(cmd->env);
	free(cmd->path);
	free(cmd);
	if (errno == ENOENT)
		free_everything(env, tokens, 127);
	return (free_everything(env, tokens, errno), 0);
}
