/*
** write_history.c for write in /home/said_p/Work/PSU_2015_42sh/srcs/history
**
** Made by pierre said
** Login   <said_p@epitech.net>
**
** Started on  Fri Jun  3 20:50:12 2016 pierre said
** Last update Sun Jun  5 13:52:55 2016 pierre said
*/

#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include "kala.h"

static t_history	*get_last_hist(t_history *hist)
{
  t_history		*ptr;

  ptr = hist;
  while (ptr->next)
    ptr = ptr->next;
  return (ptr);
}

static void	save_history(t_history *hist, int fd)
{
  t_history	*ptr;

  ptr = get_last_hist(hist);
  while (ptr)
    {
      if (ptr->cmd[0] != 0)
	{
	  write(fd, ptr->cmd, strlen(ptr->cmd));
	  write(fd, "\n", 1);
	}
      ptr = ptr->prev;
    }
}

t_bool	write_history(t_history *hist)
{
  int	fd;

  if (hist == NULL)
    return (TRUE);
  if ((fd = open(HISTORY_FILE, O_CREAT | O_RDWR | O_TRUNC, 00644)) < 0)
    return (FALSE);
  save_history(hist, fd);
  close(fd);
  return (TRUE);
}
