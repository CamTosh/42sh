/*
** my_blitstr.c for liblap in /home/rotaru_i
**
** Made by Iulian Rotaru
** Login   <rotaru_i@epitech.net>
**
** Started on  Tue Feb  2 17:31:01 2016 Iulian Rotaru
** Last update Sun Jun  5 01:39:49 2016 ROTARU Iulian
*/

#include "kalas.h"

void		copy_area(t_bunny_pixelarray *pix,
			  t_bunny_pixelarray *extract,
			  t_bunny_position *area,
			  t_text *text)
{
  t_area_text	v;

  v.text = text;
  v.ratio = v.text->police_size / 7;
  if (v.ratio == 0)
    v.ratio = 1;
  v.ptr = (unsigned int*) pix->pixels;
  v.ptrr = (unsigned int*) extract->pixels;
  v.blit.x = area[2].x;
  v.blit.y = area[2].y;
  v.y = 0;
  v.pix = pix;
  v.extract = extract;
  v.area = area;
  main_boucle(&v);
}

void	ps(t_bunny_position *pos, t_text *text)
{
  pos[2].x = text->pos.x;
  pos[2].y = text->pos.y;
  pos[0].y = 0;
  pos[1].y = text->y;
}

void	my_blitnbr(int nb,
		   t_bunny_pixelarray *pix,
		   t_bunny_pixelarray *text_pix,
		   t_text *text)
{
  int	i[2];
  char	buffer[11];
  int	multi;

  i[0] = 0;
  if (nb < 0)
    {
      i[0] = 1;
      nb = -nb;
      *buffer = '-';
    }
  multi = 1;
  i[1] = nb;
  while ((i[1] /= 10) != 0)
    multi *= 10;
  *(buffer + i[0]) = (nb / multi) + 48;
  while (multi != 0)
    {
      *(buffer + i[0]) = (nb / multi) + 48;
      nb = nb % multi;
      multi = multi / 10;
      ++i[0];
    }
  *(buffer + i[0]) = 0;
  my_blitstr(buffer, pix, text_pix, text);
}

int	nbr_plus(const char *nb, int *forward)
{
  int	i;
  int	mult;
  int	out;

  i = 0;
  while (*(nb + i) && *(nb + i) >= '0' && *(nb + i) <= '9')
    ++i;
  *forward = i;
  --i;
  mult = 1;
  out = 0;
  while (i >= 0)
    {
      out += (*(nb + i) - 48) * mult;
      mult *= 10;
      --i;
    }
  return (out);
}

void	add_nb(const char *str, int *out, int **recup)
{
  int	get[2];
  int	*tmp;
  int	i;

  get[0] = nbr_plus(str + *out, get + 1);
  if (!*recup)
    {
      if (!(*recup = bunny_malloc(sizeof(int) * 2)))
	return ;
      **recup = 1;
      *(*recup + 1) = get[0];
    }
  else if (*recup)
    {
      if (!(tmp = bunny_malloc(sizeof(int) * (**recup + 2))))
	return ;
      i = -1;
      *tmp = **recup + 1;
      while (++i < **recup)
	*(tmp + i + 1) = *(*recup + i + 1);
      *(tmp + i + 1) = get[0];
      bunny_free(*recup);
      *recup = tmp;
    }
  *out += get[1];
}
