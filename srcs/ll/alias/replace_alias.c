/*
** replace_alias.c for replace in /home/said_p/Work/PSU_2015_42sh/srcs/alias
**
** Made by pierre said
** Login   <said_p@epitech.net>
**
** Started on  Sun Jun  5 01:11:57 2016 pierre said
** Last update Sun Jun  5 09:01:49 2016 pierre said
*/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "kala.h"
#include "utils.h"

static char	*get_first(char *str, int *cut)
{
  char		*first;
  int		i;
  t_bool	quote;

  i = 0;
  quote = FALSE;
  if ((first = malloc(sizeof(char) * (strlen(str) + 1))) == NULL)
    return (NULL);
  while (str[i] && ((str[i] != ' ' && str[i] != '\t') || quote == TRUE))
    {
      if (str[i] == '\"')
      	quote = (quote == TRUE) ? FALSE : TRUE;
      first[i] = str[i];
      i = i + 1;
    }
  first[i] = '\0';
  *cut = i;
  return (first);
}

static int	rep_lex_str(t_lexem **lex, char *str, int cutted)
{
  if (cut((*lex)->str, 0, cutted) == -1
      || ((*lex)->str = insert((*lex)->str, 0, str)) == NULL)
    return (FALSE);
  return (TRUE);
}

static int	loop_detect(char *first, t_alias *last, t_alias *tmp)
{
  free(first);
  if (last != NULL && last == tmp)
    return (CONTINUE);
  return (3);
}

int		replace_alias(t_lexem **lex,
			      t_alias *alias, t_alias **replaced, t_alias *last)
{
  t_alias	*tmp;
  char		*first;
  int		cut;

  tmp = alias;
  if ((first = get_first((*lex)->str, &cut)) == NULL)
    return (FALSE);
  while (tmp)
    {
      if (strcmp(tmp->alias, first) == 0)
	{
	  if (tmp->replaced == TRUE)
	    return (loop_detect(first, last, tmp));
	  *replaced = tmp;
	  tmp->replaced = TRUE;
	  free(first);
	  if ((first = strdup(tmp->input)) == NULL
	      || rep_lex_str(lex, first, cut) == FALSE)
	    return (FALSE);
	  return (TRUE);
	}
      tmp = tmp->next;
    }
  free(first);
  return (CONTINUE);
}
