/*
** printf_put_nbr.c for libdprintf in /home/guillaume/Documents/Libraries
**
** Made by Benard Guillaume
** Login   <guillaume@epitech.net>
**
** Started on  Wed Mar 16 23:02:45 2016 Benard Guillaume
** Last update Wed May  4 12:19:14 2016 Guillaume Benard
*/

#include <stdlib.h>
#include <unistd.h>
#include "my_dprintf.h"

static int	dprintf_put_nbr_rec(long int value, t_printf *print)
{
  char		digit;

  if (value < 0)
    {
      if (write(print->fd, "-", 1) == -1)
	return (EXIT_FAILURE);
      print->ret += 1;
    }
  if (((value > 9) || (value < -9))
      && (dprintf_put_nbr_rec(ABS(value / 10), print) == EXIT_FAILURE))
    return (EXIT_FAILURE);
  print->ret += 1;
  digit = ABS(value % 10) + '0';
  if (write(print->fd, &digit, 1) == -1)
    return (EXIT_FAILURE);
  return (EXIT_SUCCESS);
}

int		dprintf_put_nbr(t_printf *print)
{
  long int	value;

  value = va_arg(print->ap, int);
  if (dprintf_put_nbr_rec(value, print) == EXIT_FAILURE)
    return (EXIT_FAILURE);
  return (EXIT_SUCCESS);
}
