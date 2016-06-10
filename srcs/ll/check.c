/*
** check.c for KalaSH in /home/guillaume/Documents/rendu/42sh/PSU_2015_42sh
**
** Made by Guillaume Benard
** Login   <guillaume@epitech.net>
**
** Started on  Sun Jun  5 08:46:54 2016 Guillaume Benard
** Last update Sun Jun  5 20:08:00 2016 Guillaume Benard
*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "kala.h"
#include "ll.h"

static t_lexem	*rm_lexem(t_lexem *lexem, t_shell *shell)
{
  t_lexem	*next;

  next = lexem->right;
  if (lexem->right)
    lexem->right->left = lexem->left;
  if (lexem->left)
    lexem->left->right = lexem->right;
  else
    shell->lexem = next;
  free(lexem->str);
  free(lexem);
  return (next);
}

static t_bool	apply_ampersand(t_shell *shell)
{
  t_lexem	*list;

  list = shell->lexem;
  while (list)
    {
      if (list->type == AMPERSAND)
	{
	  if (!(list->left) || IS_AMP_ERR(list->left->type))
	    {
	      my_dprintf(STDERR_FILENO, "Invalid null command.\n");
	      return (FALSE);
	    }
	  if (AMP_REP(list->left->type))
	    {
	      list->left->type += 1;
	      list = rm_lexem(list, shell);
	    }
	  else
	    list = list->right;
	}
      else
	list = list->right;
    }
  return (CONTINUE);
}

static t_bool	put_before(t_shell *shell, t_lexem *lex)
{
  t_lexem	*prev;

  if (lex->left->type >= LDIR && lex->left->type <= PIPE_ERR)
    {
      my_dprintf(STDERR_FILENO, "Ambiguous output redirect.\n");
      return (FALSE);
    }
  prev = lex->left;
  prev->right = lex->right;
  lex->left = prev->left;
  if (prev->left)
    prev->left->right = lex;
  if (lex->right)
    lex->right->left = prev;
  if (!(lex->left))
    shell->lexem = lex;
  return (CONTINUE);
}

static t_bool	set_ldir_at_the_left(t_shell *shell)
{
  t_lexem	*list;

  list = shell->lexem;
  while (list)
    {
      if (IS_LDIR(list->type))
	{
	  while ((list->left) && !(IS_DEL(list->left->type)))
	    {
	      if (put_before(shell, list) != CONTINUE)
		return (FALSE);
	    }
	}
      list = list->right;
    }
  return (CONTINUE);
}

t_bool	check_list(t_shell *shell)
{
  if (apply_ampersand(shell) != CONTINUE
      || set_ldir_at_the_left(shell) != CONTINUE
      || set_rdir_at_the_end(shell) != CONTINUE
      || check_empty_cmd(shell->lexem) != CONTINUE)
    return (FALSE);
  return (CONTINUE);
}
