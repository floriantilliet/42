/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ftilliet <ftilliet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/25 08:56:16 by ochetrit          #+#    #+#             */
/*   Updated: 2024/09/10 11:36:35 by ftilliet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/minishell.h"

int	write_in(int fd, char *limit, t_env **env)
{
	char	*ret;

	while (TRUE)
	{
		write(STDOUT_FILENO, ">", 1);
		ret = get_next_line(STDIN_FILENO);
		if (!ft_strcmp(ret, limit))
		{
			if (!ret)
				write(STDOUT_FILENO, "\n", 1);
			close(fd);
			free(ret);
			if (g_exit_code == SIGINT)
				return (close(fd), exit_status(130, *env), FALSE);
			return (exit_status(0, *env), TRUE);
		}
		ft_putstr_fd(ret, fd);
		free(ret);
	}
	return (TRUE);
}

int	create_here_doc(t_token *lst, char *limiter, int n, t_env **env)
{
	char	*tmp1;
	char	*tmp2;
	char	*limit;

	tmp1 = ft_strdup(".tmp");
	tmp2 = ft_itoa(n);
	lst->file_n = ft_strjoin(tmp1, tmp2);
	free(tmp1);
	free(tmp2);
	lst->fd = open(lst->file_n, O_RDWR | O_CREAT, S_IRUSR | S_IWUSR);
	if (lst->fd == -1)
		return (ft_printf(ERROR_OPEN, 2), exit_status(1, *env), FALSE);
	limit = ft_strjoin(limiter, "\n");
	if (!write_in(lst->fd, limit, env))
		return (free(limit), FALSE);
	return (free(limit), TRUE);
}

void	initialise_file_n(t_token **tokens)
{
	t_token	*lst;

	if (!tokens || !*tokens)
		return ;
	lst = *tokens;
	while (lst)
	{
		lst->file_n = NULL;
		lst = lst->next;
	}
}

int	handle_here_doc(t_token **tokens, t_env **env)
{
	t_token	*lst;
	int		nb;

	lst = *tokens;
	nb = 0;
	signals(HERE_DOC);
	initialise_file_n(tokens);
	while (lst)
	{
		lst->fd = 0;
		if (lst->type == HEREDOC)
		{
			nb++;
			if (!lst->next || !(lst->next->value))
				return (exit_status(2, *env), FALSE);
			if (!create_here_doc(lst, lst->next->value, nb, env))
				return (signals(PROMPT), FALSE);
		}
		lst = lst->next;
	}
	signals(CHILD);
	return (TRUE);
}

int	init_std(t_env *env)
{
	if (dup2(env->fd_in, STDIN_FILENO) == -1)
		return (ft_printf(ERROR_DUP, STDERR_FILENO), FALSE);
	if (dup2(env->fd_out, STDOUT_FILENO) == -1)
		return (ft_printf(ERROR_DUP, STDERR_FILENO), FALSE);
	return (TRUE);
}
