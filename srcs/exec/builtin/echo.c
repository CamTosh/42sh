/*
** echo.c for echo in /home/said_p/Work/PSU_2015_42sh/srcs/exec/builtin
**
** Made by pierre said
** Login   <said_p@epitech.net>
**
** Started on  Sun Jun  5 04:15:08 2016 pierre said
** Last update Sun Jun  5 13:29:33 2016 ROTARU Iulian
*/

#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include "kala.h"

t_bool		my_echo(t_lexem *lex, t_shell *sh)
{
  t_bool	nocar;
  int		i;

  nocar = FALSE;
  if (lex->av[1] != NULL && strcmp(lex->av[1], "-n") == 0)
    nocar = TRUE;
  i = (nocar == TRUE) ? 2 : 1;
  while (lex->av[i])
    {
      write(1, lex->av[i], strlen(lex->av[i]));
      if (lex->av[i + 1])
	write(1, " ", 1);
      i = i + 1;
    }
  if (nocar == FALSE)
    write(1, "\n", 1);
  (void)sh;
  return (TRUE);
}
