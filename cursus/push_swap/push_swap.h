/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ftilliet <ftilliet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/11 14:18:53 by ftilliet          #+#    #+#             */
/*   Updated: 2024/01/11 17:10:04 by ftilliet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PUSH_SWAP_H
# define PUSH_SWAP_H
# include <stdlib.h>


typedef struct s_stack_node
{
    int						value;
    struct s_stack_node		*next;
    struct s_stack_node		*prev;
}							t_stack_node;

#endif