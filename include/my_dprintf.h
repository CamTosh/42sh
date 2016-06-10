/*
** my_dprintf.h for libdprintf in /home/guillaume/Documents/rendu/Minishell2
**
** Made by benard_g
** Login   <guillaume@epitech.net>
**
** Started on  Sat Apr  9 01:40:17 2016 benard_g
** Last update Sat Apr  9 01:40:24 2016 benard_g
*/

#ifndef MY_DPRINTF_H_
# define MY_DPRINTF_H_

# include <stdarg.h>
# include <stdbool.h>

/*
**  +------------------------------------+
**  |               Macros               |
**  +------------------------------------+
*/
# ifndef ABS
#  define ABS(x) (((x) >= 0) ? (x) : -(x))
# endif /* !ABS */

/*
**  +------------------------------------+
**  |              Structures            |
**  +------------------------------------+
*/
typedef struct	s_printf
{
  int		fd;
  int		ret;
  int		idx;
  va_list	ap;
}		t_printf;

typedef struct	s_dprintf_flags
{
  char		flag;
  int		(*ptr)(t_printf *print);
}		t_dprintf_flags;

/*
**  +------------------------------------+
**  |             Functions              |
**  +------------------------------------+
*/
int		my_dprintf(int fd, const char *format, ...);
int		dprintf_putchar(t_printf *print);
int		dprintf_putstr(t_printf *print);
int		dprintf_put_nbr(t_printf *print);
int		dprintf_hexa_min(t_printf *print);
int		dprintf_hexa_max(t_printf *print);
int		dprintf_decimal(t_printf *print);
int		dprintf_binary(t_printf *print);
int		dprintf_putnbr_base(unsigned long int, const char *base,
				    int base_value, t_printf *print);
int		dprintf_ptr(t_printf *print);
int		dprintf_modulo_n(t_printf *print);

#endif /* !MY_DPRINTF_H_ */
