/*
** cut_delim.c for KalaSH in /home/guillaume/Documents/rendu/42sh/PSU_2015_42sh
**
** Made by Guillaume Benard
** Login   <guillaume@epitech.net>
**
** Started on  Fri Jun  3 17:26:36 2016 Guillaume Benard
** Last update Sun Jun  5 20:21:45 2016 ROTARU Iulian
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "kala.h"
#include "ll.h"
#include "utils.h"

int	return_error(const char *msg, const char c)
{
  my_dprintf(STDERR_FILENO, "%s", msg);
  if (c != END_CHAR)
    my_dprintf(STDERR_FILENO, " %c", c);
  my_dprintf(STDERR_FILENO, ".\n");
  return (-1);
}

int	pass_quote(const char *str)
{
  char	quote;
  int	len;

  len = 1;
  quote = *(str);
  while ((str[len]) && (str[len] != quote))
    ++len;
  if (!(str[len]))
    return (-1);
  return (len);
}

static int	get_file_name_len(const char *str)
{
  int		len;
  const char	*save;

  save = str;
  while (IS_SPACE(*str))
    ++str;
  if (!(*str) || (IS_DELIM(*str)))
    return (return_error(MISS_NAME_DIR, END_CHAR));
  while ((*str) && !(IS_SPACE(*str)) && !(IS_DELIM(*str)))
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
  return (str - save);
}

char		*cut_dir(t_lexem **lex, char *str,
			 const t_lexer_tab *info)
{
  t_lexem	*new;
  int		len;

  new = NULL;
  if (!(new = new_lexem()))
    return (NULL);
  str += info->len;
  if ((len = get_file_name_len(str)) == -1
      || !(new->str = malloc(sizeof(char) * (len + 1))))
    {
      free(new);
      return (NULL);
    }
  strncpy(new->str, str, len);
  new->str[len--] = END_CHAR;
  while (len >= (NULL_VALUE - info->len))
    str[len--] = SPACE_CHAR;
  new->type = info->type;
  new->priority = info->priority;
  add_in_lexer_list(lex, new);
  return (str);
}

char		*cut_that(t_lexem **lex, char *str,
			  const t_lexer_tab *info)
{
  t_lexem	*new;

  if (!(new = new_lexem()))
    return (NULL);
  new->type = info->type;
  new->priority = info->priority;
  add_in_lexer_list(lex, new);
  return (str + info->len);
}
