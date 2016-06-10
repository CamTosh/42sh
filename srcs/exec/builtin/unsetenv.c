/*
** unsetenv.c for mysh in /home/benard_g/Debian/guillaume/Documents/rendu
**
** Made by Benard Guillaume
** Login   <benard_g@epitech.net>
**
** Started on  Tue Apr 12 11:00:58 2016 Benard Guillaume
** Last update Sun Jun  5 16:07:53 2016 Guillaume Benard
*/

#include <stdio.h>
#include <stdlib.h>
#include "kala.h"
#include "utils.h"

int	locate_env_var(const char *field, char **env)
{
  int	env_idx;
  int	idx;

  env_idx = 0;
  while (env[env_idx])
    {
      idx = 0;
      while ((env[env_idx][idx]) && (field[idx]) && (env[env_idx][idx] != '=')
	     && (env[env_idx][idx] == field[idx]))
	idx += 1;
      if (env[env_idx][idx] == '=' && !(field[idx]))
	return (env_idx);
      env_idx += 1;
    }
  return (-1);
}

static int	erase_var(int idx, t_shell *sh)
{
  char		*to_free;

  to_free = sh->env[idx];
  while (sh->env[idx])
    {
      sh->env[idx] = sh->env[idx + 1];
      idx += 1;
    }
  free(to_free);
  return (EXIT_SUCCESS);
}

t_bool	my_unsetenv(t_lexem *node, t_shell *sh)
{
  int	idx;
  int	len;
  int	env_idx;

  if ((len = my_count_wordtab(node->av)) < 2)
    {
      my_dprintf(2, UNSETENV_USAGE);
      return (TRUE);
    }
  idx = 1;
  while (node->av[idx])
    {
      if ((env_idx = locate_env_var(node->av[idx], sh->env)) != -1
	  && (erase_var(env_idx, sh) == EXIT_FAILURE))
	return (FALSE);
      idx += 1;
    }
  return (TRUE);
}
