/*
** my_getenv.c for KalaSH in /home/guillaume/Documents/rendu/42sh/PSU_2015_42sh
**
** Made by Guillaume Benard
** Login   <guillaume@epitech.net>
**
** Started on  Wed Jun  1 15:46:48 2016 Guillaume Benard
** Last update Thu Jun  2 22:20:07 2016 Guillaume Benard
*/

#include <stdlib.h>
#include <string.h>
#include "kala.h"
#include "utils.h"

static char	*is_same_field(const char *field, const char *env)
{
  char		*content;
  int		idx;

  content = NULL;
  idx = NULL_VALUE;
  while ((field[idx]) && (env[idx]) && (env[idx] != VALUE_CHAR)
	 && (field[idx] == env[idx]))
    ++idx;
  if ((field[idx])
      || (env[idx] != VALUE_CHAR)
      || ((content = strdup(&env[idx + 1])) ==  NULL))
    return (NULL);
  return (content);
}

char	*my_getenv(const char *field, char *const env[])
{
  char	*content;
  int	idx;

  content = NULL;
  if (field)
    {
      idx = NULL_VALUE;
      while ((env[idx] != NULL)
	     && ((content = is_same_field(field, env[idx])) == NULL))
	++idx;
    }
  return (content);
}
