/*
** misc.c for kalash in /home/rotaru_i/Coding/LibLap/kalaterm
**
** Made by ROTARU Iulian
** Login   <rotaru_i@epitech.net>
**
** Started on  Sun Jun  5 00:58:33 2016 ROTARU Iulian
** Last update Sun Jun  5 00:59:37 2016 ROTARU Iulian
*/

#include "kalas.h"

void	nset(void *data, size_t t)
{
  int	i;

  i = -1;
  while (++i < (int)t)
    *(((char *)data) + i) = 0;
}

int	add_char(t_kala *data, char add)
{
  char	*new;
  int	i;

  if (!(new = bunny_malloc(sizeof(char) * (len(data->input) + 2))))
    return (-1);
  i = 0;
  while (data->input && *(data->input + i))
    {
      *(new + i) = *(data->input + i);
      ++i;
    }
  *(new + i) = add;
  *(new + i + 1) = 0;
  bunny_free(data->input);
  data->input = new;
  return (0);
}

int	len(const char *str)
{
  int	i;

  i = 0;
  if (!str)
    return (0);
  while (*(str + i))
    ++i;
  return (i);
}

int	writerr(char *str, int ret)
{
  write(STDERR_FILENO, str, len(str));
  return (ret);
}
