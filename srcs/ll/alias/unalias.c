/*
** unalias.c for unalias in /home/said_p
**
** Made by pierre said
** Login   <said_p@epitech.net>
**
** Started on  Sun Jun  5 01:53:32 2016 pierre said
** Last update Sun Jun  5 01:55:20 2016 pierre said
*/

#include <string.h>
#include <stdlib.h>
#include "kala.h"

void		unalias(t_alias **alias, const char *in)
{
  t_alias	*ptr;
  t_alias	*to_free;

  ptr = *alias;
  while (ptr)
    {
      if (strcmp(ptr->alias, in) == 0)
	{
	  to_free = ptr;
	  if (ptr->next != NULL)
	    ptr->next->prev = ptr->prev;
	  if (ptr->prev != NULL)
	    ptr->prev->next = ptr->next;
	  if (*alias == ptr)
	    *alias = ptr->next;
	  free(to_free->alias);
	  free(to_free->input);
	  free(to_free);
	  return ;
	}
      ptr = ptr->next;
    }
}
