/*
** printf_ptr.c for libdprintf in /home/guillaume/Documents/Libraries/my_dprintf
**
** Made by Benard Guillaume
** Login   <guillaume@epitech.net>
**
** Started on  Fri Mar 18 00:22:40 2016 Benard Guillaume
** Last update Mon Jun  6 00:24:38 2016 almazo_t
*/

#include <stdlib.h>
#include <unistd.h>
#include "my_dprintf.h"

int			dprintf_ptr(t_printf *print)
{
  unsigned long int	add;

  add = va_arg(print->ap, unsigned long int);
  if (add == 0)
    {
      if (write(print->fd, "(nil)", 5) == -1)
	return (EXIT_FAILURE);
      print->ret += 5;
    }
  else
    {
      if ((write(print->fd, "0x", 2) == -1)
	  || (dprintf_putnbr_base(add, "0123456789abcdef",
				  16, print) == EXIT_FAILURE))
	return (EXIT_FAILURE);
      print->ret += 2;
    }
  return (EXIT_SUCCESS);
}

int	dprintf_modulo_n(t_printf *print)
{
  int	*value;

  value = va_arg(print->ap, int *);
  (*value) = print->ret;
  return (EXIT_SUCCESS);
}
