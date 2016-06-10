/*
** wordtab.c for KalaSH in /home/guillaume/Documents/rendu/42sh/PSU_2015_42sh
**
** Made by Guillaume Benard
** Login   <guillaume@epitech.net>
**
** Started on  Mon May 30 16:39:01 2016 Guillaume Benard
** Last update Sun Jun  5 16:17:48 2016 Guillaume Benard
*/

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "kala.h"

char	**free_wordtab(char *wordtab[])
{
  int	idx;

  if (!(wordtab))
    return (NULL);
  idx = 0;
  while (wordtab[idx])
    free(wordtab[idx++]);
  free(wordtab);
  return (NULL);
}

int	wordtab_len(char *const wordtab[])
{
  int	idx;

  idx = 0;
  while (wordtab[idx])
    ++idx;
  return (idx);
}

void	show_wordtab(char *const wordtab[])
{
  while (*wordtab)
    my_dprintf(1, "%s\n", *(wordtab++));
}

char	**dup_wordtab(char *const wordtab[])
{
  char	**dup;
  int	idx;

  if (!(dup = calloc(wordtab_len(wordtab) + 1, sizeof(char *))))
    return (NULL);
  idx = 0;
  while (wordtab[idx])
    {
      if (!(dup[idx] = strdup(wordtab[idx])))
	return (free_wordtab(dup));
      ++idx;
    }
  return (dup);
}
