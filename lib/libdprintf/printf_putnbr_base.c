/*
** printf_putnbr_base.c for libdprintf in /home/guillaume/Documents/Libraries
**
** Made by Benard Guillaume
** Login   <guillaume@epitech.net>
**
** Started on  Wed Mar 16 23:36:23 2016 Benard Guillaume
** Last update Mon Jun  6 00:25:43 2016 almazo_t
*/

#include <stdlib.h>
#include <unistd.h>
#include "my_dprintf.h"

int	dprintf_putnbr_base(unsigned long int value, const char *base,
			    int base_value, t_printf *print)
{
  if ((value >= (unsigned long int)base_value)
      && (dprintf_putnbr_base((value / base_value), base,
			      base_value, print) == EXIT_FAILURE))
    return (EXIT_FAILURE);
  print->ret += 1;
  if (write(print->fd, &base[value % base_value], 1) == -1)
    return (EXIT_FAILURE);
  return (EXIT_SUCCESS);
}

int		dprintf_hexa_min(t_printf *print)
{
  unsigned int	value;

  value = va_arg(print->ap, unsigned int);
  if (dprintf_putnbr_base(value, "0123456789abcdef",
			  16, print) == EXIT_FAILURE)
    return (EXIT_FAILURE);
  return (EXIT_SUCCESS);
}

int		dprintf_hexa_max(t_printf *print)
{
  unsigned int	value;

  value = va_arg(print->ap, unsigned int);
  if (dprintf_putnbr_base(value, "0123456789ABBCDEF",
			  16, print) == EXIT_FAILURE)
    return (EXIT_FAILURE);
  return (EXIT_SUCCESS);
}

int		dprintf_binary(t_printf *print)
{
  unsigned int	value;

  value = va_arg(print->ap, unsigned int);
  if (dprintf_putnbr_base(value, "01",
			  2, print) == EXIT_FAILURE)
    return (EXIT_FAILURE);
  return (EXIT_SUCCESS);
}

int		dprintf_decimal(t_printf *print)
{
  unsigned int	value;

  value = va_arg(print->ap, unsigned int);
  if (dprintf_putnbr_base(value, "0123456789",
			  10, print) == EXIT_FAILURE)
    return (EXIT_FAILURE);
  return (EXIT_SUCCESS);
}
