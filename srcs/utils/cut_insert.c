/*
** cut_insert.c for cut in /home/said_p/Test
**
** Made by pierre said
** Login   <said_p@epitech.net>
**
** Started on  Mon May 23 01:43:41 2016 pierre said
** Last update Fri Jun  3 23:05:23 2016 pierre said
*/

#include <string.h>
#include <unistd.h>
#include <stdlib.h>

int	cut(char *s, int i, int size)
{
  char	*tmp;

  if (s == NULL || i < 0 || size < 0)
    return (0);
  if ((tmp = strdup(&s[i + size])) == NULL)
    return (-1);
  s[i] = '\0';
  strcat(s, tmp);
  free(tmp);
  return (0);
}

char	*insert(char *s, int i, const char *ins)
{
  char	*str;

  if ((str = malloc(sizeof(char) * (strlen(s)
				    + strlen(ins) + 1))) == NULL)
    return (NULL);
  str[0] = 0;
  strcat(str, s);
  str[i] = 0;
  strcat(&str[i], ins);
  while (s[i])
    {
      str[i + strlen(ins)] = s[i];
      i = i + 1;
    }
  str[i + strlen(ins)] = '\0';
  free(s);
  return (str);
}
