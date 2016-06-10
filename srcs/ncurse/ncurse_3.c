/*
** ncurse_3.c for  in /home/tim/rendu/2_semestre/system_unix/42sh/PSU_2015_42sh
**
** Made by almazo_t
** Login   <tim@epitech.net>
**
** Started on  Sun Jun  5 03:36:53 2016 almazo_t
** Last update Sun Jun  5 19:55:35 2016 Alif Matthias
*/

#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/ioctl.h>
#include "kala.h"

static void	add_to_buff(char *buff, int *i, char c)
{
  int		idx[2];

  *idx = 0;
  while (buff[*idx] && *idx <= *i)
    ++*idx;
  idx[1] = i[1] + 1;
  while (--idx[1] > *idx && idx[1] > 0)
    buff[idx[1]] = buff[idx[1] - 1];
  buff[*idx] = c;
  ++*i;
}

static void	aff_curs(char c)
{
  write(1, "\033[5;47;33m", strlen("\033[5;47;33m"));
  write(1, &c, 1);
  write(1, "\033[m", strlen("\033[m"));
}

void	aff_prompt(t_shell *shell)
{
  my_dprintf(2, "\033[1;%dm|%c| \033[1;31mKalaSH \033[1;%dm>\033[0m ",
	     shell->rando, shell->exit.status != EXIT_SUCCESS
	     ? '!' : 'o', shell->rando);
}

void			print_buff(t_shell *shell, char *buff, int *curs_pos)
{
  int			i;
  struct winsize	ws;
  int			printed;

  printed = 0;
  i = -1;
  write(1, "\r", 1);
  ioctl(1, TIOCGWINSZ, &ws);
  while (++i < ws.ws_col && i < BUFF_SIZE)
    write(1, " ", 1);
  write(1, "\r", 1);
  aff_prompt(shell);
  i = -1;
  while (buff[++i])
    {
      if (i == *curs_pos + 1)
	{
	  aff_curs(buff[i]);
	  printed = 1;
	}
      else
	write(1, &buff[i], 1);
    }
  if (printed == 0)
    aff_curs(' ');
}

void	process_keys(t_shell *shell, int *i, char *c, char *buff)
{
  if (*c >= ' ' && *c < 127)
    {
      add_to_buff(buff, i, *c);
      shell->history_on = FALSE;
      buff[i[1] + 1] = '\0';
      ++i[1];
      shell->com.on = FALSE;
    }
  else
    may_act(shell, buff, i, c);
}
