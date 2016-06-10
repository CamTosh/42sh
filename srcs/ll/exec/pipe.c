/*
** pipe.c for KalaSH in /home/guillaume/Documents/rendu/42sh/PSU_2015_42sh/srcs
**
** Made by Guillaume Benard
** Login   <guillaume@epitech.net>
**
** Started on  Sun Jun  5 01:46:12 2016 Guillaume Benard
** Last update Sun Jun  5 23:22:23 2016 Guillaume Benard
*/

#include <fcntl.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include "kala.h"
#include "ll.h"

t_bool		exec_left(t_lexem *node, t_shell *shell, int *pipefd)
{
  t_bool	ret;

  (void)close(pipefd[0]);
  node->left->fd[STDIN_FILENO] = node->fd[STDIN_FILENO];
  node->left->is_pipe = TRUE;
  if ((ret = g_exec[node->left->type](node->left, shell)) == FALSE)
    return (FALSE);
  (void)close(pipefd[1]);
  return ((node->is_pipe == TRUE) ? (TRUE) : (ret));
}

t_bool		exec_right(t_lexem *node, t_shell *shell, int *pipefd)
{
  t_bool	ret;

  (void)close(pipefd[1]);
  node->right->is_pipe = node->is_pipe;
  node->right->is_from_pipe = TRUE;
  node->right->fd[STDOUT_FILENO] = node->fd[STDOUT_FILENO];
  node->right->fd[STDERR_FILENO] = node->fd[STDERR_FILENO];
  if ((ret = g_exec[node->right->type](node->right, shell)) == FALSE)
    return (FALSE);
  (void)close(pipefd[0]);
  return ((node->is_pipe == TRUE) ? (TRUE) : (ret));
}

t_bool	exec_pipe(t_lexem *node, t_shell *shell)
{
  pid_t	pid;
  int	pipefd[2];

  if (!(node->left) || !(node->right))
    return ((node->is_pipe) ? (TRUE) : (CONTINUE));
  if (pipe(pipefd) != EXIT_SUCCESS)
    return (FALSE);
  node->right->fd[STDIN_FILENO] = pipefd[0];
  node->left->fd[STDOUT_FILENO] = pipefd[1];
  node->left->fd[STDERR_FILENO] = (node->type == PIPE_ERR)
    ? (pipefd[1]) : (STDERR_FILENO);
  if ((pid = fork()) == -1)
    return (FALSE);
  return ((pid == 0) ? (exec_left(node, shell, pipefd))
	  : (exec_right(node, shell, pipefd)));
}
