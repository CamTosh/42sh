/*
** create_path_tab.c for  in /home/tim/rendu/2_semestre/system_unix/42sh/
**
** Made by almazo_t
** Login   <tim@epitech.net>
**
** Started on  Wed Jun  1 14:35:32 2016 almazo_t
** Last update Mon Jun  6 00:07:50 2016 almazo_t
*/

#include <stdlib.h>
#include "kala.h"

static int	count_paths(const char *path)
{
  int		i;
  int		k;

  i = -1;
  k = 0;
  while (path[++i])
    {
      if (path[i] == ':')
	++k;
    }
  (i > 0) ? ++k : 0;
  return (k);
}

static int	len_path(const char *path)
{
  int		i;

  i = 0;
  while (path[i] && path[i] != ':')
    ++i;
  return (i);
}

static char	*creat_line(int *i, const char *path)
{
  int		k;
  char		*line;

  k = -1;
  if ((line = calloc(sizeof(char)
		     * (len_path(&path[*i]) + 2), sizeof(char))) == NULL)
    return (NULL);
  line[++k] = '/';
  while (path[*i] && path[*i] != ':')
    {
      line[k] = path[*i];
      ++k;
      ++(*i);
    }
  line[k] = '/';
  return (line);
}

char	**cup_path(const char *path)
{
  char	**tmp;
  int	i;
  int	k;
  int	size;

  i = -1;
  k = 0;
  size = count_paths(path);
  if (path == NULL
      || (tmp = calloc(sizeof(char *) * (size + 1), sizeof(char *))) == NULL)
    return (NULL);
  while (path[++i] && k < size)
    {
      if ((tmp[k] = creat_line(&i, path)) == NULL)
	return (NULL);
      ++k;
    }
  return (tmp);
}
