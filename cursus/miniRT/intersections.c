/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersections.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: florian <florian@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/12 15:09:11 by florian           #+#    #+#             */
/*   Updated: 2024/10/16 09:18:00 by florian          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include.h"

float *init_intersections(void)
{
    return NULL;
}

float *add_intersection(float *intersections, float t)
{
    float *new_intersections;
    int current_size = 0;

    if (intersections != NULL)
    {
        while (intersections[current_size] != -1.0f)
            current_size++;
    }

    new_intersections = realloc(intersections, sizeof(float) * (current_size + 1 + 1)); // Add space for the new value and a new terminator
    if (!new_intersections)
        return intersections; // Return old array if reallocation fails

    new_intersections[current_size] = t;
    new_intersections[current_size + 1] = -1.0f; // Update the terminator
    return new_intersections;
}

void free_intersections(float *intersections)
{
    free(intersections);
}

void print_intersections(float *intersections)
{
    int i = 0;
    if (intersections == NULL)
    {
        return;
    }
    while (intersections[i] != -1.0f)
    {
        printf("t: %f\n", intersections[i]);
        i++;
    }
}

float hit(float *intersections)
{
    float min = -1.0f;
    int i = 0;

    if (intersections == NULL)
        return min;

    while (intersections[i] != -1.0f)
    {
        if (intersections[i] > 0 && (min == -1.0f || intersections[i] < min))
        {
            min = intersections[i];
        }
        i++;
    }
    return min;
}

t_array *initArray(size_t initialSize)
{
  t_array *a = malloc(sizeof(t_array));
  if (a == NULL)
    return NULL;
  a->array = malloc(initialSize * sizeof(float));
  if (a->array == NULL)
  {
    free(a);
    return NULL;
  }
  a->used = 0;
  a->size = initialSize;
  return a;
}

void insertArray(t_array *a, float element) {
  // a->used is the number of used entries, because a->array[a->used++] updates a->used only *after* the array has been accessed.
  // Therefore a->used can go up to a->size 
  if (a->used == a->size) {
    a->size *= 2;
    a->array = realloc(a->array, a->size * sizeof(float));
  }
  a->array[a->used++] = element;
}

void freeArray(t_array *a) {
  free(a->array);
  a->array = NULL;
  a->used = a->size = 0;
}

void printArray(t_array *a) {
  for (size_t i = 0; i < a->used; i++)
	printf("%f\n", a->array[i]);
}

float hitArray(t_array *a) {
	float min = -1.0f;
	size_t i = 0;

	if (a->array == NULL)
		return min;

	while (i < a->used)
	{
		if (a->array[i] > 0 && (min == -1.0f || a->array[i] < min))
		{
			min = a->array[i];
		}
		i++;
	}
	return min;
}