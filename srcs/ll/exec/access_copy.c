/*
** access_copy.c for KalaSH in /home/rotaru_i/Coding/42sh
**
** Made by ROTARU Iulian
** Login   <rotaru_i@epitech.net>
**
** Started on  Sun Jun  5 19:48:37 2016 ROTARU Iulian
** Last update Sun Jun  5 19:51:32 2016 ROTARU Iulian
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

t_bool	access_copy(const char *buffer, t_lexem *node)
{
  free(*node->av);
  if (!(*node->av = strdup(buffer)))
    return (FALSE);
  return (CONTINUE);
}

t_bool	slashed(const char *str)
{
  int	i;

  i = -1;
  while (*(str + ++i))
    if (*(str + i) == '/')
      return (TRUE);
  return (FALSE);
}

t_bool	slashed_ret(t_lexem *node, char **path, t_shell *shell)
{
  free_wordtab(path);
  if (access(*node->av, X_OK) < 0)
    {
      my_dprintf(STDERR_FILENO, "%s: Command not found.\n", *node->av);
      shell->exit.status = 1;
      return (TRUE);
    }
  return (CONTINUE);
}

t_bool	too_long(char *buffer, char **path, t_lexem *node, int i)
{
  (void)buffer;
  my_dprintf(STDERR_FILENO,
	     "%s/%s: File name too long.\n", *(path + i), *node->av);
  free_wordtab(path);
  return (TRUE);
}

t_bool	check_command(t_lexem *node, t_shell *shell)
{
  char	buffer[256];
  char	**path;
  int	i;

  if ((!node || !shell || !node->str)
      || (!(path = env_field_to_wordtab("PATH", shell->env))))
    return (FALSE);
  if (slashed(*node->av) == TRUE)
    return (slashed_ret(node, path, shell));
  i = -1;
  while (*(path + ++i))
    {
      bzero(buffer, 256);
      if (snprintf(buffer, 256, "%s/%s", *(path + i), *node->av) >= 256)
	return (too_long(buffer, path, node, i));
      if (!access(buffer, X_OK))
	return (access_copy(buffer, node));
    }
  my_dprintf(STDERR_FILENO, "%s: Command not found.\n", *node->av);
  shell->exit.status = 1;
  free_wordtab(path);
  return (TRUE);
}
