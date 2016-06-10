/*
** rep_glob.c for rep_glob in /home/said_p/Test
**
** Made by pierre said
** Login   <said_p@epitech.net>
**
** Started on  Fri Jun  3 22:15:54 2016 pierre said
** Last update Sun Jun  5 20:27:10 2016 ROTARU Iulian
*/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <glob.h>
#include "kala.h"
#include "utils.h"

char	*locate_format(char *str, int i)
{
  char	*format;
  int	j;
  int	tmp;
  int	len;

  len = 0;
  if ((format = malloc(sizeof(char) * (strlen(str) + 1))) == NULL)
    return (NULL);
  while (i >= 0 && str[i] != '\'' && str[i] != '"'
	 && str[i] != ' ' && str[i] != '\t')
    i = i - 1;
  tmp = ++i;
  j = 0;
  while (str[i] && str[i] != '\'' && str[i] != '"'
	 && str[i] != ' ' && str[i] != '\t')
    {
      format[j] = str[i];
      i = i + 1;
      j = j + 1;
      len = len + 1;
    }
  format[j] = '\0';
  if (cut(str, tmp, len) == -1)
    return (NULL);
  return (format);
}

t_bool		format_res(char *format, char **res, t_bool *ret)
{
  glob_t	glo;
  int		i;
  int		len;

  i = -1;
  len = 0;
  if ((*ret = glob(format, 0, NULL, &glo)) >= 1)
    return (FALSE);
  while (glo.gl_pathv[++i])
    len += strlen(glo.gl_pathv[i]) + 1;
  if ((*res = malloc(sizeof(char) * (len + 1))) == NULL)
    {
      globfree(&glo);
      return (FALSE);
    }
  *res[0] = '\0';
  i = -1;
  while (glo.gl_pathv[++i])
    {
      strcat(*res, glo.gl_pathv[i]);
      if (glo.gl_pathv[i + 1])
	strcat(*res, " ");
    }
  globfree(&glo);
  return (TRUE);
}

t_bool	insert_file(char *format, char **str, int ins, t_bool *ret)
{
  char	*res;

  res = NULL;
  if (format[0] != '*')
    ins = ins - (strlen(format) - 1);
  if (format_res(format, &res, ret) == FALSE)
    {
      if (*ret == GLOB_NOMATCH)
	my_dprintf(2, "No match.\n");
      return (FALSE);
    }
  if ((*str = insert(*str, ins, res)) == NULL)
    return (FALSE);
  free(res);
  return (TRUE);
}

char	*rep_glob(char *str, t_bool *ret)
{
  char	*format;
  char	quote;
  int	i;

  i = 0;
  quote = FALSE;
  while (str[i])
    {
      if (str[i] == '"' && quote != '\'')
	quote = (quote == FALSE) ? '"' : FALSE;
      if (str[i] == '\'' && quote != '"')
	quote = (quote == FALSE) ? '\'' : FALSE;
      if (str[i] == '*' && quote == FALSE)
	{
	  if ((format = locate_format(str, i)) == NULL
	      || insert_file(format, &str, i, ret) == FALSE)
	    return (NULL);
	  free(format);
	}
      i = i + 1;
    }
  return (str);
}
