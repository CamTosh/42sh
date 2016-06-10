/*
** my_perror.c for KalaSH in /home/guillaume/Documents/rendu/42sh/PSU_2015_42sh
**
** Made by Guillaume Benard
** Login   <guillaume@epitech.net>
**
** Started on  Mon May 30 15:54:02 2016 Guillaume Benard
** Last update Sun Jun  5 16:19:36 2016 Guillaume Benard
*/

#include <stdio.h>
#include <unistd.h>
#include "kala.h"

int	my_perror(const char *str, int ret)
{
  (void)my_dprintf(STDERR_FILENO, "%s\n", str);
  return (ret);
}
