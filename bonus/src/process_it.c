/*
** process.c for kalash in /home/rotaru_i/Coding/LibLap/kalaterm
**
** Made by ROTARU Iulian
** Login   <rotaru_i@epitech.net>
**
** Started on  Sun Jun  5 01:08:07 2016 ROTARU Iulian
** Last update Sun Jun  5 07:46:39 2016 ROTARU Iulian
*/

#include "kalas.h"

void	process_readings(t_kala *data)
{
  int	i;

  i = -1;
  check_if_y(data);
  while (*(data->buff.read_buff + ++i))
    {
      check_clear(data, &i);
      write_in_term(data, i);
      if ((data->buff.x_idx == 104 || *(data->buff.read_buff + i) == '\n')
	  && data->buff.y_idx < 1000)
	{
	  *(*(data->buff.term_buff + data->buff.y_idx)
	    + data->buff.x_idx + 1) = 0;
	  data->buff.x_idx = -1;
	  max_length_case(data);
	  check_if_y(data);
	}
      ++data->buff.x_idx;
    }
}

void	check_master(t_kala *data)
{
  nset(data->buff.read_buff, 4096);
  if (read(data->pty.fd_master, data->buff.read_buff, 4096) > 0)
    {
      data->buff.scroll = 0;
      process_readings(data);
    }
}

void	fill(t_bunny_pixelarray *pix, unsigned int color)
{
  int	i;

  i = -1;
  while (++i < pix->clipable.buffer.width * pix->clipable.buffer.height)
    *(((unsigned int *)pix->pixels) + i) = color;
}

void		update_logo(t_kala *data)
{
  t_color	black;
  int		i;

  black.full = BLACK;
  if (data->round % 1000 <= 500)
    {
      black.argb[3] = data->round % 500 <= 255
	? data->round % 500
	: 255 - (data->round % 500);
      i = -1;
      while (++i < data->pix->clipable.buffer.width
	     * data->pix->clipable.buffer.height)
	*(((unsigned int *)data->pix->pixels) + i)
	  = color_mixer(*(((unsigned int *)data->pix->pixels) + i),
			black.full);
    }
}

void	aff_master(t_kala *data)
{
  int	y;

  y = data->buff.y_idx - data->buff.scroll <= 31
    ? -1
    : data->buff.y_idx - 32 - data->buff.scroll;
  data->buff.text.fg = 0xFFDDDDDD;
  data->buff.text.pos.x = 0;
  data->buff.text.pos.y = 0;
  while (*(data->buff.term_buff + ++y)
	 && data->buff.text.pos.y + 28
	 < data->pix->clipable.buffer.height)
    {
      if (len(*(data->buff.term_buff + y)))
	my_blitstr(*(data->buff.term_buff + y), data->pix,
		   data->font, &data->buff.text);
      data->buff.text.pos.y += 28;
    }
}
