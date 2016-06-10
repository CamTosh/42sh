/*
** pty_setup.c for kalash in /home/rotaru_i/Coding/LibLap/kalaterm
**
** Made by ROTARU Iulian
** Login   <rotaru_i@epitech.net>
**
** Started on  Sun Jun  5 01:04:29 2016 ROTARU Iulian
** Last update Sun Jun  5 22:00:07 2016 ROTARU Iulian
*/

#include "kalas.h"

int	start_up_pty(t_kala *data)
{
  if ((data->pty.fd_master = posix_openpt(O_RDWR)) < 0)
    return (writerr("Error: PTY can't be summoned...\n", -1));
  if (grantpt(data->pty.fd_master) != 0)
    return (writerr("Error: can't change access rights on slave...\n", -1));
  if (unlockpt(data->pty.fd_master) != 0)
    return (writerr("Error: can't unlock slave part of PTY...\n", -1));
  if ((data->pty.fd_slave = open(ptsname(data->pty.fd_master), O_RDWR)) < 0)
    return (writerr("Error: PTY's slave can't be opened...\n", -1));
  return (0);
}

int	master_side(t_kala *data)
{
  int	flags;

  close(data->pty.fd_slave);
  FD_ZERO(&data->pty.fd_zero);
  FD_SET(0, &data->pty.fd_zero);
  FD_SET(data->pty.fd_master, &data->pty.fd_zero);
  flags = fcntl(data->pty.fd_master, F_GETFL, 0);
  fcntl(data->pty.fd_master, F_SETFL, flags | O_NONBLOCK);
  return (0);
}

int			slave_side(t_kala *data)
{
  char			*prog[2];
  struct winsize	size;

  close(data->pty.fd_master);
  ioctl(data->pty.fd_slave, TIOCGWINSZ, &size);
  size.ws_col = 90;
  size.ws_row = 31;
  close(0);
  close(1);
  close(2);
  dup(data->pty.fd_slave);
  dup(data->pty.fd_slave);
  dup(data->pty.fd_slave);
  close(data->pty.fd_slave);
  setsid();
  ioctl(0, TIOCSCTTY, 1);
  *prog = data->shell;
  *(prog + 1) = NULL;
  execve(*prog, prog, data->env);
  exit(1);
  return (0);
}

int	summon_pty(t_kala *data)
{
  if (start_up_pty(data) == -1)
    return (-1);
  if ((data->pty.child_pid = fork()))
    {
      if (master_side(data) == -1)
	return (-1);
    }
  else if (slave_side(data) == -1)
    return (-1);
  data->pty_setup = true;
  return (0);
}

char	*sdup(const char *str)
{
  int	i;
  char	*out;

  if (!(out = bunny_malloc(sizeof(char) * (len(str) + 1))))
    return (NULL);
  nset(out, len(str) + 1);
  i = -1;
  while (*(str + ++i))
    *(out + i) = *(str + i);
  return (out);
}
