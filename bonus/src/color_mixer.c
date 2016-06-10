/*
** color_mixer.c for tekgui in /home/rotaru_i
**
** Made by Iulian Rotaru
** Login   <rotaru_i@epitech.net>
**
** Started on  Thu Feb 25 17:52:56 2016 Iulian Rotaru
** Last update Mon May 30 18:10:49 2016 Iulian Rotaru
*/

#include "kalas.h"

unsigned int	color_mixer(unsigned int one,
			    unsigned int add)
{
  t_color	first;
  t_color	adder;
  t_color	out;
  double	coeff;

  first.full = one;
  adder.full = add;
  coeff = (double)adder.argb[3] / 256.0;
  out.argb[0] = (char)((double)adder.argb[0]
		       * coeff + (double)first.argb[0] * (1.0 - coeff));
  out.argb[1] = (char)((double)adder.argb[1]
		       * coeff + (double)first.argb[1] * (1.0 - coeff));
  out.argb[2] = (char)((double)adder.argb[2]
		       * coeff + (double)first.argb[2] * (1.0 - coeff));
  out.argb[3] = (char)((double)adder.argb[3]
		       * coeff + (double)first.argb[3] * (1.0 - coeff));
  return (out.full);
}
