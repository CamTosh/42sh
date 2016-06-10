/*
** my_bunny_blit.c for liblap in /home/rotaru_i
**
** Made by Iulian Rotaru
** Login   <rotaru_i@epitech.net>
**
** Started on  Tue Feb  2 13:43:37 2016 Iulian Rotaru
** Last update Mon May 30 18:10:40 2016 Iulian Rotaru
*/

#include "kalas.h"

unsigned int	get_mix_color(t_bunny_pixelarray *pix,
			      int idx,
			      unsigned int color)
{
  t_color	one;
  t_color	two;
  t_color	res;
  unsigned int	*ptr;
  double	coeff;

  ptr = (unsigned int*)pix->pixels;
  one.full = color;
  two.full = ptr[idx];
  coeff = (double) two.argb[3] / 256.0;
  res.argb[3] = two.argb[3] * coeff + one.argb[3] * (1 - coeff);
  res.argb[2] = two.argb[2] * coeff + one.argb[2] * (1 - coeff);
  res.argb[1] = two.argb[1] * coeff + one.argb[1] * (1 - coeff);
  res.argb[0] = two.argb[0] * coeff + one.argb[0] * (1 - coeff);
  return (res.full);
}

void	def_set_pos(t_bunny_position *pos,
		    t_bunny_position *place)
{
  if (pos == NULL)
    {
      place->x = 0;
      place->y = 0;
    }
  else
    {
      place->x = pos->x;
      place->y = pos->y;
    }
}

void			colorize(void **sender, int x, int y, int mode)
{
  t_bunny_position	*place;
  t_bunny_pixelarray	*big;
  t_bunny_pixelarray	*small;
  unsigned int		*ptr;
  unsigned int		*ptrr;

  ptr = (unsigned int*)sender[0];
  ptrr = (unsigned int*)sender[1];
  place = (t_bunny_position*)sender[2];
  big = (t_bunny_pixelarray*)sender[3];
  small = (t_bunny_pixelarray*)sender[4];
  if (mode == 1)
    ptr[(place->y + y) * big->clipable.clip_width + x + place->x]
      = get_mix_color(small, (y * small->clipable.clip_width) +
		      x, ptr[(place->y + y) *
			     big->clipable.clip_width + x +
			     place->x]);
  else
    ptr[(place->y + y) * big->clipable.clip_width + x + place->x]
      = ptrr[(y * small->clipable.clip_width) + x];
}

void			my_bunny_blit(t_bunny_pixelarray *big,
				      t_bunny_pixelarray *small,
				      t_bunny_position *pos,
				      int mode)
{
  t_bunny_position	place;
  int			x;
  int			y;
  unsigned int		*ptr;
  unsigned int		*ptrr;
  void			*sender[5];

  ptr = (unsigned int*)big->pixels;
  ptrr = (unsigned int*)small->pixels;
  def_set_pos(pos, &place);
  sender[0] = (void*)ptr;
  sender[1] = (void*)ptrr;
  sender[2] = (void*)&place;
  sender[3] = (void*)big;
  sender[4] = (void*)small;
  y = 0;
  while (y < small->clipable.clip_height)
    {
      x = 0;
      while (x < small->clipable.clip_width)
	colorize(sender, x++, y, mode);
      y++;
    }
}
