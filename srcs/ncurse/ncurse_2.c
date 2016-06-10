/*
** ncurse_2.c for  in /home/tim/rendu/2_semestre/system_unix/42sh/PSU_2015_42sh
**
** Made by almazo_t
** Login   <tim@epitech.net>
**
** Started on  Sun Jun  5 03:25:50 2016 almazo_t
** Last update Sun Jun 05 17:01:12 2016 ALIF Matthias
*/

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/ioctl.h>
#include "kala.h"

static void	aff_cmd(t_shell *shell, char *buff, int *i)
{
  if (shell->com.on == TRUE && shell->com.cursor)
    {
      put_in_buff(buff, shell->com.cursor->str, i);
      print_buff(shell, buff, i);
      aff_cmpl(shell);
    }
  else
    print_buff(shell, buff, i);
}

static char	*give_it_to_guigui(t_shell *shell, char *buff, char *c)
{
  char		*ret;

  my_dprintf(1, "%s\n", shell->key.curs);
  if (*c == 4)
    return (NULL);
  if (shell->history_on == TRUE && shell->bufist)
    return (strdup(shell->bufist));
  if (shell->com.on == TRUE && shell->com.cursor)
    {
      shell->com.on = FALSE;
      ret = strdup(shell->com.cursor->str);
      delete_list(&shell->com);
      return (ret);
    }
  return (strdup(buff));
}

static t_bool	bentor(t_shell *shell, int *i, char *c, char *buff)
{
  if (complete_part(shell, buff, i, c) == FALSE)
    return (FALSE);
  if (g_sigint == 1)
    {
      bzero(buff, sizeof(char) * BUFF_SIZE);
      shell->history_on = FALSE;
      shell->com.on = FALSE;
      aff_prompt(shell);
      g_sigint = 0;
      return (FALSE);
    }
  process_keys(shell, i, c, buff);
  aff_cmd(shell, buff, i);
  return (TRUE);
}

char	*gnl_ncurse(t_shell *shell)
{
  char	buff[BUFF_SIZE + 1];
  int	i[5];
  char	c[RD_SIZE];

  shell->history_on = FALSE;
  bzero(buff, sizeof(char) * BUFF_SIZE);
  write(1, shell->key.nocurs, strlen(shell->key.nocurs));
  bzero(i, sizeof(int) * 4);
  *i = -1;
  i[4] = 1;
  aff_prompt(shell);
  while ((read(STDIN_FILENO, c, RD_SIZE)) > 0 && *c != 4)
    {
      mv_curs(shell, i, buff);
      i[2] = strlen(buff);
      if ((bentor(shell, i, c, buff)) == FALSE)
	break ;
    }
  return (give_it_to_guigui(shell, buff, c));
}

int	gogo_ncurse(struct termios *old)
{
  if ((ioctl(0, TCGETS, &old[0])) < 0
      || (ioctl(0, TCGETS, &old[1])) < 0)
    return (EXIT_FAILURE);
  old[1].c_lflag &= ~ICANON;
  old[1].c_lflag &= ~ECHO;
  if ((ioctl(0, TCSETS, &old[1])) < 0)
    return (EXIT_FAILURE);
  return (EXIT_SUCCESS);
}
