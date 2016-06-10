/*
** alias_handle.c for alias_handle in /home/said_p
**
** Made by pierre said
** Login   <said_p@epitech.net>
**
** Started on  Sun Jun  5 03:49:14 2016 pierre said
** Last update Sun Jun  5 13:30:02 2016 ROTARU Iulian
*/

#include <stdio.h>
#include <stdlib.h>
#include "kala.h"
#include "utils.h"

t_bool	alias_handle(t_lexem *lex, t_shell *sh)
{
  char	*str;

  if (lex->av[1] == NULL || lex->av[2] == NULL)
    {
      if (lex->av[1] == NULL)
	show_alias(sh->alias);
      return (CONTINUE);
    }
  if ((str = concat_av(&lex->av[2])) == NULL)
    return (FALSE);
  unalias(&sh->alias, lex->av[1]);
  if (add_alias(&sh->alias, lex->av[1], str) == -1)
    return (FALSE);
  return (TRUE);
}

t_bool	unalias_handle(t_lexem *lex, t_shell *sh)
{
  int	i;

  if (lex->av[1] == NULL)
    {
      dprintf(2, UNALIAS_HANDLE);
      return (TRUE);
    }
  i = 0;
  while (lex->av[i])
    {
      unalias(&sh->alias, lex->av[i]);
      i = i + 1;
    }
  return (TRUE);
}
