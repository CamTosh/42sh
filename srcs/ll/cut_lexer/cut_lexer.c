/*
** cut_lexer.c for KalaSH in /home/guillaume/Documents/rendu/42sh/PSU_2015_42sh
**
** Made by Guillaume Benard
** Login   <guillaume@epitech.net>
**
** Started on  Wed Jun  1 18:08:14 2016 Guillaume Benard
** Last update Sat Jun  4 05:43:58 2016 Guillaume Benard
*/

#include <stdlib.h>
#include <string.h>
#include "kala.h"
#include "ll.h"
#include "utils.h"

static t_bool	reorder(t_lexem **list)
{
  if (*list)
    {
      while ((*list)->left)
	*list = (*list)->left;
    }
  return (TRUE);
}

static t_bool	clean_exit(t_lexem **list, char *str)
{
  t_lexem	*lexem;

  free(str);
  reorder(list);
  while ((lexem = *list))
    {
      *list = (*list)->right;
      free(lexem->str);
      free(lexem);
    }
  return (FALSE);
}

static const t_lexer_tab	g_tab[] = {
  {1, SEMI_LEN, COL, ";", &cut_that},
  {2, OR_LEN, OR, "||", &cut_that},
  {3, AND_LEN, AND, "&&", &cut_that},
  {4, DLDIR_LEN, DLDIR, "<<", &cut_dir},
  {4, LDIR_LEN, LDIR, "<", &cut_dir},
  {4, DRDIR_LEN, DRDIR, ">>", &cut_dir},
  {4, RDIR_LEN, RDIR, ">", &cut_dir},
  {4, PIPE_LEN, PIPE, "|", &cut_that},
  {4, AMP_LEN, AMPERSAND, "&", &cut_that},
  {5, NULL_VALUE, STRING, "*", &cut_cmd}
};

static int	get_lexem(t_lexem **lex, char *str)
{
  unsigned int	idx;
  char		*ret;

  idx = 0;
  while ((idx < (G_TAB_SIZE - 1))
	 && (strncmp(str, g_tab[idx].flag, g_tab[idx].len) != MATCH))
    ++idx;
  if (!(ret = g_tab[idx].fct(lex, str, &g_tab[idx])))
    return (-1);
  return (ret - str);
}

t_bool	cut_lexer(t_lexem **lex, const char *str)
{
  int	idx;
  int	ret;
  char	*cpy;

  *lex = NULL;
  if (!(cpy = strdup(str)))
    return (clean_exit(lex, NULL));
  idx = NULL_VALUE;
  while (cpy[idx])
    {
      if (!(IS_SPACE(cpy[idx])))
	{
	  if ((ret = get_lexem(lex, &cpy[idx])) == -1)
	    return (clean_exit(lex, cpy));
	  idx += ret;
	}
      else
	++idx;
    }
  free(cpy);
  return (reorder(lex));
}
