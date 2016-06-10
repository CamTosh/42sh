/*
** gnl.c for KalaSH in /home/guillaume/Documents/rendu/42sh/PSU_2015_42sh
**
** Made by Guillaume Benard
** Login   <guillaume@epitech.net>
**
** Started on  Mon May 30 15:06:56 2016 Guillaume Benard
** Last update Wed Jun  1 17:32:59 2016 Guillaume Benard
*/

#include <stdlib.h>
#include <unistd.h>
#include "kala.h"
#include "utils.h"

static int	my_len(const char *str, char lim)
{
  int		idx;

  if (!(str))
    return (0);
  idx = 0;
  while ((str[idx]) && (str[idx] != lim))
    ++idx;
  return (idx);
}

static t_bool	expand(char **line, const char *buf)
{
  char		*new;
  int		idx;
  int		line_len;
  int		buf_len;
  int		buf_idx;

  line_len = my_len(*line, '\0');
  buf_len = my_len(buf, '\n');
  if (!(line_len) && !(*buf))
    return (TRUE);
  if (!(new = malloc(sizeof(char *) * (line_len + buf_len + 2))))
    return (FALSE);
  idx = -1;
  while (++idx < line_len)
    new[idx] = (*line)[idx];
  buf_idx = 0;
  while (idx <= (line_len + buf_len))
    new[idx++] = buf[buf_idx++];
  new[idx] = 0;
  free(*line);
  *line = new;
  return (TRUE);
}

char		*get_next_line(const int fd)
{
  static char	buf[READ_SIZE + 1];
  char		*line;
  int		ret;
  int		idx_buf;
  int		idx_crush;

  line = NULL;
  ret = TRUE;
  while ((ret > 0) && (expand(&line, &buf[0]))
	 && (my_len(line, '\n') == my_len(line, '\0')))
    {
      if (((ret = read(fd, &buf[0], READ_SIZE)) <= 0 && !(line))
	  || (buf[0] == '\0'))
	return (NULL);
      buf[(ret < 0) ? (0) : (ret)] = '\0';
    }
  if (line)
    line[my_len(line, '\n')] = '\0';
  idx_buf = my_len(&buf[0], '\n');
  idx_buf += (buf[idx_buf] == '\n') ? (1) : (0);
  idx_crush = 0;
  while (buf[idx_buf])
    buf[idx_crush++] = buf[idx_buf++];
  buf[idx_crush] = 0;
  return (line);
}
