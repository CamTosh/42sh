/*
** zsh.c for  in /home/alif_m/tek1/PSU/PSU_2015_42sh/srcs/ncurse
**
** Made by ALIF Matthias
** Login   <alif_m@epitech.net>
**
** Started on  Thu Jun 02 14:45:30 2016 ALIF Matthias
** Last update Sun Jun  5 16:17:16 2016 Guillaume Benard
*/

#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <ncurses.h>
#include <sys/types.h>
#include <sys/ioctl.h>
#include "kala.h"

int	get_actual_pos(t_shell *shell)
{
  char	buff[3];
  char	trash[12];
  int	i;

  i = 0;
  my_dprintf(1, "%s\n", shell->key.pos);
  if (read(0, buff, 2) < 2)
    return (1);
  buff[0] = 0;
  if (read(0, buff, 2) < 2)
    return (1);
  buff[1] = !buff[1] || buff[1] < '0' || buff[1] > '9' ? 0 : buff[1];
  read(0, trash, 12);
  buff[2] = '\0';
  return (my_getnbr(buff, &i) == FALSE ? 0 : i);
}

static int	count_char(t_com *com)
{
  t_cmd		*tmp;
  int		ret;

  ret = 0;
  tmp = com->cmd_l;
  while (tmp)
    {
      ret += strlen(tmp->str) + (strlen(tmp->str) % 8);
      tmp = tmp->next;
    }
  return (ret);
}

static void		check_pos(t_shell *shell)
{
  int			y;
  int			cc;
  struct winsize	ws;

  ioctl(1, TIOCGWINSZ, &ws);
  y = -1;
  cc = (count_char(&shell->com) / ws.ws_col);
  while (++y < cc)
    my_dprintf(1, "\n");
  gotoyx(shell, get_actual_pos(shell) - (1 + y), 0);
}

void	aff_cmpl(t_shell *shell)
{
  t_cmd	*tmp;

  tmp = shell->com.cmd_l;
  check_pos(shell);
  shell->com.y[0] = get_actual_pos(shell);
  while (tmp)
    {
      if (tmp == shell->com.cursor)
	my_dprintf(1, PINK"%s"RES"\t", tmp->str);
      else
	my_dprintf(1, "%s\t", tmp->str);
      tmp = tmp->next;
    }
  shell->com.y[1] = get_actual_pos(shell);
  gotoyx(shell, get_actual_pos(shell) + (shell->com.y[0]
					 - get_actual_pos(shell)), 0);
}
