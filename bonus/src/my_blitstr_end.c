/*
** my_blitstr_end.c for RTV2 in /home/rotaru_i
**
** Made by
** Login   <rotaru_i@epitech.net>
**
** Started on  Sat May  7 19:21:39 2016
** Last update Fri Jun  3 16:23:11 2016 ROTARU Iulian
*/

#include "kalas.h"

void	set_start_nb(t_bunny_position *pos, t_text *text, int ratio, int j)
{
  pos[2].x = text->pos.x + (ratio * 6 * j);
  pos[2].y = text->pos.y;
  pos[0].y = 0;
  pos[1].y = text->y;
}

void	ratio_setter(int *ratio, t_text *text)
{
  *ratio = text->police_size / 7;
  if (*ratio == 0)
    *ratio = 1;
}

static void	apply_colors_text(t_area_text *v)
{
  if (v->ptrr[(v->y + v->area[0].y) *
	      v->extract->clipable.clip_width +
	      (v->x + v->area[0].x)])
    v->ptr[(v->blit.y + (v->y) * (v->ratio) + v->j) *
	   v->pix->clipable.clip_width +
	   v->blit.x + (v->x) * (v->ratio) + v->i]
      = color_mixer(v->ptr[(v->blit.y + (v->y) * (v->ratio) + v->j) *
			   v->pix->clipable.clip_width +
			   v->blit.x + (v->x) * (v->ratio) + v->i],
		    v->text->fg);
  else
    v->ptr[(v->blit.y + (v->y) * (v->ratio) + v->j) *
	   v->pix->clipable.clip_width +
	   v->blit.x + (v->x) * (v->ratio) + v->i]
      = color_mixer(v->ptr[(v->blit.y + (v->y) * (v->ratio) + v->j) *
			   v->pix->clipable.clip_width +
			   v->blit.x + (v->x) * (v->ratio) + v->i],
		    v->text->bg);
}

static void	main_under_boucle(t_area_text *v)
{
  while (v->x < v->area[1].x - v->area[0].x)
    {
      v->i = 0;
      while (v->i < v->ratio)
	{
	  apply_colors_text(v);
	  v->i++;
	}
      v->x++;
    }
}

void	main_boucle(t_area_text *v)
{
  while (v->y < v->area[1].y - v->area[0].y)
    {
      v->j = 0;
      while (v->j < v->ratio)
	{
	  v->x = 0;
	  main_under_boucle(v);
	  v->j++;
	}
      v->y++;
    }
}
