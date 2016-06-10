/*
** setenv.c for mysh in /home/benard_g/Debian/guillaume/Documents/rendu
**
** Made by Benard Guillaume
** Login   <benard_g@epitech.net>
**
** Started on  Mon Apr 11 17:22:11 2016 Benard Guillaume
** Last update Sun Jun  5 16:07:40 2016 Guillaume Benard
*/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "kala.h"
#include "utils.h"

t_bool	my_env(t_lexem *node, t_shell *sh)
{
  if (node->av[1] != NULL)
    {
      my_dprintf(2, ENV_USAGE);
      return (TRUE);
    }
  show_wordtab(sh->env);
  return (TRUE);
}

static t_bool	add_new(t_lexem *node, t_shell *sh)
{
  int		idx;
  int		len;
  char		**env;

  len = my_count_wordtab(sh->env);
  if (!(env = calloc(len + 2, sizeof(char *))))
    return (FALSE);
  idx = 0;
  while (idx < len)
    {
      env[idx] = sh->env[idx];
      idx += 1;
    }
  if (!(env[idx] = calloc(strlen(node->av[1])
			  + strlen(node->av[2]) + 2, sizeof(char))))
    return (FALSE);
  strcpy(env[idx], node->av[1]);
  strcat(env[idx], "=");
  strcat(env[idx], node->av[2]);
  free(sh->env);
  sh->env = env;
  return (TRUE);
}

static t_bool	add_in_env(t_lexem *node, t_shell *sh)
{
  int		idx;
  char		*to_free;

  if ((idx = locate_env_var(node->av[1], sh->env)) == -1)
    return (add_new(node, sh));
  to_free = sh->env[idx];
  if (!(sh->env[idx] = calloc(strlen(node->av[1])
			      + strlen(node->av[2]) + 2, sizeof(char))))
    return (FALSE);
  strcpy(sh->env[idx], node->av[1]);
  strcat(sh->env[idx], "=");
  strcat(sh->env[idx], node->av[2]);
  free(to_free);
  return (TRUE);
}

t_bool		my_setenv(t_lexem *node, t_shell *sh)
{
  int		len;
  char		*s;

  s = NULL;
  if ((len = my_count_wordtab(node->av)) > 3)
    {
      my_dprintf(2, SETENV_USAGE);
      return (TRUE);
    }
  if (len == 1)
    return (my_env(node, sh));
  if (node->av[2] == NULL)
    if ((s = calloc(1, sizeof(char))) == NULL)
      return (FALSE);
  node->av[2] = (node->av[2] == NULL) ? s : node->av[2];
  if (add_in_env(node, sh) == FALSE)
    {
      if (node->av[2] == s)
	node->av[2] = NULL;
      return (FALSE);
    }
  if (node->av[2] == s)
    node->av[2] = NULL;
  return (TRUE);
}
