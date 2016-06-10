/*
** loop.c for kalash in /home/rotaru_i/Coding/LibLap/kalaterm
**
** Made by ROTARU Iulian
** Login   <rotaru_i@epitech.net>
**
** Started on  Sun Jun  5 01:09:59 2016 ROTARU Iulian
** Last update Sun Jun  5 22:01:01 2016 ROTARU Iulian
*/

#include "kalas.h"

t_bunny_response	kala_loop(t_kala *data)
{
  t_bunny_position	blit;

  if ((data->pty_setup == false) && (summon_pty(data) == -1))
    return (-1);
  check_master(data);
  fill(data->pix, 0);
  fill(data->bg_filtre, 0);
  blit.x = (data->pix->clipable.buffer.width
	    - data->bg_pix->clipable.buffer.width) / 2;
  blit.y = (data->pix->clipable.buffer.height
	    - data->bg_pix->clipable.buffer.height) / 2;
  my_bunny_blit(data->pix, data->bg_pix, &blit, 1);
  update_logo(data);
  bunny_blit(&data->win->buffer, data->bg, NULL);
  aff_master(data);
  bunny_blit(&data->win->buffer, &data->pix->clipable, NULL);
  bunny_display(data->win);
  if (waitpid(data->pty.child_pid, &data->pty.child_status, WNOHANG) > 0)
    return (EXIT_SUCCESS);
  data->round += 4;
  return (GO_ON);
}

t_bunny_response	kala_type(uint32_t unicode,
				  t_kala *data)
{
  if (unicode == 8)
    unicode = 127;
  write(data->pty.fd_master, &unicode, 1);
  return (GO_ON);
}

void	kala_start_fade(t_kala *data)
{
  if (data->intro.state == 0)
    {
      data->intro.slam = 100.0;
      data->intro.dezoom = 0.01;
      data->intro.blit.x = data->win->buffer.width / 2
	- data->logo->buffer.width / 2;
      data->intro.blit.y = data->win->buffer.height / 2
	- data->logo->buffer.height / 2;
      data->logo->scale.x = 10.0;
      data->logo->scale.y = 10.0;
      data->intro.state = 1;
      data->intro.round = 0;
      data->intro.black.full = 0xFF000000;
      bunny_sound_play((t_bunny_sound *)data->draa);
    }
}

void	kala_zoom(t_kala *data)
{
  if (data->intro.state == 1)
    {
      bunny_clear(&data->win->buffer, 0xFF000000);
      data->logo->scale.x -= data->intro.dezoom;
      data->logo->scale.y -= data->intro.dezoom;
      data->intro.dezoom *= 1.0 + data->intro.dezoom;
      if (data->logo->scale.x < 1.0)
	{
	  data->logo->scale.x = 1.0;
	  data->logo->scale.y = 1.0;
	}
      if (data->intro.round % 2 == 0)
	data->intro.black.argb[3] -= 1;
      bunny_blit(&data->win->buffer, data->logo, &data->intro.blit);
      bunny_fill(&data->win->buffer, data->intro.black.full);
      bunny_display(data->win);
      ++data->intro.round;
      if (data->logo->scale.x <= 1.0)
	data->intro.state = 2;
    }
}

void	kala_setup_one(t_kala *data)
{
  if (data->intro.state == 2)
    {
      data->logo->origin.x = data->logo->buffer.width / 2;
      data->logo->origin.y = data->logo->buffer.height / 2;
      data->shard->origin.x = data->shard->buffer.width / 2;
      data->shard->origin.y = data->shard->buffer.height / 2;
      data->intro.state = 3;
    }
}
