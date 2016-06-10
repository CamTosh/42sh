/*
** kala_style.c for kalash in /home/rotaru_i/Coding/LibLap/kalaterm
**
** Made by ROTARU Iulian
** Login   <rotaru_i@epitech.net>
**
** Started on  Sun Jun  5 01:12:24 2016 ROTARU Iulian
** Last update Sun Jun  5 07:44:53 2016 ROTARU Iulian
*/

#include "kalas.h"

void	kala_slam_second(t_kala *data)
{
  bunny_blit(&data->win->buffer, data->shard, &data->intro.blit);
  data->intro.blit.x = (data->win->buffer.width / 2
			- data->logo->buffer.width / 2)
    + ((rand() % (int)(data->intro.slam + 1))
       - data->intro.slam / 2) + data->logo->origin.x;
  data->intro.blit.y = (data->win->buffer.height / 2
			- data->logo->buffer.height / 2)
    + ((rand() % (int)(data->intro.slam + 1))
       - data->intro.slam / 2) + data->logo->origin.y;
  data->logo->rotation = (rand() % (int)((data->intro.slam / 5) + 1)
			  - data->intro.slam / 10);
  bunny_blit(&data->win->buffer, data->logo, &data->intro.blit);
  bunny_display(data->win);
  data->intro.slam -= 1.2;
}

void	kala_slam(t_kala *data)
{
  if (data->intro.state == 3)
    {
      bunny_clear(&data->win->buffer, 0xFF000000);
      data->intro.blit.x = (data->win->buffer.width / 2
			    - data->shard->buffer.width / 2)
	+ ((rand() % (int)(data->intro.slam + 1))
	   - data->intro.slam / 2) + data->shard->origin.x;
      data->intro.blit.y = (data->win->buffer.height / 2
			    - data->shard->buffer.height / 2)
	+ ((rand() % (int)(data->intro.slam + 1))
	   - data->intro.slam / 2) + data->shard->origin.y;
      data->shard->rotation = (rand() % (int)((data->intro.slam / 5) + 1)
			       - data->intro.slam / 10);
      kala_slam_second(data);
      if (data->intro.slam <= 0.0)
	{
	  data->intro.state = 4;
	  data->intro.slam = 0.0;
	  data->intro.black.full = 0;
	}
    }
}

void	kala_afterslam_second(t_kala *data)
{
  data->intro.blit.x = (data->win->buffer.width / 2
			- data->logo->buffer.width / 2)
    + ((rand() % (int)(data->intro.slam + 1))
       - data->intro.slam / 2) + data->logo->origin.x;
  data->intro.blit.y = (data->win->buffer.height / 2
			- data->logo->buffer.height / 2)
    + ((rand() % (int)(data->intro.slam + 1))
       - data->intro.slam / 2) + data->logo->origin.y;
  data->logo->rotation = (rand() % (int)((data->intro.slam / 5) + 1)
			  - data->intro.slam / 10);
  bunny_blit(&data->win->buffer, data->logo, &data->intro.blit);
  bunny_display(data->win);
  data->intro.black.argb[3] += 1;
}

void	kala_afterslam(t_kala *data)
{
  if (data->intro.state == 4)
    {
      bunny_fill(&data->shard->buffer, data->intro.black.full);
      bunny_clear(&data->win->buffer, 0xFF000000);
      data->intro.blit.x = (data->win->buffer.width / 2
			    - data->shard->buffer.width / 2)
	+ ((rand() % (int)(data->intro.slam + 1))
	   - data->intro.slam / 2) + data->shard->origin.x;
      data->intro.blit.y = (data->win->buffer.height / 2
			    - data->shard->buffer.height / 2)
	+ ((rand() % (int)(data->intro.slam + 1))
	   - data->intro.slam / 2) + data->shard->origin.y;
      data->shard->rotation = (rand() % (int)((data->intro.slam / 5) + 1)
			       - data->intro.slam / 10);
      bunny_blit(&data->win->buffer, data->shard, &data->intro.blit);
      kala_afterslam_second(data);
      if (data->intro.black.argb[3] >= 50)
	{
	  data->intro.state = 5;
	  data->intro.black.full = 0x00000000;
	}
    }
}

void	kala_end_fade(t_kala *data)
{
  if (data->intro.state == 5)
    {
      bunny_fill(&data->bg->buffer, data->intro.black.full);
      bunny_blit(&data->win->buffer, data->bg, NULL);
      bunny_display(data->win);
      data->intro.black.argb[3] += 1;
      if (data->intro.black.argb[3] >= 70)
	data->intro.state = 6;
    }
  if (data->intro.state == 6)
    {
      bunny_delete_clipable(data->logo);
      bunny_delete_clipable(data->shard);
      bunny_sound_stop((t_bunny_sound *)data->draa);
      bunny_delete_sound((t_bunny_sound *)data->draa);
      bunny_set_loop_main_function((t_bunny_loop)kala_loop);
    }
}
