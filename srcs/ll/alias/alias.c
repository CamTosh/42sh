/*
** alias.c for alias in /home/said_p/Work/PSU_2015_42sh/srcs/alias
**
** Made by pierre said
** Login   <said_p@epitech.net>
**
** Started on  Sun Jun  5 01:11:15 2016 pierre said
** Last update Sun Jun  5 16:14:15 2016 Guillaume Benard
*/

#include <stdio.h>
#include "kala.h"
#include "ll.h"

static void	wire_lex(t_lexem **lex, t_lexem *tmp)
{
  t_lexem	*ptr;

  tmp->left = (*lex)->left;
  if ((*lex)->left != NULL)
    (*lex)->left->right = tmp;
  ptr = tmp;
  while (ptr->right)
    ptr = ptr->right;
  ptr->right = (*lex)->right;
  if ((*lex)->right != NULL)
    (*lex)->right->left = tmp;
  *lex = tmp;
}

static int	call_sons(t_lexem *tmp, t_alias *alias, t_alias *called)
{
  t_lexem	*ptr;
  t_lexem	*next;
  t_bool	passed;
  t_bool	ret;

  ptr = tmp;
  passed = FALSE;
  while (ptr)
    {
      next = ptr->right;
      if (ptr->type == STRING)
	{
	  if (passed == FALSE)
	    {
	      if ((ret = make_alias(&ptr, alias, called)) != CONTINUE)
		return (ret);
	      passed = TRUE;
	    }
	  else
	    if ((ret = make_alias(&ptr, alias, NULL)) != CONTINUE)
	      return (ret);
	}
      ptr = next;
    }
  return (CONTINUE);
}

t_bool		make_alias(t_lexem **lex, t_alias *alias, t_alias *last)
{
  t_alias	*called;
  t_lexem	 *tmp;
  t_bool	ret;

  if ((ret = replace_alias(lex, alias, &called, last)) == FALSE)
    return (FALSE);
  else if (ret == CONTINUE)
    return (CONTINUE);
  else if (ret == 3)
    {
      my_dprintf(2, "Alias loop.\n");
      return (TRUE);
    }
  if (cut_lexer(&tmp, (*lex)->str) == FALSE)
    return (FALSE);
  if ((ret = call_sons(tmp, alias, called)) != CONTINUE)
    return (ret);
  called->replaced = FALSE;
  wire_lex(lex, tmp);
  return (CONTINUE);
}
