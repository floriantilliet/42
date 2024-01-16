/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ftilliet <ftilliet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/11 14:18:53 by ftilliet          #+#    #+#             */
/*   Updated: 2024/01/16 17:54:42 by ftilliet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PUSH_SWAP_H
# define PUSH_SWAP_H
# include <stdlib.h>
# include <unistd.h>
# include "libft/libft.h"

typedef struct s_stack_node
{
    int						value;
    int                     index;
    struct s_stack_node		*next;
    struct s_stack_node		*prev;
}							t_stack_node;

void	swap(t_stack_node **head);
void	push(t_stack_node **head, t_stack_node **head_b);
void	rotate(t_stack_node **head);
void	reverse_rotate(t_stack_node **head);
void	sa(t_stack_node **head);
void	sb(t_stack_node **head);
void	ss(t_stack_node **head, t_stack_node **head_b);
void	pa(t_stack_node **head, t_stack_node **head_b);
void	pb(t_stack_node **head, t_stack_node **head_b);
void	ra(t_stack_node **head);
void	rb(t_stack_node **head);
void	rr(t_stack_node **head, t_stack_node **head_b);
void	rra(t_stack_node **head);
void	rrb(t_stack_node **head);
void	rrr(t_stack_node **head, t_stack_node **head_b);
void	radix_sort(t_stack_node **stackA, t_stack_node **stackB);
void	assign_indexes(t_stack_node *head);
int		ft_double_lstsize(t_stack_node *lst);

#endif