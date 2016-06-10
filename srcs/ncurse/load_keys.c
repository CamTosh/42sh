/*
** load_keys.c for  in /home/tim/rendu/2_semestre/system_unix/42sh/PSU_2015_42sh/srcs/ncurse
**
** Made by almazo_t
** Login   <tim@epitech.net>
**
** Started on  Tue May 31 17:28:10 2016 almazo_t
** Last update Sun Jun 05 14:04:43 2016 ALIF Matthias
*/

#include <unistd.h>
#include <term.h>
#include <stdlib.h>
#include <ncurses.h>
#include <string.h>
#include "kala.h"
#include "utils.h"

static const char	*my_getpath(const char *were, const char *search)
{
  int			i;

  i = 0;
  while (search[i] == were[i])
    i++;
  if (search[i] == '\0')
    return (were);
  return (NULL);
}

const char	*my_search_env(char *const tab_env[], const char *str)
{
  int		i;
  const char	*s;

  i = 0;
  while (tab_env[i] != NULL)
    {
      if ((s = my_getpath(tab_env[i], str)) != NULL)
	{
	  s = &s[strlen(str) + 1];
	  return (s);
	}
      i++;
    }
  return (NULL);
}

static t_bool	search_keys(t_shell *data)
{
  if ((data->key.top = tigetstr("kcuu1")) == NULL
      || (data->key.right = tigetstr("kcuf1")) == NULL
      || (data->key.left = tigetstr("kcub1")) == NULL
      || (data->key.bottom = tigetstr("kcud1")) == NULL
      || (data->key.nocurs = tigetstr("civis")) == NULL
      || (data->key.curs = tigetstr("cnorm")) == NULL
      || (data->key.pos = tigetstr("u7")) == NULL
      || (data->key.clr_line = tigetstr("el")) == NULL
      || (data->key.end = tigetstr("kend")) == NULL
      || (data->key.home = tigetstr("home")) == NULL
      || (data->key.clear = tigetstr("clear")) == NULL
      || (data->key.clr = tigetstr("ed")) == NULL)
    return (FALSE);
  data->key.tabu = "\t";
  return (TRUE);
}

t_bool		load_keys(t_shell *shell, char *const env[])
{
  const char	*terminal;
  int		err;
  char		*csl_on;

  if ((terminal = my_getenv("TERM", env)) == NULL
      || setupterm(terminal, 1, &err) == ERR)
    return (FALSE);
  if ((csl_on = tigetstr("smkx")) == NULL)
    return (FALSE);
  write(1, csl_on, strlen(csl_on));
  return (search_keys(shell));
}
