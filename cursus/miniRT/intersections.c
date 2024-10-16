/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersections.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: florian <florian@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/12 15:09:11 by florian           #+#    #+#             */
/*   Updated: 2024/10/16 19:29:26 by florian          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include.h"

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

void insertArray(t_array *a, float element)
{
  // a->used is the number of used entries, because a->array[a->used++] updates a->used only *after* the array has been accessed.
  // Therefore a->used can go up to a->size 
  if (a->used == a->size) {
    a->size *= 2;
    a->array = realloc(a->array, a->size * sizeof(float));
  }
  a->array[a->used++] = element;
}

void freeArray(t_array *a)
{
  free(a->array);
  a->array = NULL;
  a->used = a->size = 0;
}

void printArray(t_array *a)
{
  for (size_t i = 0; i < a->used; i++)
	printf("%f\n", a->array[i]);
}

float hitArray(t_array *a)
{
  if (a->array[a->used - 2] >= 0 && a->array[a->used - 1])
    return(fmin(a->array[a->used - 2], a->array[a->used - 1]));
  else if (a->array[a->used - 2] >= 0)
    return (a->array[a->used - 2]);
  else if (a->array[a->used - 1] >= 0)
    return (a->array[a->used - 1]);
  else
    return (-1); 
}