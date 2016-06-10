/*
** job.h for KalaSH in /home/rotaru_i/Coding/42sh/srcs/ll
**
** Made by ROTARU Iulian
** Login   <rotaru_i@epitech.net>
**
** Started on  Sat Jun  4 06:45:02 2016 ROTARU Iulian
** Last update Sun Jun 05 20:35:01 2016 ALIF Matthias
*/

#ifndef JOB_H_
# define JOB_H_

# include <termios.h>

typedef struct		s_proc
{
  struct s_proc		*next;
  char			**cmd;
  pid_t			pid;
  t_bool		complete;
  t_bool		stopped;
  int			status;
}			t_proc;

typedef struct		s_job
{
  int			bg;
  struct s_job		*next;
  char			*cmd;
  pid_t			pgid;
  t_proc		*leader;
  struct termios	save;
  int			fds[3];
}			t_job;

# define EXEC_FCT(x) (((x) < 4) ? ((x) - 1) : (3))

#endif /* !JOB_H_ */
