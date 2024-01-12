/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   operations.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ftilliet <ftilliet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/11 14:39:50 by ftilliet          #+#    #+#             */
/*   Updated: 2024/01/12 14:42:48 by ftilliet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	ft_putchar_fd(char c, int fd)
{
	write(fd, &c, 1);
}

void	ft_putendl_fd(char *str, int fd)
{
	if (fd != -1 && str != NULL)
	{
		while (*str != '\0')
		{
			ft_putchar_fd(*str, fd);
			str++;
		}
		ft_putchar_fd('\n', fd);
	}
}


void	swap(t_stack_node **head)
{
	t_stack_node	*tmp;

	if (*head && (*head)->next)
	{
		tmp = (*head)->next;
		(*head)->next = tmp->next;
		(*head)->prev = tmp;
		tmp->next = *head;
		tmp->prev = NULL;
		*head = tmp;
	}
}

void sa(t_stack_node **head)
{
    swap(head);
    ft_putendl_fd("sa", 1);
}

void sb(t_stack_node **head)
{
    swap(head);
    ft_putendl_fd("sb", 1);
}

void ss(t_stack_node **head, t_stack_node **head_b)
{
    swap(head);
    swap(head_b);
    ft_putendl_fd("ss", 1);
}

void	push(t_stack_node **head, t_stack_node **head_b)
{
	t_stack_node	*tmp;

	if (*head)
	{
		tmp = (*head)->next;
		(*head)->next = *head_b;
		*head_b = *head;
		*head = tmp;
	}
}

void pa(t_stack_node **head, t_stack_node **head_b)
{
    push(head, head_b);
    ft_putendl_fd("pa", 1);
}

void pb(t_stack_node **head, t_stack_node **head_b)
{
    push(head_b, head);
    ft_putendl_fd("pb", 1);
}

void	rotate(t_stack_node **head)
{
	t_stack_node	*tmp;

	if (*head && (*head)->next)
	{
		tmp = *head;
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = *head;
		*head = (*head)->next;
		tmp->next->next = NULL;
		tmp->next->prev = tmp;
	}
}

void ra(t_stack_node **head)
{
    rotate(head);
    ft_putendl_fd("ra", 1);
}

void rb(t_stack_node **head)
{
    rotate(head);
    ft_putendl_fd("rb", 1);
}

void rr(t_stack_node **head, t_stack_node **head_b)
{
    rotate(head);
    rotate(head_b);
    ft_putendl_fd("rr", 1);
}

void reverse_rotate(t_stack_node **head)
{
    t_stack_node	*tmp;

    if (*head && (*head)->next)
    {
        tmp = *head;
        while (tmp->next)
            tmp = tmp->next;
        tmp->next = *head;
        tmp->prev->next = NULL;
        tmp->prev = NULL;
        *head = tmp;
    }
}

void rra(t_stack_node **head)
{
    reverse_rotate(head);
    ft_putendl_fd("rra", 1);
}

void rrb(t_stack_node **head)
{
    reverse_rotate(head);
    ft_putendl_fd("rrb", 1);
}

void rrr(t_stack_node **head, t_stack_node **head_b)
{
    reverse_rotate(head);
    reverse_rotate(head_b);
    ft_putendl_fd("rrr", 1);
}


#include <stdio.h>

// void print_stack(t_stack_node *head)
// {
//     while (head != NULL)
//     {
//         printf("%d ", head->value);
//         head = head->next;
//     }
//     printf("\n");
// }

// int main()
// {
//     t_stack_node *stack = NULL;
//     t_stack_node *stack_b = NULL;

//     // Ajouter des éléments à la pile
//     for (int i = 1; i <= 4; i++)
//     {
//         t_stack_node *new_node = malloc(sizeof(t_stack_node));
//         new_node->value = i;
//         new_node->next = stack;
//         new_node->prev = NULL;
//         if (stack)
//             stack->prev = new_node;
//         stack = new_node;
//     }

//     for (int i = 5; i <= 8; i++)
//     {
//         t_stack_node *new_node = malloc(sizeof(t_stack_node));
//         new_node->value = i;
//         new_node->next = stack_b;
//         new_node->prev = NULL;
//         if (stack_b)
//             stack_b->prev = new_node;
//         stack_b = new_node;
//     }

//     // Tester la fonction swap
//     printf("Avant swap:\n");
//     // Afficher la pile avant l'appel à la fonction swap
//     print_stack(stack);
//     swap(&stack);
//     printf("Après swap:\n");
//     // Afficher la pile après l'appel à la fonction swap
//     print_stack(stack);

//     // Tester la fonction push
//     printf("Avant push:\n");
//     // Afficher la pile A et la pile B avant l'appel à la fonction push
//     print_stack(stack);
//     print_stack(stack_b);
//     push(&stack, &stack_b);
//     printf("Après push:\n");
//     // Afficher la pile A et la pile B après l'appel à la fonction push
//     print_stack(stack);
//     print_stack(stack_b);

//     // Tester la fonction rotate
//     printf("Avant rotate:\n");
//     // Afficher la pile avant l'appel à la fonction rotate
//     print_stack(stack);

//     rotate(&stack);
//     printf("Après rotate:\n");
//     // Afficher la pile après l'appel à la fonction rotate
//     print_stack(stack);

//     return (0);
// }
