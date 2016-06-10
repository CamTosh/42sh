/*
** replace_env.c for replace_env in /home/said_p/Work/PSU_2015_42sh/srcs/ll
**
** Made by pierre said
** Login   <said_p@epitech.net>
**
** Started on  Wed Jun  1 15:25:06 2016 pierre said
** Last update Mon Jun  6 00:13:49 2016 almazo_t
*/

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "kala.h"
#include "utils.h"

static int	check_env(const char *in, char **env, char **str, int *j)
{
  int		i;
  int		len;

  i = 0;
  len = 0;
  while (in[len] != ' ' && in[len] != '\t' && in[len])
    len = len + 1;
  while (env[i])
    {
      if (strncmp(in, env[i], len) == 0)
	{
	  if ((*str = insert(*str, *j, &env[i][len + 1])) == NULL)
	    return (-1);
	  *j = *j + strlen(&env[i][len + 1]) - 1;
	  return (len);
	}
      i = i + 1;
    }
  my_dprintf(2, "%s: Undefined variable.\n", in);
  return (-1);
}

static void	inc_idx(int *i, int *j, const char *in)
{
  if (in[*i] != '\0')
    {
      *i = *i + 1;
      *j = *j + 1;
    }
}

static int	init_rep_env(int *i, int *j, char **str, const char *in)
{
  *i = 0;
  *j = 0;
  if ((*str = strdup(in)) == NULL)
    return (-1);
  return (0);
}

char		*replace_var_env(const char *in, char **env)
{
  char		*str;
  t_bool	quote;
  int		len;
  int		i;
  int		j;

  quote = FALSE;
  if (init_rep_env(&i, &j, &str, in) == -1)
    return (NULL);
  while (in[i])
    {
      if (in[i] == '"' || in[i] == '\'')
	quote = TRUE;
      if (in[i] == '$' && in[i + 1] != '\0'
	  && (in[i - 1] != '\\' || quote == TRUE))
	{
	  if ((len = check_env(&in[i + 1], env, &str, &j)) == -1)
	    return (NULL);
	  i = i + len;
	}
      else
	str[j] = in[i];
      inc_idx(&i, &j, in);
    }
  return (str);
}
