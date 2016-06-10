/*
** env_field_to_wortdab.c for KalaSH in /home/guillaume/Documents/rendu/42sh
**
** Made by Guillaume Benard
** Login   <guillaume@epitech.net>
**
** Started on  Thu Jun  2 03:02:18 2016 Guillaume Benard
** Last update Thu Jun  2 21:29:37 2016 Guillaume Benard
*/

#include <stdlib.h>
#include <string.h>
#include "kala.h"
#include "utils.h"

static int	count_field_case(const char *field)
{
  int		count;

  count = 1;
  while (*field)
    {
      if (*field == SEPARATOR_ENV_CHAR)
	++count;
      ++field;
    }
  return (count);
}

static char	**edit_wordtab(char *field, char *wordtab[])
{
  char		*next;
  int		idx;

  idx = NULL_VALUE;
  next = field;
  while (*field)
    {
      while ((*next) && (*next != SEPARATOR_ENV_CHAR))
	++next;
      if (*next == SEPARATOR_ENV_CHAR)
	*(next++) = END_CHAR;
      if (!(wordtab[idx++] = strdup(field)))
	return (free_wordtab(wordtab));
      field = next;
    }
  return (wordtab);
}

static char	*get_env_var(const char *field, char *const env[])
{
  char		*value;

  value = NULL;
  if ((value = my_getenv(field, env)))
    return (value);
  else if (strcmp(field, PATH_FIELD) == MATCH)
    value = strdup(DEFAULT_PATH);
  return (value);
}

char	**env_field_to_wordtab(const char *field, char *const env[])
{
  char	**wordtab;
  char	*env_field;

  env_field = NULL;
  if (!(field)
      || !(env_field = get_env_var(field, env))
      || !(wordtab = calloc(count_field_case(env_field) + 1,
			    sizeof(char *)))
      || !(wordtab = edit_wordtab(env_field, wordtab)))
    wordtab = NULL;
  free(env_field);
  return (wordtab);
}
