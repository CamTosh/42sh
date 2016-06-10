/*
** parsing.c for KalaSH in /home/guillaume/Documents/rendu/42sh/PSU_2015_42sh
**
** Made by Guillaume Benard
** Login   <guillaume@epitech.net>
**
** Started on  Mon May 30 19:14:03 2016 Guillaume Benard
** Last update Sun Jun  5 17:22:46 2016 pierre said
*/

#include <stdlib.h>
#include <glob.h>
#include "kala.h"
#include "ll.h"

static t_bool	is_a_comment(const char *str)
{
  while (IS_SPACE(*str))
    ++str;
  return ((*str == COM_CHAR) ? (TRUE) : (FALSE));
}

static t_bool	lexem_treatment(t_shell *shell)
{
  t_lexem	*lexem;
  t_lexem	*next;
  t_bool	ret;

  lexem = shell->lexem;
  while (lexem)
    {
      next = lexem->right;
      if (lexem->type == STRING)
	{
	  if ((ret = make_alias(&lexem, shell->alias, NULL)) != CONTINUE)
	    return (ret);
	  if (lexem->left == NULL)
	    shell->lexem = lexem;
	  if ((lexem->str = rep_glob(lexem->str, &ret)) == NULL)
	    return ((ret == GLOB_NOMATCH) ? TRUE : FALSE);
	}
      lexem = next;
    }
  return (check_list(shell));
}

t_bool		lets_pars(t_shell *shell, const char *line)
{
  t_bool	ret;

  shell->lexem = NULL;
  if (is_a_comment(line))
    return (CONTINUE);
  if (!(cut_lexer(&shell->lexem, line))
      || (lexem_treatment(shell) != CONTINUE))
    {
      shell->lexem = free_lexem_list(shell->lexem);
      shell->exit.status = EXIT_FAILURE;
      return (CONTINUE);
    }
  shell->lexem = build_tree(shell->lexem);
  ret = exec(shell);
  liberate_tree(shell->lexem);
  return (ret);
}
