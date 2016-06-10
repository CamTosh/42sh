/*
** concat_av.c for concat_av in /home/said_p/Test
**
** Made by pierre said
** Login   <said_p@epitech.net>
**
** Started on  Tue May 31 16:52:43 2016 pierre said
** Last update Sun Jun  5 04:01:42 2016 pierre said
*/

#include <string.h>
#include <stdlib.h>

char	*concat_av(char **av)
{
  char	*str;
  int	i;
  int	len;

  if (av == NULL)
    return (NULL);
  len = 0;
  i = -1;
  while (av[++i])
    len = len + strlen(av[i]) + 1;
  if ((str = malloc(sizeof(char) * (len + 1))) == NULL)
    return (NULL);
  str[0] = 0;
  i = 0;
  while (av[i])
    {
      strcat(str, av[i]);
      if (av[i + 1] != NULL)
	strcat(str, " ");
      i = i + 1;
    }
  return (str);
}
