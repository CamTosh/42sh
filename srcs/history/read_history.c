/*
** read_history.c for read_history in /home/said_p/Work/PSU_2015_42sh
**
** Made by pierre said
** Login   <said_p@epitech.net>
**
** Started on  Fri Jun  3 18:36:17 2016 pierre said
** Last update Sun Jun  5 22:05:49 2016 ROTARU Iulian
*/

#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include "kala.h"
#include "utils.h"

void		free_history(t_history **history)
{
  t_history	*ptr;
  t_history	*ptr_free;

  ptr = *history;
  while (ptr)
    {
      ptr_free = ptr;
      ptr = ptr->next;
      free(ptr_free->cmd);
      free(ptr_free);
    }
}

t_bool		add_in_hist(t_history **hist, char *cmd)
{
  t_history	*node;

  if (cmd == NULL || cmd[0] == '\n'
      || (*hist != NULL && strcmp((*hist)->cmd, cmd) == 0))
    return (TRUE);
  if ((node = malloc(sizeof(t_history))) == NULL)
    return (FALSE);
  node->cmd = cmd;
  node->next = NULL;
  node->prev = NULL;
  node->next = *hist;
  if (*hist)
    (*hist)->prev = node;
  *hist = node;
  return (TRUE);
}

static t_bool	read_history(t_history **hist, int fd)
{
  char		*s;

  while ((s = get_next_line(fd)) != NULL)
    {
      if (add_in_hist(hist, s) == FALSE)
	return (FALSE);
    }
  return (TRUE);
}

t_history	*create_history()
{
  int		fd;
  t_history	*hist;

  hist = NULL;
  if ((fd = open(HISTORY_FILE, O_RDONLY)) == -1)
    return (NULL);
  if (read_history(&hist, fd) == FALSE)
    {
      close(fd);
      return (NULL);
    }
  close(fd);
  return (hist);
}
