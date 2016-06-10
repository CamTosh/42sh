/*
** complete_cmd.c for  in /home/tim/rendu/2_semestre/system_unix/42sh/PSU_2015_42sh/srcs/ncurse
**
** Made by almazo_t
** Login   <tim@epitech.net>
**
** Started on  Wed Jun  1 17:16:43 2016 almazo_t
** Last update Sun Jun  5 22:30:54 2016 almazo_t
*/

#include <sys/types.h>
#include <dirent.h>
#include <string.h>
#include <stdlib.h>
#include "kala.h"

char	*isol_wrd(const char *str, int i)
{
  char	*tmp;
  int	k;
  int	l;

  k = invlen(str, i) - 1;
  if ((tmp = calloc(sizeof(char) * (k + 5), sizeof(char))) == NULL)
    return (NULL);
  i = i - k;
  l = -1;
  while (l <= (k + 1) && str[i] && is_wrd(str[i]) == TRUE)
    {
      tmp[++l] = str[i];
      ++i;
    }
  return (tmp);
}

const char	*creat_path(const char *tmp, const char *name, int par)
{
  char		*new;
  int		i;
  int		k;

  if (par != 3)
    return (tmp);
  i = -1;
  k = strlen(tmp) + strlen(name) + 2;
  if ((new = calloc(sizeof(char) * k, sizeof(char))) == NULL)
    return (NULL);
  while (name[++i] && name[i] != '/')
    new[i] = name[i];
  new[i] = '/';
  k = -1;
  while (tmp[++k])
    new[++i] = tmp[k];
  free((void *)tmp);
  return (new);
}

t_bool		read_it(t_com *com, DIR *dir, const char *str, int par)
{
  struct dirent	*op;
  char		*tmp;
  int		len;

  while ((op = readdir(dir)))
    {
      len = strlen(str);
      if (((((strncmp(str, op->d_name, len) == 0 && par == 0)
	     || par == 1 || par == 3) && op->d_name[0] != '.')
	   || (strncmp(str, op->d_name, len) == 0 && par == 2)))
	{
	  if ((tmp = strdup(op->d_name)) == NULL)
	    return (FALSE);
	  if (creat_list(com, creat_path(tmp, str, par)) == FALSE)
	    return (FALSE);
	}
    }
  return (TRUE);
}

static t_bool	complete_cmd(t_com *com, const char *str)
{
  DIR		*dir;
  int		i;

  i = -1;
  while (com->paths[++i])
    {
      if ((dir = opendir(com->paths[i])) != NULL)
	if (read_it(com, dir, str, 0) == FALSE)
	  return (FALSE);
      closedir(dir);
    }
  return (TRUE);
}

t_bool	completion(t_shell *shell, const char *str, int pos)
{
  char	*wrd;
  int	ret[2];

  shell->com.cmd_l = NULL;
  if ((wrd = isol_wrd(str, pos)) == NULL)
    return (FALSE);
  ret[0] = strlen(wrd);
  ret[1] = select_param(str, pos);
  if (ret[1] == FUNC && ret[0] != 0)
    complete_cmd(&shell->com, wrd);
  else if (ret[1] == PAR)
    complet_par(shell, str, pos);
  shell->com.cursor = shell->com.cmd_l;
  free(wrd);
  return (TRUE);
}
