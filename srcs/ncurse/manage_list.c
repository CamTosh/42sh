/*
** manage_list.c for # in /home/tim/rendu/2_semestre/system_unix/42sh/PSU_2015_42sh/srcs/ncurse
**
** Made by almazo_t
** Login   <tim@epitech.net>
**
** Started on  Wed Jun  1 17:20:20 2016 almazo_t
** Last update Sun Jun  5 23:57:25 2016 almazo_t
*/

#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <sys/ioctl.h>
#include <sys/types.h>
#include "kala.h"

void	delete_list(t_com *com)
{
  t_cmd	*tmp;
  t_cmd	*cursor;

  cursor = com->cmd_l;
  while (cursor != NULL)
    {
      tmp = cursor;
      cursor = cursor->next;
      if (tmp && tmp->str)
	{
	  free((void *)tmp->str);
	  free(tmp);
	}
    }
  free(cursor);
  com->cmd_l = NULL;
  com->cursor = com->cmd_l;
}

int	tabu(t_shell *shell, char *buff, int *i)
{
  *i = strlen(buff);
  if (shell->com.on == TRUE && shell->com.cursor)
    shell->com.cursor = (shell->com.cursor->next) ? shell->com.cursor->next :
      shell->com.cmd_l;
  else
    completion(shell, buff, *i);
  if (shell->com.cmd_l)
    shell->com.on = TRUE;
  return (0);
}

t_bool	creat_list(t_com *com, const char *str)
{
  t_cmd	*tmp;
  t_cmd	*new;

  tmp = com->cmd_l;
  if ((new = malloc(sizeof(t_cmd))) == NULL)
    return (FALSE);
  new->str = str;
  new->next = NULL;
  new->prev = NULL;
  if (tmp == NULL)
    com->cmd_l = new;
  else
    {
      while (tmp->next != NULL)
	tmp = tmp->next;
      new->prev = tmp;
      tmp->next = new;
    }
  return (TRUE);
}

void			mv_curs(t_shell *shell, int *i, char *buff)
{
  struct winsize	ws;

  ioctl(1, TIOCGWINSZ, &ws);
  shell->com.st = get_actual_pos(shell);
  shell->rando = rand() % 6 + 30;
  i[4] = (16 + strlen(buff)) / ws.ws_col;
  if (shell->com.st >= ws.ws_row - 1)
    gotoyx(shell, 1, 0);
  else
    gotoyx(shell, shell->com.st - i[4] - 1, 0);
  write(1, shell->key.clr, strlen(shell->key.clr));
}
