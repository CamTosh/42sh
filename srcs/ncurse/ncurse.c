/*
** ncurse.c for KalaSH in /home/guillaume/Documents/rendu/42sh/PSU_2015_42sh
**
** Made by Guillaume Benard
** Login   <guillaume@epitech.net>
**
** Started on  Mon May 30 14:27:08 2016 Guillaume Benard
** Last update Mon Jun  6 00:05:30 2016 almazo_t
*/

#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <term.h>
#include <sys/ioctl.h>
#include <ncurses.h>
#include <unistd.h>
#include "kala.h"
#include "utils.h"

static const char	g_del[] = {
  127,
  '\0'
};

static const t_ncu	g_fct[] = {
  {"\t", tabu},
  {NULL, left},
  {NULL, right},
  {NULL, down},
  {NULL, up},
  {g_del, del},
  {"\b", backspace},
  {NULL, end},
  {NULL, home},
};

void		may_act(t_shell *shell, char *buff, int *i, char *c)
{
  int		y;
  const char	*str;

  y = -1;
  while (++y < (int)(sizeof(g_fct) / sizeof(t_ncu)))
    {
      if (y != 0 && y != 5 && y != 6)
	str = ((char **)(&shell->key))[y];
      else
	str = g_fct[y].key;
      if (str && (strncmp(str, c, strlen(str))) == MATCH)
	{
	  g_fct[y].fct(shell, buff, i);
	  break ;
	}
    }
  if (y != 4 && y != 3)
    shell->history_on = FALSE;
}

static void	clear_aff(t_shell *shell)
{
  int		tmp;

  tmp = shell->com.y[0] - 1;
  while (tmp < shell->com.y[1])
    {
      my_dprintf(1, "%s\n", shell->key.clr_line);
      ++tmp;
    }
  my_dprintf(1, "%c[%d;%df\n", 0x1B, shell->com.y[0] - 1, 0);
}

static void	aff_defin(t_shell *shell, const char *buff)
{
  write(1, "\r", 1);
  aff_prompt(shell);
  write(1, buff, strlen(buff));
  write(1, " ", 1);
}

t_bool	complete_part(t_shell *shell, char *buff, int *i, char *c)
{
  if (shell->history_on == FALSE
      && shell->com.on == TRUE && shell->com.cursor->str)
    i[3] = strlen(shell->com.cursor->str);
  if (*c == '\n'&& shell->com.on == TRUE && shell->com.cursor)
    {
      shell->com.on = FALSE;
      *i = strlen(buff) - 1;
      clear_aff(shell);
      i[1] = strlen(buff);
      delete_list(&shell->com);
    }
  else if (shell->com.on == TRUE && *c >= ' ' && *c < 127)
    {
      shell->com.on = FALSE;
      clear_aff(shell);
    }
  else if (*c == '\n')
    {
      aff_defin(shell, buff);
      return (FALSE);
    }
  return (TRUE);
}

void	gotoyx(t_shell *shell, int y, int x)
{
  if (y <= 0)
    y = get_actual_pos(shell);
  my_dprintf(1, "\033[%d;%df\n", y, x);
}
