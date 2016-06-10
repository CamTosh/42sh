/*
** complete_param.c for  in /home/tim/rendu/2_semestre/system_unix/42sh/PSU_2015_42sh/srcs/ncurse
**
** Made by almazo_t
** Login   <tim@epitech.net>
**
** Started on  Thu Jun  2 16:11:20 2016 almazo_t
** Last update Mon Jun  6 00:01:00 2016 almazo_t
*/

#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <dirent.h>
#include "kala.h"

static t_bool	start_cmp(t_com *com, const char *str, int par)
{
  DIR		*dir;

  if ((dir = opendir(str)) != NULL && par != 1)
    if (read_it(com, dir, str, 3) == FALSE)
      return (FALSE);
  if ((dir = opendir(".")) != NULL)
    if (read_it(com, dir, str, par) == FALSE)
      return (FALSE);
  closedir(dir);
  return (TRUE);
}

t_bool	complet_par(t_shell *shell, const char *str, int pos)
{
  char	*wrd;
  int	size_wrd;

  shell->com.cmd_l = NULL;
  if ((wrd = isol_wrd(str, pos)) == NULL)
    return (FALSE);
  size_wrd = strlen(wrd);
  if (size_wrd == 0)
    start_cmp(&shell->com, ".", 1);
  else if (size_wrd != 0)
    start_cmp(&shell->com, wrd, 2);
  else
    delete_list(&shell->com);
  shell->com.cursor = shell->com.cmd_l;
  free(wrd);
  return (TRUE);
}

t_bool	is_wrd(char c)
{
  char	*ope;
  int	i;

  ope = "<>;|&\t ";
  i = -1;
  while (ope[++i])
    {
      if (ope[i] == c)
	return (FALSE);
    }
  return (TRUE);
}

int	invlen(const char *str, int i)
{
  int	k;

  k = 0;
  while (i >= 0)
    {
      if (is_wrd(str[i]) == FALSE)
	return (k);
      ++k;
      --i;
    }
  return (k);
}
