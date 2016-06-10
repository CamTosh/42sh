/*
** my_dprintf.c for my_dprintf in /home/guillaume/Documents/Libraries/my_dprintf
**
** Made by Benard Guillaume
** Login   <guillaume@epitech.net>
**
** Started on  Wed Mar 16 20:42:16 2016 Benard Guillaume
** Last update Wed May  4 12:19:01 2016 Guillaume Benard
*/

#include <stdlib.h>
#include <unistd.h>
#include "my_dprintf.h"

static t_dprintf_flags const flags[] = {
  {'c', &dprintf_putchar},
  {'s', &dprintf_putstr},
  {'i', &dprintf_put_nbr},
  {'d', &dprintf_put_nbr},
  {'x', &dprintf_hexa_min},
  {'X', &dprintf_hexa_max},
  {'u', &dprintf_decimal},
  {'b', &dprintf_binary},
  {'p', &dprintf_ptr},
  {'n', &dprintf_modulo_n}
};

static int	jump_modifiers(const char *format, t_printf *print)
{
  while ((format[print->idx] == '#') || (format[print->idx] == '.')
	 || (format[print->idx] == 'z') || (format[print->idx] == '-')
	 || (format[print->idx] == ' ') || (format[print->idx] == '+')
	 || (format[print->idx] == 't') || (format[print->idx] == 'I')
	 || (format[print->idx] == 'h') || (format[print->idx] == 'l')
	 || (format[print->idx] == 'L') || (format[print->idx] == 'q')
	 || (format[print->idx] == 'j') || (format[print->idx] == '\'')
	 || ((format[print->idx] >= '0') && (format[print->idx] <= '9')))
    print->idx += 1;
  return (EXIT_SUCCESS);
}

static int	dprintf_flag(const char *format, t_printf *print)
{
  int		idx;
  int		lim;

  jump_modifiers(format, print);
  if (format[print->idx] == 0)
    return (EXIT_SUCCESS);
  lim = sizeof(flags) / sizeof(flags[0]);
  idx = 0;
  while ((idx < lim) && (format[print->idx] != flags[idx].flag))
    idx += 1;
  if (idx < lim)
    {
      print->idx += 1;
      return (flags[idx].ptr(print));
    }
  if (((format[print->idx] != '%') && (write(print->fd, "%", 1) == -1))
      || (write(print->fd, &format[print->idx++], 1) == -1))
    return (EXIT_FAILURE);
  print->ret += (format[print->idx - 1] == '%') ? (1) : (2);
  return (EXIT_SUCCESS);
}

static int	dprintf_read_format(const char *format, t_printf *print)
{
  if (format[print->idx] == '%')
    {
      print->idx += 1;
      if (dprintf_flag(format, print) == EXIT_FAILURE)
	return (EXIT_FAILURE);
    }
  else
    {
      if (write(print->fd, &format[print->idx++], 1) == -1)
	return (EXIT_FAILURE);
      print->ret += 1;
    }
  return (EXIT_SUCCESS);
}

int		my_dprintf(int fd, const char *format, ...)
{
  t_printf	print;

  if (format == NULL)
    return (-1);
  va_start(print.ap, format);
  print.fd = fd;
  print.ret = 0;
  print.idx = 0;
  while (format[print.idx])
    {
      if (dprintf_read_format(format, &print) == EXIT_FAILURE)
	return (-1);
    }
  va_end(print.ap);
  return (print.ret);
}
