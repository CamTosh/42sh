/*
** cd.c for mysh in /home/benard_g/Debian/guillaume/Documents/rendu/Minishell2
**
** Made by Benard Guillaume
** Login   <benard_g@epitech.net>
**
** Started on  Tue Apr 12 20:59:27 2016 Benard Guillaume
** Last update Sun Jun  5 16:13:05 2016 Guillaume Benard
*/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include "kala.h"
#include "utils.h"

t_bool	my_exit(t_lexem *node, t_shell *sh)
{
  int	len;

  len = my_count_wordtab(node->av);
  if (len == 1)
    {
      sh->exit.should_exit = TRUE;
      return (TRUE);
    }
  if ((len > 2) || (my_getnbr(node->av[1], &len) == FALSE))
    {
      my_dprintf(2, EXIT_USAGE);
      return (TRUE);
    }
  sh->exit.should_exit = TRUE;
  sh->exit.status = len;
  return (TRUE);
}

static int	go_to_dir(t_lexem *node, t_shell *sh, char *dir)
{
  char		*new_av[4];

  new_av[0] = "";
  new_av[1] = "OLDPWD";
  new_av[2] = getcwd(NULL, 0);
  new_av[3] = MY_NULL;
  if ((dir == NULL)
      || (chdir(dir) == -1))
    {
      (void)my_dprintf(STDERR_FILENO, "%s: Permission denied.\n", dir);
      return (TRUE);
    }
  node->av = free_wordtab(node->av);
  free(dir);
  if (!(node->av = dup_wordtab(new_av)))
    return (FALSE);
  free(new_av[2]);
  return (my_setenv(node, sh));
}

t_bool	my_cd(t_lexem *node, t_shell *sh)
{
  int	len;

  if ((len = my_count_wordtab(node->av)) > 2)
    {
      my_dprintf(2, CD_USAGE);
      return (TRUE);
    }
  if (len == 1)
    return (go_to_dir(node, sh, my_getenv("HOME", sh->env)));
  if (strcmp(node->av[1], "-") == 0)
    return (go_to_dir(node, sh, my_getenv("OLDPWD", sh->env)));
  return (go_to_dir(node, sh, strdup(node->av[1])));
}
