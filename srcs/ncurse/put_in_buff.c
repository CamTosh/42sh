/*
** put_in_buff.c for  in /home/tim/rendu/2_semestre/system_unix/42sh/PSU_2015_42sh/srcs/ncurse
**
** Made by almazo_t
** Login   <tim@epitech.net>
**
** Started on  Fri Jun  3 19:05:59 2016 almazo_t
** Last update Sun Jun  5 11:43:25 2016 Alif Matthias
*/

#include <string.h>
#include "kala.h"

static int	put_wrd(char *buff, char *tmp, const char *str, int *ret)
{
  int		i;
  int		k;
  int		l;

  i = -1;
  k = -1;
  while (++i <= ret[1] && buff[i])
    tmp[i] = buff[i];
  l = i + ret[0];
  while (str[++k])
    {
      tmp[i] = str[k];
      ++i;
    }
  ret[1] = i - strlen(str);
  while (buff[l] && is_wrd(buff[l]) == TRUE)
    ++l;
  while (buff[l] && i < BUFF_SIZE)
    {
      tmp[i] = buff[l++];
      ++i;
    }
  return (ret[1]);
}

void	put_in_buff(char *buff, const char *str, int *i)
{
  char	tmp[BUFF_SIZE];
  int	ret[2];

  ret[0] = invlen(buff, *i);
  ret[1] = *i - ret[0];
  bzero(tmp, BUFF_SIZE * sizeof(char));
  *i = put_wrd(buff, tmp, str, ret);
  strncpy(buff, tmp, BUFF_SIZE);
}
