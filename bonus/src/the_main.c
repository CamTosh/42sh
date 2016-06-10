/*
** main.c for kalaSH in /home/rotaru_i/termi_kalaSH
**
** Made by Iulian Rotaru
** Login   <rotaru_i@epitech.net>
**
** Started on  Wed May 25 17:03:07 2016 Iulian Rotaru
** Last update Sun Jun  5 22:01:21 2016 ROTARU Iulian
*/

#include "kalas.h"

t_bunny_response	kala_intro(t_kala *data)
{
  kala_start_fade(data);
  kala_zoom(data);
  kala_setup_one(data);
  kala_slam(data);
  kala_afterslam(data);
  kala_end_fade(data);
  return (GO_ON);
}

int	start_check(t_kala *data, char *av[])
{
  nset(data, sizeof(data));
  nset(&data->buff, sizeof(t_aff));
  if (!(data->win = bunny_start(1700, 900, 0, "kalaSH"))
      || !(data->pix = bunny_new_pixelarray(1700, 900))
      || !(data->font = bunny_load_pixelarray("./res/font.png"))
      || !(data->logo = bunny_load_picture("./res/kalaSH.png"))
      || !(data->shard = bunny_load_picture("./res/fissure.png"))
      || !(data->bg = bunny_load_picture("./res/kalaBG.png"))
      || !(data->bg_pix = bunny_load_pixelarray("./res/kalaSH_work.png"))
      || !(data->bg_filtre = bunny_new_pixelarray(1700, 900))
      || !(data->draa = bunny_load_music("./res/best.ogg"))
      || !(data->buff.term_buff = bunny_malloc(sizeof(char *)
					       * (SCROLL_HISTORY + 1)))
      || !(data->buff.read_buff = bunny_malloc(sizeof(char) * (4097))))
    return (1);
  nset(data->buff.term_buff, sizeof(char *) * (SCROLL_HISTORY + 1));
  if (access(*(av + 1), F_OK))
    return (writerr("Usage: Given parameter can't be used as shell\n", 1));
  return (0);
}

int		main(int ac, char *av[], char *env[])
{
  t_kala	data;

  if (ac == 1)
    return (writerr("Usage: ./kalaSH path_to_shell\n", 1));
  if (start_check(&data, av) == 1)
    return (1);
  data.round = 256;
  data.shell = *(av + 1);
  data.env = env;
  data.buff.text.police_size = 21;
  data.buff.text.x = 5;
  data.buff.text.y = 7;
  data.intro.state = 0;
  data.pty_setup = false;
  bunny_set_key_response((t_bunny_key)kala_key);
  bunny_set_loop_main_function((t_bunny_loop)kala_intro);
  bunny_set_text_response((t_bunny_type)kala_type);
  kala_intro(&data);
  bunny_loop(data.win, 60, &data);
  if (waitpid(data.pty.child_pid, &data.pty.child_status, WNOHANG) <= 0)
    kill(data.pty.child_pid, SIGKILL);
  bunny_delete_clipable(&data.pix->clipable);
  bunny_stop(data.win);
  return (GO_ON);
}
