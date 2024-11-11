/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersections.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: florian <florian@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/12 15:09:11 by florian           #+#    #+#             */
/*   Updated: 2024/11/11 21:55:21 by florian          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include.h"

t_array *init_array(size_t initialSize)
{
  t_array *a = malloc(sizeof(t_array));
  if (a == NULL)
    return NULL;
  a->array = malloc(initialSize * sizeof(t_intersection));
  if (a->array == NULL)
  {
    free(a);
    return NULL;
  }
  a->used = 0;
  a->size = initialSize;
  return a;
}

void insert_array(t_array *a, double element, t_objects *object)
{
  // a->used is the number of used entries, because a->array[a->used++] updates a->used only *after* the array has been accessed.
  // Therefore a->used can go up to a->size 
  if (a->used == a->size) {
    a->size *= 2;
    a->array = realloc(a->array, a->size * sizeof(t_intersection));
  }
  a->array[a->used++].t = element;
  a->array[a->used - 1].object = object;
}

void free_array(t_array *a)
{
  free(a->array);
  a->array = NULL;
  a->used = a->size = 0;
}

t_array *concatenate_array(t_array *a, t_array *b)
{
  size_t i;
  t_array *new_array;

  new_array = init_array(a->size + b->size);
  i = 0;
  while (i < a->used)
  {
    insert_array(new_array, a->array[i].t, a->array[i].object);
    i++;
  }
  i = 0;
  while (i < b->used)
  {
    insert_array(new_array, b->array[i].t, b->array[i].object);
    i++;
  }
  free_array(a);
  free_array(b);
  return (new_array);
}

void sort_array(t_array *a)
{
  size_t i;
  size_t j;
  t_intersection temp;

  i = 0;
  while (i < a->used)
  {
    j = i + 1;
    while (j < a->used)
    {
      if (a->array[i].t > a->array[j].t)
      {
        temp = a->array[i];
        a->array[i] = a->array[j];
        a->array[j] = temp;
      }
      j++;
    }
    i++;
  }
}

void print_array(t_array *a)
{
  for (size_t i = 0; i < a->used; i++)
  {
  	printf("%f\n", a->array[i].t);
  }
}

double hit_array(t_array *a)
{
  double min = -1;
  size_t i = 0;
  if (a == NULL)
    return -1;
  while (i < a->used)
  {
    if (a->array[i].t >= 0 && (min == -1 || a->array[i].t < min))
    {
      min = a->array[i].t;
    }
    i++;
  }
  return min;
}

int hit_index(t_array *a, double t)
{
  size_t i = 0;
  while (i < a->used)
  {
    if (a->array[i].t == t)
      return i;
    i++;
  }
  return -1;
}
