/*
** cut_cmd.c for KalaSH in /home/guillaume/Documents/rendu/42sh/PSU_2015_42sh
**
** Made by Guillaume Benard
** Login   <guillaume@epitech.net>
**
** Started on  Sat Jun  4 00:43:12 2016 Guillaume Benard
** Last update Sun Jun  5 01:57:08 2016 Guillaume Benard
*/

#include <stdlib.h>
#include <string.h>
#include "kala.h"
#include "ll.h"
#include "utils.h"

static char	*g_dir[] = {
  "<<",
  "<",
  ">>",
  ">"
};

static t_bool	launch_remove_dir(t_lexem **lex, char *str,
				  const t_lexer_tab *info)
{
  int		idx;

  idx = NULL_VALUE;
  while ((idx < G_DIR_SIZE)
	 && (strncmp(g_dir[idx], str, strlen(g_dir[idx])) != MATCH))
    ++idx;
  if (!(cut_dir(lex, str, &info[idx - GOOD_DIR_TAB])))
    return (FALSE);
  return (TRUE);
}

static int	next_word(char *str)
{
  int		len;
  char		*save;

  save = str;
  while (*(str) && !(IS_DELIM(*str)) && !(IS_SPACE(*str)))
    {
      if (IS_QUOTE(*str))
	{
	  if ((len = pass_quote(str)) == -1)
	    return (return_error(UNMATCH_QUOTE, *str));
	  str += len;
	}
      else if (*str == B_SLASH)
	{
	  if (!(*(++str)))
	    return (return_error(MISS_SLASH, END_CHAR));
	}
      ++str;
    }
  while ((*str) && (IS_SPACE(*str) && !(IS_DELIM(*str))))
    ++str;
  return (str - save);
}

static int	extract_dir(t_lexem **lex, char *str,
			    const t_lexer_tab *info)
{
  char		*save;
  int		len;

  save = str;
  while ((*str) && !(IS_DELIM(*str)))
    {
      if ((len = next_word(str)) == -1)
	return (-1);
      str += len;
      if ((IS_DIR(*str)) && !(launch_remove_dir(lex, str, info)))
	return (-1);
    }
  return (str - save);
}

char		*cut_cmd(t_lexem **lex, char *str,
			 const t_lexer_tab *info)
{
  int		len;
  t_lexem	*new;

  new = NULL;
  if (((len = extract_dir(lex, str, info)) == -1)
      || !(new = new_lexem())
      || !(new->str = malloc(sizeof(char) * (len + 1))))
    {
      free(new);
      return (NULL);
    }
  strncpy(new->str, str, len);
  new->str[len] = END_CHAR;
  new->type = info->type;
  new->priority = info->priority;
  add_in_lexer_list(lex, new);
  return (str + len);
}
