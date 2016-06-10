/*
** kala_key.c for kalash in /home/rotaru_i/Coding/LibLap/kalaterm
**
** Made by ROTARU Iulian
** Login   <rotaru_i@epitech.net>
**
** Started on  Sun Jun  5 00:56:52 2016 ROTARU Iulian
** Last update Sun Jun  5 21:56:53 2016 ROTARU Iulian
*/

#include "kalas.h"

static char	*(g_keys[]) =
{
  "\x1b\x5b\x41",
  "\x1b\x5b\x42",
  "\x1b\x5b\x43",
  "\x1b\x5b\x44",
  NULL
};

t_bunny_response	kala_key_end(t_bunny_event_state state,
				     t_bunny_keysym sym,
				     t_kala *data)
{
  if (state == GO_DOWN && sym == BKS_DOWN && bunny_get_keyboard()[BKS_LALT])
    data->buff.scroll = data->buff.scroll > 0
      ? data->buff.scroll - 1 : data->buff.scroll;
  else if (state == GO_DOWN && sym == BKS_DOWN)
    write(data->pty.fd_master, g_keys[1], len(g_keys[1]));
  if (state == GO_DOWN && sym == BKS_RIGHT)
    write(data->pty.fd_master, g_keys[2], len(g_keys[2]));
  if (state == GO_DOWN && sym == BKS_LEFT)
    write(data->pty.fd_master, g_keys[2], len(g_keys[2]));
  return (GO_ON);
}

t_bunny_response	kala_key(t_bunny_event_state state,
				 t_bunny_keysym sym,
				 t_kala *data)
{
  if (state == GO_DOWN && sym == BKS_ESCAPE)
    return (EXIT_SUCCESS);
  if (state == GO_DOWN && sym == BKS_L && bunny_get_keyboard()[BKS_LCONTROL])
    write(data->pty.fd_master, "\nclear\n", 7);
  if (state == GO_DOWN && sym == BKS_UP && bunny_get_keyboard()[BKS_LALT])
    data->buff.scroll = data->buff.scroll < data->buff.y_idx - 31
      ? data->buff.scroll + 1 : data->buff.scroll;
  else if (state == GO_DOWN && sym == BKS_UP)
    write(data->pty.fd_master, g_keys[0], len(g_keys[0]));
  return (kala_key_end(state, sym, data));
}
