/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersections.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: florian <florian@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/12 15:09:11 by florian           #+#    #+#             */
/*   Updated: 2024/10/13 00:45:41 by florian          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include.h"

t_intersections	**init_intersections(void)
{
	t_intersections	**intersections;

	intersections = malloc(sizeof(t_intersections *));
	if (!intersections)
		return (NULL);
	*intersections = NULL;
	return (intersections);
}

t_intersections	*create_intersection(float t)
{
	t_intersections	*new_intersection;

	new_intersection = malloc(sizeof(t_intersections));
	if (!new_intersection)
		return (NULL);
	new_intersection->t = t;
	return (new_intersection);
}

void	add_intersection(t_intersections **intersections, t_intersections *new_intersection)
{
	t_intersections    *current;

	if (*intersections == NULL)
		*intersections = new_intersection;
	else
	{
		current = *intersections;
		while (current->next != NULL)
			current = current->next;
		current->next = new_intersection;
	}
}

void free_intersections(t_intersections **intersections)
{
    t_intersections *current;
    t_intersections *next;

    current = *intersections;
    while (current)
    {
        next = current->next;
        free(current);
        current = next;
    }
    *intersections = NULL;
}

void print_intersections(t_intersections **intersections)
{
    t_intersections *current;

    current = *intersections;
    while (current)
    {
        printf("t: %f\n", current->t);
        current = current->next;
    }
}

float hit(t_intersections **intersections)
{
	t_intersections *current;
	float min;
	
	if (!intersections)
		return (-1);
	current = *intersections;
	min = current->t;
	while (current)
	{
		if (current->t < min && current->t > 0)
			min = current->t;
		current = current->next;
	}
	return (min);
}