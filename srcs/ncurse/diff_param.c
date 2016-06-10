/*
** diff_param.c for  in /home/tim/rendu/2_semestre/system_unix/42sh/PSU_2015_42sh/srcs/ncurse
**
** Made by almazo_t
** Login   <tim@epitech.net>
**
** Started on  Thu Jun  2 17:06:38 2016 almazo_t
** Last update Fri Jun 10 17:41:27 2016 Iulian Rotaru
*/

#include <string.h>
#include <stdlib.h>
#include "kala.h"

static int	check_ope(char c)
{
  char		*param;
  char		*func;
  int		i;

  i = -1;
  param = "<>";
  func = ";|&";
  while (param[++i])
    if (c == param[i])
      return (PAR);
  i = -1;
  while (func[++i])
    if (c == func[i])
      return (FUNC);
  return (0);
}

int	select_param(const char *str, int pos)
{
  int	i;

  i = pos;
  if (strlen(str) == 0)
    return (0);
  while (i > 0 && is_wrd(str[i]))
    --i;
  if (i <= 0)
    return (FUNC);
  else if (str[i - 1] && ((i - 1 >= 0 && str[i] == ' '
			   && check_ope(str[i - 1]) == FUNC)
			  ||(check_ope(str[i]) == FUNC)))
    return (FUNC);
  else if (str[i - 1] && ((i - 1 >= 0 && str[i] == ' '
			   && check_ope(str[i - 1]) == PAR)
			  || (check_ope(str[i]) == PAR)))
    return (PAR);
  return (PAR);
}

int	left(t_shell *shell, char *buff, int *i)
{
  (void)buff;
  if (shell->com.on == TRUE && shell->com.cursor)
    shell->com.cursor = (shell->com.cursor->prev) ? shell->com.cursor->prev :
      shell->com.cmd_l;
  else if (shell->com.on == FALSE)
    *i = *i >= 0 ? *i - 1 : *i;
  return (0);
}

int	right(t_shell *shell, char *buff, int *i)
{
  (void)buff;
  if (shell->com.on == TRUE && shell->com.cursor)
    shell->com.cursor = (shell->com.cursor->next) ? shell->com.cursor->next :
      shell->com.cmd_l;
  else if (shell->com.on == FALSE)
    *i = (*i < i[1]) ? (*i + 1) : *i;
  return (0);
}

int	up(t_shell *shell, char *buff, int *i)
{
  if (shell->com.on == FALSE)
    {
      shell->history_on = TRUE;
      if (!(shell->bufist =
	    get_history(shell->hist, 0, shell)))
	shell->history_on = FALSE;
      else
	{
	  strncpy(buff, shell->bufist, BUFF_SIZE);
	  *i = strlen(buff) - 1;
	  i[1] = strlen(buff);
	}
    }
  return (0);
}
