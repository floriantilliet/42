/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ftilliet <ftilliet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/27 12:32:45 by ftilliet          #+#    #+#             */
/*   Updated: 2023/11/27 16:45:41 by ftilliet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <stdlib.h>
# include <unistd.h>

# define BUFFER_SIZE 1

size_t	ft_strlen(char *str);
char	*ft_strjoin(char *s1, char *s2);
int		new_line(char *str);
char	*clean(char *str);
char	*get_new_line(char *str);
char	*get_next_line(int fd);

#endif