/*
** my_getnbr.c for KalaSH in /home/guillaume/Documents/rendu/42sh/PSU_2015_42sh
**
** Made by Guillaume Benard
** Login   <guillaume@epitech.net>
**
** Started on  Thu Jun  2 21:43:02 2016 Guillaume Benard
** Last update Sun Jun  5 13:28:29 2016 Guillaume Benard
*/

#include <limits.h>
#include "kala.h"
#include "utils.h"

static t_bool	is_nbr(const char *str)
{
  int		idx;

  if (!(str))
    return (FALSE);
  str += (*str == SIGN_CHAR) ? (1) : (0);
  idx = 0;
  while (str[idx] && IS_DIGIT(str[idx]))
    ++idx;
  return (((idx == NULL_VALUE) || (str[idx])) ? (FALSE) : (TRUE));
}

t_bool	my_getnbr(const char *str, int *nb)
{
  int	sign;

  if (!(is_nbr(str)))
    return (FALSE);
  (*nb) = NULL_VALUE;
  sign = (*str == SIGN_CHAR) ? (-1) : (1);
  str += (*str == SIGN_CHAR) ? (1) : (0);
  while (*str)
    {
      if ((sign > 0) && (CAN_GO_UP(*nb, *str)))
	*nb = *nb * 10 + *(str++) - '0';
      else if ((sign < 0) && (CAN_GO_DOWN(*nb, *str)))
	*nb = *nb * 10 - *(str++) + '0';
      else
	{
	  *nb = (sign > 0) ? (INT_MAX) : (INT_MIN);
	  return (TRUE);
	}
    }
  return (TRUE);
}
