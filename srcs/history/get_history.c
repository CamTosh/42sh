/*
** get_history.c for get in /home/said_p/Work/PSU_2015_42sh/srcs/history
**
** Made by pierre said
** Login   <said_p@epitech.net>
**
** Started on  Fri Jun  3 21:43:50 2016 pierre said
** Last update Fri Jun 10 17:40:08 2016 Iulian Rotaru
*/

#include <string.h>
#include "kala.h"

char		*get_history(t_history *hist,
			     t_bool mode, t_shell *sh)
{
  if (mode == 0)
    {
      if (!sh->last_hist)
	{
	  sh->last_hist = hist;
	  return (hist->cmd);
	}
      else if (sh->last_hist->next)
	{
	  sh->last_hist = sh->last_hist->next;
	  return (sh->last_hist->cmd);
	}
    }
  else if (mode == 1 && sh->last_hist)
    {
      if (!sh->last_hist->prev)
	return ((char *)(sh->last_hist = NULL));
      else
	{
	  sh->last_hist = sh->last_hist->prev;
	  return (sh->last_hist->cmd);
	}
    }
  return (NULL);
}
