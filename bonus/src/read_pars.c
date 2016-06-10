/*
** read_pars.c for kalash in /home/rotaru_i/Coding/LibLap/kalaterm
**
** Made by ROTARU Iulian
** Login   <rotaru_i@epitech.net>
**
** Started on  Sun Jun  5 01:06:26 2016 ROTARU Iulian
** Last update Sun Jun  5 01:07:14 2016 ROTARU Iulian
*/

#include "kalas.h"

void	check_if_y(t_kala *data)
{
  if (!*(data->buff.term_buff + data->buff.y_idx))
    {
      if (!(*(data->buff.term_buff + data->buff.y_idx) = bunny_malloc(106)))
	return ;
      nset(*(data->buff.term_buff + data->buff.y_idx), 106);
    }
}

void	write_in_term(t_kala *data, int i)
{
  if (*(data->buff.read_buff + i) == '\b')
    {
      if (data->buff.x_idx >= 1)
	data->buff.x_idx -= 2;
    }
  else
    *(*(data->buff.term_buff + data->buff.y_idx) + data->buff.x_idx)
      = *(data->buff.read_buff + i);
}

void	max_length_case(t_kala *data)
{
  int	j;

  if (data->buff.y_idx == 999)
    {
      j = -1;
      bunny_free(*(data->buff.term_buff));
      while (*(data->buff.term_buff + ++j + 1))
	*(data->buff.term_buff + j) = *(data->buff.term_buff + j + 1);
      *(data->buff.term_buff + j) = NULL;
    }
  else
    data->buff.y_idx++;
}

int	strcmp_start(const char *one, const char *two)
{
  int	i;

  if (!one || !two)
    return (1);
  i = 0;
  while (*(one + i) && *(two + i) && *(two + i) == *(one + i))
    ++i;
  if (!*(one + i))
    return (0);
  return (1);
}

void	check_clear(t_kala *data, int *i)
{
  int	j;

  if (strcmp_start(CLEAR_SEQ, data->buff.read_buff + *i) == 0)
    {
      j = -1;
      while (++j < 1000)
	if (data->buff.term_buff[j])
	  {
	    bunny_free(data->buff.term_buff[j]);
	    data->buff.term_buff[j] = NULL;
	  }
      data->buff.x_idx = 0;
      data->buff.y_idx = 0;
      data->buff.scroll = 0;
      check_if_y(data);
      *i += 11;
    }
}
