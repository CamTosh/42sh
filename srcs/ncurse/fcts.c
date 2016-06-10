/*
** fcts.c for sepojfseifjapodjaw in /home/alif_m/tek1/PSU/PSU_2015_42sh
**
** Made by Alif Matthias
** Login   <alif_m@epitech.net>
**
** Started on  Mon May 30 18:04:47 2016 Alif Matthias
** Last update Fri Jun 10 17:41:47 2016 Iulian Rotaru
*/

#include <string.h>
#include "kala.h"

int	down(t_shell *shell, char *buff, int *i)
{
  if (shell->com.on == FALSE)
    {
      shell->history_on = TRUE;
      if (!(shell->bufist =
	    get_history(shell->hist, 1, shell)))
	{
	  bzero(buff, sizeof(char) * BUFF_SIZE);
	  *i = 0;
	  i[1] = 0;
	  shell->history_on = FALSE;
	}
      else
	{
	  strncpy(buff, shell->bufist, BUFF_SIZE);
	  *i = strlen(buff) - 1;
	  i[1] = strlen(buff);
	}
    }
  return (0);
}

int	del(t_shell *shell, char *buff, int *i)
{
  int	idx;

  if (*i >= 0)
    idx = --*i;
  else
    return (0);
  while (++idx < i[1] && buff[idx])
    buff[idx] = buff[idx + 1];
  buff[idx] = '\0';
  i[1] = strlen(buff);
  if (i[1] > 0)
    --i[1];
  shell->com.on = FALSE;
  return (0);
}

int	backspace(t_shell *shell, char *buff, int *i)
{
  (void)shell;
  (void)buff;
  (void)i;
  return (0);
}

int	end(t_shell *shell, char *buff, int *i)
{
  (void)shell;
  (void)buff;
  *i = *(i + 1);
  return (0);
}

int	home(t_shell *shell, char *buff, int *i)
{
  (void)shell;
  (void)buff;
  *i = -1;
  return (0);
}
