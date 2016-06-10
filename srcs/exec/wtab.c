/*
** exec.c for KalaSH in /home/rotaru_i/Coding/42sh/srcs/exec
**
** Made by ROTARU Iulian
** Login   <rotaru_i@epitech.net>
**
** Started on  Fri Jun  3 22:55:16 2016 ROTARU Iulian
** Last update Sun Jun  5 20:13:01 2016 ROTARU Iulian
*/

#include <stdlib.h>
#include <stdio.h>
#include "kala.h"

static char	*wtab_word_extract(char *str, int i,
				   int *tab_idx, char refchar)
{
  int		len;
  char		*out;
  int		new_idx;
  char		save;

  len = 0;
  save = refchar;
  new_idx = i - 1;
  ret_thr(&refchar, str, &new_idx, &len);
  if (!(out = malloc(sizeof(char) * (len + 1))))
    return (NULL);
  --i;
  refchar = save;
  ret_scd(out, &refchar, str, &i);
  ++*tab_idx;
  return (out);
}

int	ret_frth(void **send, int *i, int *tab_idx, char *refchar)
{
  char	*str;

  str = (char *)*send;
  if (!*refchar && (*(str + *i) == '\"' || *(str + *i) == '\''))
    {
      *refchar = *(str + *i);
      if ((*i == 0) || (*i && (*(str + *i - 1) == TAB_CHAR
			       || *(str + *i - 1) == SPACE_CHAR)
			&& (!(*i - 1) || *(str + *i - 2) != '\\')))
	{
	  ++*i;
	  if (!(*((char **)*(send + 1) + *tab_idx) =
		wtab_word_extract(str, *i, tab_idx, *refchar)))
	    return (2);
	}
      else
	return (1);
    }
  else if (*refchar && *(str + *i) == *refchar)
    {
      *refchar = 0;
      return (1);
    }
  return (0);
}

int	ret_sixth(void **send, int *i, int *tab_idx, char *refchar)
{
  char	*str;

  str = *send;
  if ((*(str + *i) && (!*refchar && (!*i && *(str + *i) != SPACE_CHAR
				     && *(str + *i) != TAB_CHAR)))
      && (!(*((char **)*(send + 1) + *tab_idx) =
	    wtab_word_extract(str, *i, tab_idx, *refchar))))
    return (1);
  if ((*(str + *i) && (!*refchar && *i && (*(str + *i) != SPACE_CHAR
					   && *(str + *i) != TAB_CHAR)
		       && ((*(str + *i - 1) == SPACE_CHAR || *(str + *i - 1)
			    == TAB_CHAR)
			   && (*i - 1) && *(str + *i - 2) != '\\')))
      && (!(*((char **)*(send + 1) + *tab_idx) =
	    wtab_word_extract(str, *i, tab_idx, *refchar))))
    return (1);
  return (0);
}

static char	**wtab_word_harvest(char *str, char **out)
{
  int		i;
  int		tab_idx;
  char		refchar;
  void		*send[2];

  i = -1;
  tab_idx = 0;
  refchar = 0;
  *send = (void *)str;
  *(send + 1) = (void *)out;
  while (*(str + ++i))
    {
      if (ret_frth(send, &i, &tab_idx, &refchar) == 1)
	continue;
      if (ret_sixth(send, &i, &tab_idx, &refchar) == 1)
	return (NULL);
      if (*(str + i) && !refchar && *(str + i) == '\\' && (i - 1) > 0
	  && *(str + i - 1) != '\\')
	continue;
    }
  out[tab_idx] = NULL;
  return (out);
}

char	**wtab(char *str)
{
  int	words;
  char	**out;

  if (!str)
    return (NULL);
  while ((*str) && ((*str) == ' ' || (*str) == '\t'))
    ++str;
  words = wtab_word_count(str);
  if (!(out = malloc(sizeof(char *) * (words + 1))))
    return (NULL);
  return (wtab_word_harvest(str, out));
}
