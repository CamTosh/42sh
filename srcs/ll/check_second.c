/*
** check_second.c for KalaSH in /home/guillaume/Documents/rendu/42sh
**
** Made by Guillaume Benard
** Login   <guillaume@epitech.net>
**
** Started on  Sun Jun  5 11:47:01 2016 Guillaume Benard
** Last update Sun Jun  5 23:05:54 2016 Guillaume Benard
*/

#include <stdio.h>
#include <unistd.h>
#include "kala.h"
#include "ll.h"

t_bool		put_after(t_shell *shell, t_lexem *lex)
{
  t_lexem	*next;

  next = lex->right;
  if ((next->type >= PIPE) && (next->type < DRDIR_ERR))
    {
      my_dprintf(STDERR_FILENO, "Ambiguous output redirect.\n");
      return (FALSE);
    }
  lex->right = next->right;
  next->left = lex->left;
  if (lex->left)
    lex->left->right = next;
  if (next->right)
    next->right->left = lex;
  lex->left = next;
  next->right = lex;
  if (!(next->left))
    shell->lexem = next;
  return (TRUE);
}

t_bool		set_rdir_at_the_end(t_shell *shell)
{
  t_lexem	*lex;

  lex = shell->lexem;
  while (lex)
    {
      if ((lex->type >= RDIR) && (lex->type <= DRDIR_ERR))
	{
	  while ((lex->right) && !(IS_DEL(lex->right->type)))
	    {
	      if (put_after(shell, lex) == FALSE)
		return (FALSE);
	    }
	}
      lex = lex->right;
    }
  return (CONTINUE);
}

t_bool	t_dir(t_type t)
{
  if (t == LDIR || t == DLDIR || (t >= RDIR && t <= DRDIR_ERR))
    return (TRUE);
  return (FALSE);
}

t_bool	check_empty_cmd(t_lexem *elem)
{
  while (elem)
    {
      while ((elem) && (elem->type == STRING
			|| (t_dir(elem->type)) || elem->type == COL))
	elem = elem->right;
      if (!elem)
	return (CONTINUE);
      if (!((((elem->left && (elem->left->type == STRING
			      || ((t_dir(elem->left->type))
				  && elem->left->left
				  && elem->left->left->type == STRING))))
	     && (elem->right && (elem->right->type == STRING
				 || ((t_dir(elem->right->type))
				     && elem->right->right
				     && elem->right->right->type
				     == STRING))))))
	{
	  my_dprintf(2, "Invalid null command.\n");
	  return (FALSE);
	}
      elem = elem->right;
    }
  return (CONTINUE);
}
