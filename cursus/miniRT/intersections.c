/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersections.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: florian <florian@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/12 15:09:11 by florian           #+#    #+#             */
/*   Updated: 2024/10/18 14:21:05 by florian          ###   ########.fr       */
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

t_array concatenateArray(t_array *a, t_array *b)
{
  size_t i;
  t_array new_array;

  new_array = *initArray(a->size + b->size);
  i = 0;
  while (i < a->used)
  {
    insertArray(&new_array, a->array[i]);
    i++;
  }
  i = 0;
  while (i < b->used)
  {
    insertArray(&new_array, b->array[i]);
    i++;
  }
  freeArray(a);
  freeArray(b);
  return (new_array);
}

void printArray(t_array *a)
{
  for (size_t i = 0; i < a->used; i++)
	printf("%f\n", a->array[i]);
}

float hitArray(t_array *a)
{
  float min = -1;
  size_t i = 0;
  if (a == NULL)
    return -1;
  while (i < a->used)
  {
    if (a->array[i] >= 0 && (min == -1 || a->array[i] < min))
    {
      min = a->array[i];
    }
    i++;
  }
  return min;
}

