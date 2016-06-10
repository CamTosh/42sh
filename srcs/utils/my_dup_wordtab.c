/*
** my_dup_wordtab.c for libmy in /home/guillaume/Documents/Libraries/libmy
**
** Made by Benard Guillaume
** Login   <guillaume@epitech.net>
**
** Started on  Thu Mar 31 13:28:54 2016 Benard Guillaume
** Last update Sun Jun  5 03:02:27 2016 pierre said
*/

#include <string.h>
#include <stdlib.h>

void	*my_free_wordtab(char **wordtab)
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

int	my_count_wordtab(char **wordtab)
{
  int	idx;

  if (!(wordtab))
    return (0);
  idx = 0;
  while (wordtab[idx])
    idx += 1;
  return (idx);
}

char	**my_dup_wordtab(char **wordtab)
{
  char	**dup;
  int	idx;
  int	len;

  if (!(wordtab))
    return (NULL);
  len = my_count_wordtab(wordtab);
  if (!(dup = calloc((len + 1), sizeof(char *))))
    return (NULL);
  idx = 0;
  while (wordtab[idx])
    {
      if (!(dup[idx] = strdup(wordtab[idx])))
	return (my_free_wordtab(dup));
      idx += 1;
    }
  return (dup);
}
