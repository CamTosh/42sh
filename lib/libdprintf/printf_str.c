/*
** printf_str.c for libdprintf in /home/guillaume/Documents/Libraries/my_dprintf
**
** Made by Benard Guillaume
** Login   <guillaume@epitech.net>
**
** Started on  Wed Mar 16 21:25:01 2016 Benard Guillaume
** Last update Mon Jun  6 00:24:06 2016 almazo_t
*/

#include <stdlib.h>
#include <unistd.h>
#include "my_dprintf.h"

static int	dprintf_strlen(const char *str)
{
  int		idx;

  idx = 0;
  while (str[idx])
    idx += 1;
  return (idx);
}

int	dprintf_putchar(t_printf *print)
{
  char	c;

  c = va_arg(print->ap, int);
  if (write(print->fd, &c, 1) == -1)
    return (EXIT_FAILURE);
  print->ret += 1;
  return (EXIT_SUCCESS);
}

int	dprintf_putstr(t_printf *print)
{
  char	*str;
  int	ret;

  str = va_arg(print->ap, char *);
  if (str == NULL)
    ret = write(print->fd, "(null)", 6);
  else
    ret = write(print->fd, str, dprintf_strlen(str));
  if (ret == -1)
    return (EXIT_FAILURE);
  print->ret += ret;
  return (EXIT_SUCCESS);
}
