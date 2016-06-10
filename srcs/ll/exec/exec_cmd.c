/*
** exec_cmd.c for KalaSH in /home/rotaru_i/Coding/42sh
**
** Made by ROTARU Iulian
** Login   <rotaru_i@epitech.net>
**
** Started on  Sun Jun  5 02:28:42 2016 ROTARU Iulian
** Last update Sun Jun  5 19:53:35 2016 ROTARU Iulian
*/
#include <signal.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <unistd.h>
#include "kala.h"
#include "utils.h"
#include "ll.h"

t_bool		exec_cmd(t_lexem *node, t_shell *shell)
{
  int		save[3];
  t_bool	ret;

  shell->last_hist = NULL;
  if ((launch_dup(node, save) == FALSE)
      || (ret = my_select(node, shell)) == FALSE)
    return (FALSE);
  else if (ret == TRUE)
    {
      shell->exit.status = (shell->exit.should_exit == FALSE)
	? (EXIT_FAILURE) : (shell->exit.status);
      free_wordtab(node->av);
      return (reset_dup(node, save));
    }
  if (exec_it(node, shell) == FALSE)
    return (FALSE);
  free_wordtab(node->av);
  return (reset_dup(node, save));
}
