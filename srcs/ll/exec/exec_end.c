/*
** exec_end.c for KalaSH in /home/rotaru_i/Coding/42sh
**
** Made by ROTARU Iulian
** Login   <rotaru_i@epitech.net>
**
** Started on  Sun Jun  5 19:54:12 2016 ROTARU Iulian
** Last update Sun Jun  5 22:09:32 2016 ROTARU Iulian
*/

#include <signal.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <unistd.h>
#include "kala.h"
#include "utils.h"
#include "ll.h"

static const t_built_tab	g_built[] = {
  {"env", &my_env},
  {"setenv", &my_setenv},
  {"unsetenv", &my_unsetenv},
  {"alias", &alias_handle},
  {"unalias", &unalias_handle},
  {"cd", &my_cd},
  {"echo", &my_echo},
  {"exit", &my_exit}
};

void	check_status_cases(int status, pid_t ret,
			   t_shell *shell, t_lexem *node)
{
  if (WIFSIGNALED(status) && (status = WTERMSIG(status)) != 13)
    {
      my_dprintf(STDERR_FILENO, "(%d) %s Interrupted by %s (%d)\n",
		 ret, *node->av,
		 (status == 8
		  ? "Floating point exception" : status == 11
		  ? "Segmentation Fault" : "Signal"), status);
      shell->exit.status = 128 + status;
    }
}

t_bool	exec_it(t_lexem *node, t_shell *shell)
{
  int	status;
  pid_t	ret;

  ret = 0;
  if ((node->is_pipe == FALSE) && (ret = fork()) < 0)
    return (FALSE);
  if (ret == 0)
    {
      signal(SIGINT, SIG_DFL);
      execve(*node->av, node->av, shell->env);
      return (FALSE);
    }
  if (waitpid(ret, &status, WCONTINUED) < 0)
    return (FALSE);
  shell->exit.status = shell->exit.should_exit == TRUE
    ? shell->exit.status : WEXITSTATUS(status);
  if (!WIFEXITED(status))
    check_status_cases(status, ret, shell, node);
  return (CONTINUE);
}

t_bool		my_select(t_lexem *node, t_shell *shell)
{
  unsigned int	idx;

  if (!(node->av = wtab(node->str)))
    return (FALSE);
  idx = 0;
  while ((idx < BUILT_SIZE)
	 && (strcmp(node->av[0], g_built[idx].str) != MATCH))
    ++idx;
  if (idx < BUILT_SIZE)
    return (g_built[idx].fct(node, shell));
  return (check_command(node, shell));
}

t_bool	launch_dup(t_lexem *node, int *save)
{
  if (node->fd[STDIN_FILENO] != STDIN_FILENO)
    {
      if ((save[STDIN_FILENO] = dup(STDIN_FILENO)) < 0
	  || (dup2(node->fd[STDIN_FILENO], STDIN_FILENO)) < 0)
	return (FALSE);
    }
  if (node->fd[STDOUT_FILENO] != STDOUT_FILENO)
    {
      if ((save[STDOUT_FILENO] = dup(STDOUT_FILENO)) < 0
	  || (dup2(node->fd[STDOUT_FILENO], STDOUT_FILENO)) < 0)
	return (FALSE);
    }
  if (node->fd[STDERR_FILENO] != STDERR_FILENO)
    {
      if ((save[STDERR_FILENO] = dup(STDERR_FILENO)) < 0
	  || (dup2(node->fd[STDERR_FILENO], STDERR_FILENO)) < 0)
	return (FALSE);
    }
  return (CONTINUE);
}

t_bool	reset_dup(t_lexem *node, int *save)
{
  if (((node->fd[STDIN_FILENO] != STDIN_FILENO)
       && (dup2(save[STDIN_FILENO], STDIN_FILENO) < 0))
      || ((node->fd[STDOUT_FILENO] != STDOUT_FILENO)
	  && (dup2(save[STDOUT_FILENO], STDOUT_FILENO) < 0))
      || ((node->fd[STDERR_FILENO] != STDERR_FILENO)
	  && (dup2(save[STDERR_FILENO], STDERR_FILENO)) < 0))
    return (FALSE);
  return ((node->is_pipe == FALSE) ? (CONTINUE) : (TRUE));
}
