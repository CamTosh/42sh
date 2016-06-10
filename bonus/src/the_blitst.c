/*
** blitst.c for kalash in /home/rotaru_i/Coding/LibLap/kalaterm
**
** Made by ROTARU Iulian
** Login   <rotaru_i@epitech.net>
**
** Started on  Sun Jun  5 01:32:32 2016 ROTARU Iulian
** Last update Sun Jun  5 07:48:01 2016 ROTARU Iulian
*/

#include "kalas.h"

static unsigned int	g_tab[][2] =
  {
    {0, 0xFFDDDDDD},
    {30, BLACK},
    {40, BLACK},
    {31, RED},
    {41, RED},
    {32, GREEN},
    {42, GREEN},
    {33, YELLOW},
    {43, YELLOW},
    {34, BLUE},
    {44, BLUE},
    {35, PINK},
    {45, PINK},
    {36, BLUE | GREEN},
    {46, BLUE | GREEN},
    {37, 0xFF888888},
    {47, 0xFF888888}
  };

int	get_all_codes(const char *str, int i, int **recup)
{
  int	out;

  out = i + 1;
  *recup = NULL;
  while (*(str + out))
    {
      if (out == i + 1 && *(str + out) != '[')
	return (0);
      else if (out == i + 1 && *(str + out) == '[')
	++out;
      if (*(str + out) >= '0' && *(str + out) <= '9')
	add_nb(str, &out, recup);
      else if (*(str + out) == ';')
	++out;
      else
	break ;
    }
  if (*(str + out) == 'm')
    return (out - i);
  return (0);
}

void		parse_glob(int *recup, int idx, t_text *text)
{
  int		scan;
  unsigned int	tmp;

  scan = -1;
  while (++scan < 17)
    {
      if ((int)g_tab[scan][0] == *(recup + idx + 1))
	text->fg = g_tab[scan][1];
      else if (*(recup + idx + 1) == 7)
	{
	  tmp = text->bg;
	  text->bg = text->fg;
	  text->fg = tmp;
	}
      if (*(recup + idx + 1) == 0)
	text->bg = 0;
    }
}

void	analyse_codes(const char *str, int *i, t_text *text, t_bunny_position *pos)
{
  int	*recup;
  int	move;
  int	idx;

  move = get_all_codes(str, *i, &recup);
  if (move == 0 || recup == NULL)
    return ;
  idx = -1;
  while (++idx < *recup)
    parse_glob(recup, idx, text);
  pos[2].x -= 6 * 3;
  *i += move;
  bunny_free(recup);
}

void			my_blitstr(char *str,
				   t_bunny_pixelarray *pix,
				   t_bunny_pixelarray *text_pix,
				   t_text *text)
{
  t_bunny_position	pos[3];
  int			i;
  int			ratio;

  if (!str || !pix || !text_pix || !text)
    return ;
  ps(pos, text);
  if (!(ratio = text->police_size / 7))
    ratio = 1;
  i = 0;
  while (str[i])
    {
      pos[0].x = text->x * str[i];
      pos[1].x = text->x * (str[i] + 1);
      if (str[i] == '\033')
	analyse_codes(str, &i, text, pos);
      else if ((str[i] > ' ' &&
		pos[2].x >= 0 && pos[2].x < pix->clipable.clip_width)
	       && (pos[2].x + 6 * ratio >= 0 &&
		   pos[2].x + 6 * ratio < pix->clipable.clip_width))
	copy_area(pix, text_pix, pos, text);
      i++;
      pos[2].x += 6 * ratio;
    }
}
