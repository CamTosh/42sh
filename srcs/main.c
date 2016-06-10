/*
** main.c for 42sh in /home/guillaume/Documents/rendu/42sh/PSU_2015_42sh
**
** Made by Guillaume Benard
** Login   <guillaume@epitech.net>
**
** Started on  Mon May 30 13:30:00 2016 Guillaume Benard
** Last update Sun Jun  5 22:42:59 2016 almazo_t
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <term.h>
#include <sys/ioctl.h>
#include <unistd.h>
#include <signal.h>
#include "kala.h"
#include "job.h"
#include "ll.h"
#include "utils.h"

t_bool	g_sigint = 0;

static int	clean_exit(t_shell *shell, int ret)
{
  free_alias(shell->alias);
  free_history(&shell->hist);
  free_wordtab(shell->env);
  return (ret);
}

static char	*gnl_basic(t_shell UNUSED(*shell))
{
  return (get_next_line(STDIN_FILENO));
}

static char	*(*g_gnl[])(t_shell *shell) = {
  &gnl_basic,
  &gnl_ncurse
};

static t_bool		shell_loop(t_shell *shell)
{
  char			*line;
  struct termios	save[2];

  if ((shell->opt[NCURSE] == TRUE) && (!(load_keys(shell, shell->env))
				       || (gogo_ncurse(save) == EXIT_FAILURE)))
    return (FALSE);
  while ((shell->exit.should_exit == FALSE)
	 && (line = g_gnl[shell->opt[NCURSE]](shell)))
    {
      if (shell->opt[NCURSE] == TRUE && (ioctl(0, TCSETS, &save[0])) < 0)
	return (FALSE);
      if (lets_pars(shell, line) != CONTINUE)
	shell->exit.should_exit = TRUE;
      shell->lexem = NULL;
      if (add_in_hist(&shell->hist, line) == FALSE)
	return (FALSE);
      if (shell->opt[NCURSE] == TRUE && (ioctl(0, TCSETS, &save[1])) < 0)
      	return (FALSE);
      shell->rando = rand() % 6 + 31;
    }
  if (shell->opt[NCURSE] == TRUE
      && (ioctl(0, TCSETS, &save[0])) < 0)
    return (FALSE);
  return (TRUE);
}

void		sig_handle(int sig)
{
  if (sig == SIGINT)
    {
      my_dprintf(2, "\n\033[1;32m|-| \033[1;31mKalaSH \033[1;32m>\033[0m ");
      g_sigint = 1;
    }
}

int		main(int UNUSED(ac), char *const av[], char *const env[])
{
  t_shell	shell;

  (void)av;
  bzero(&shell, sizeof(t_shell));
  shell.opt[NCURSE] = isatty(STDIN_FILENO);
  signal(SIGTSTP, SIG_IGN);
  signal(SIGINT, sig_handle);
  srand(getpid());
  shell.rando = rand() % 6 + 31;
  shell.jobs = NULL;
  if (shell.opt[NCURSE])
    shell.hist = create_history();
  shell.last_hist = NULL;
  if (!(shell.env = dup_wordtab(env))
      || !(shell.com.paths = env_field_to_wordtab(PATH_FIELD, shell.env))
      || !(shell_loop(&shell))
      || (shell.opt[NCURSE] == TRUE && !(write_history(shell.hist))))
    return (EXIT_FAILURE);
  return (clean_exit(&shell, shell.exit.status));
}
