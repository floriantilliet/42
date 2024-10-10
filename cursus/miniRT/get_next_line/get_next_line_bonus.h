/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.h                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: florian <florian@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/28 13:08:28 by ftilliet          #+#    #+#             */
/*   Updated: 2023/12/20 16:42:42 by florian          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_BONUS_H
# define GET_NEXT_LINE_BONUS_H

# include <stdlib.h>
# include <unistd.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 50
# endif

# ifndef FD_MAX
#  define FD_MAX 1024
# endif

size_t	gnl_strlen(char *str);
char	*gnl_strjoin(char *s1, char *s2);
int		new_line(char *str);
char	*clean(char *str);
char	*get_new_line(char *str);
char	*get_next_line(int fd);
char	*just_new_line(char *line);
void	return_new_line(char **line, char **temp, char **stash);
void	copy_until_new_line(char **line, char **str, int *i);

#endif