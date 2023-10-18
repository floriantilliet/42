/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_libr.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: udumas <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/27 14:34:30 by udumas            #+#    #+#             */
/*   Updated: 2023/09/27 15:02:38 by udumas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_LIBR_H
# define FT_LIBR_H
# include <fcntl.h>
# include <stdlib.h>
# include <unistd.h>
# define TEST 1050624

typedef struct s_coord
{
	int	x;
	int	y;
	int	max;
}			t_coord;

int				ft_strlen(char *str);
int				ft_linelen(char *str);
char			*take_sep(char *map);
int				check_first_line(char *map);
int				check_line2(char *map, char *sepz);
int				ft_open(char *path);
void			clean_str(char *str);
char			*ft_read(const char *path);
char			*ft_update_res(char *s1, char *s2);
int				get_cell_value(char c, char *str);
int				**def_matrix(int line_len, int linelen);
int				**get_matrix(int **tab, char *str, char *charset, int line_len);
void			print_matrix(int **tab, int line_len, int linelen);
int				get_min(int left, int diagonal, int up);
int				**solve(int **input_tab, int line_len, int col_len);
struct	s_coord	get_bsq(int **map, int line_len, int col_len);
char			*bsq(char *str, t_coord coord, char *charset, int line_len);
void			get_and_solve(char *str);
int				check_correcrow(char *map);
int				skip_fline(char *str);
void			ft_putstr(char *str);
void			ft_putstr2(char *str, int line_len, int col_len);
void			ft_print_error(void);
int				maperror(char *map);
int				ft_strlen(char *str);
int				ft_linelen(char *str);
int				**get_matrix(int **tab, char *str, char *charset, int line_len);
int				**def_matrix(int line_len, int col_len);
void			free_matrix(int **map, int col_len);
void			clean_str(char *str);
char			*ft_stdin(void);

#endif
