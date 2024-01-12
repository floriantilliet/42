/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ftilliet <ftilliet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/11 14:18:53 by ftilliet          #+#    #+#             */
/*   Updated: 2024/01/12 14:11:01 by ftilliet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PUSH_SWAP_H
# define PUSH_SWAP_H
# include <stdlib.h>


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

#endif