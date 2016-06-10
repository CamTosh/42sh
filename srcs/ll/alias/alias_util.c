/*
** alias_util.c for util in /home/said_p/Work/PSU_2015_42sh/srcs/alias
**
** Made by pierre said
** Login   <said_p@epitech.net>
**
** Started on  Sun Jun  5 01:09:44 2016 pierre said
** Last update Sun Jun  5 16:04:38 2016 Guillaume Benard
*/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "kala.h"

void		show_alias(t_alias *alias)
{
  t_alias	*ptr;

  ptr = alias;
  while (ptr != NULL)
    {
      my_dprintf(1, "%s\t(%s)\n", ptr->alias, ptr->input);
      ptr = ptr->next;
    }
}

void		free_alias(t_alias *list)
{
  t_alias	*ptr;
  t_alias	*to_free;

  ptr = list;
  while (ptr)
    {
      to_free = ptr;
      ptr = ptr->next;
      free(to_free->alias);
      free(to_free->input);
      free(to_free);
    }
}

int		add_alias(t_alias **list, char *alias, char *input)
{
  t_alias	*node;

  if ((node = malloc(sizeof(t_alias))) == NULL)
    return (-1);
  node->prev = NULL;
  node->next = NULL;
  node->replaced = FALSE;
  if ((node->alias = strdup(alias)) == NULL ||
      (node->input = strdup(input)) == NULL)
    return (-1);
  if (*list == NULL)
    *list = node;
  else
    {
      (*list)->prev = node;
      node->next = *list;
      *list = node;
    }
  return (0);
}
