/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: florian <florian@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/11 14:18:53 by ftilliet          #+#    #+#             */
/*   Updated: 2024/01/23 13:18:57 by florian          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PUSH_SWAP_H
# define PUSH_SWAP_H
# include "libft/libft.h"
# include <stdlib.h>
# include <unistd.h>

typedef struct s_stack_node
{
	int					value;
	int					index;
	struct s_stack_node	*next;
	struct s_stack_node	*prev;
}						t_stack_node;

void					swap(t_stack_node **head);
void					push(t_stack_node **head, t_stack_node **head_b);
void					rotate(t_stack_node **head);
void					reverse_rotate(t_stack_node **head);
void					sa(t_stack_node **head);
void					sb(t_stack_node **head);
void					ss(t_stack_node **head, t_stack_node **head_b);
void					pa(t_stack_node **head, t_stack_node **head_b);
void					pb(t_stack_node **head, t_stack_node **head_b);
void					ra(t_stack_node **head);
void					rb(t_stack_node **head);
void					rr(t_stack_node **head, t_stack_node **head_b);
void					rra(t_stack_node **head);
void					rrb(t_stack_node **head);
void					rrr(t_stack_node **head, t_stack_node **head_b);
void					radix_sort(t_stack_node **stackA,
							t_stack_node **stackB);
void					assign_indexes(t_stack_node *head);
int						ft_double_lstsize(t_stack_node *lst);
t_stack_node			*ft_double_lstnew(int content);
void					ft_double_lstadd_back(t_stack_node **head,
							t_stack_node *new);
t_stack_node			*ft_double_lstlast(t_stack_node *lst);
void					ft_double_lstadd_front(t_stack_node **head,
							t_stack_node *new);
void					sort_stack(t_stack_node **stack_A,
							t_stack_node **stack_B);
void					sort_two(t_stack_node **stack_A);
void					sort_three(t_stack_node **stack_A);
void					special_case_one(t_stack_node **stack_A);
void					special_case_two(t_stack_node **stack_A);
int						check_args(int ac, char **av);
void					sort_five(t_stack_node **stack_A,
							t_stack_node **stack_B);
void					sort_four(t_stack_node **stack_A,
							t_stack_node **stack_B);
int						get_distance(t_stack_node **stack, int val);
int						get_min(t_stack_node **stack, int val);
void					init_stack(t_stack_node **stack, int ac, char **av);
void					free_stack(t_stack_node **stack);
void					free_tab(char **tab);
int						is_stack_sorted(t_stack_node **head);

#endif