/*
** lexer.c<PSU_2015_42sh> for KalaSH in /home/guillaume/Documents/rendu/42sh
**
** Made by Guillaume Benard
** Login   <guillaume@epitech.net>
**
** Started on  Wed Jun  1 20:58:06 2016 Guillaume Benard
** Last update Sun Jun  5 20:26:05 2016 ROTARU Iulian
*/

#include <stdlib.h>
#include <unistd.h>
#include "kala.h"
#include "ll.h"

void	add_in_lexer_list(t_lexem **list, t_lexem *lex)
{
  lex->left = *list;
  if (*list)
    (*list)->right = lex;
  *list = lex;
}

void		*free_lexem_list(t_lexem *list)
{
  t_lexem	*lex;

  while ((lex = list))
    {
      list = list->right;
      free(lex->str);
      free(lex);
    }
  return (NULL);
}

t_lexem		*new_lexem(void)
{
  t_lexem	*new;

  if (!(new = calloc(NEW, sizeof(t_lexem))))
    return (NULL);
  new->fd[STDIN_FILENO] = STDIN_FILENO;
  new->fd[STDOUT_FILENO] = STDOUT_FILENO;
  new->fd[STDERR_FILENO] = STDERR_FILENO;
  return (new);
}
