/*
** dir.c for KalaSH in /home/guillaume/Documents/rendu/42sh/PSU_2015_42sh
**
** Made by Guillaume Benard
** Login   <guillaume@epitech.net>
**
** Started on  Sun Jun  5 01:40:16 2016 Guillaume Benard
** Last update Sun Jun  5 23:21:28 2016 Guillaume Benard
*/

#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include "kala.h"
#include "ll.h"
#include "utils.h"

static int	open_file(t_lexem *lex, int flag, mode_t mode)
{
  char		**w;
  char		*tmp;
  int		fd;

  if (!(w = wtab(lex->str)))
    return (-1);
  tmp = lex->str;
  lex->str = *w;
  *w = tmp;
  free_wordtab(w);
  if (access(lex->str, F_OK) != 0 && flag == O_RDONLY)
    {
      my_dprintf(STDERR_FILENO, "%s: %s\n", lex->str, NO_SUCH);
      return (-1);
    }
  if ((fd = open(lex->str, flag, mode)) < 0)
    {
      my_dprintf(STDERR_FILENO, "%s: %s\n", lex->str, PERMISSION_DENIED);
      return (-1);
    }
  return (fd);
}

t_bool		exec_ldir(t_lexem *node, t_shell *shell)
{
  int		fd;
  t_bool	ret;

  if (!(node->right))
    return (CONTINUE);
  if ((fd = open_file(node, O_RDONLY, 00644)) < 0)
    return (CONTINUE);
  node->right->fd[STDIN_FILENO] = fd;
  node->right->fd[STDOUT_FILENO] = node->fd[STDOUT_FILENO];
  node->right->fd[STDERR_FILENO] = node->fd[STDERR_FILENO];
  ret = g_exec[node->right->type](node->right, shell);
  if (close(fd) < 0)
    return (FALSE);
  return (ret);
}

t_bool	exec_dldir(t_lexem *node, t_shell *shell)
{
  if (!(node->right))
    return (CONTINUE);
  node->right->fd[STDIN_FILENO] = node->fd[STDIN_FILENO];
  node->right->fd[STDOUT_FILENO] = node->fd[STDOUT_FILENO];
  node->right->fd[STDERR_FILENO] = node->fd[STDERR_FILENO];
  return (g_exec[node->right->type](node->right, shell));
}

t_bool		exec_rdir(t_lexem *node, t_shell *shell)
{
  int		fd;
  t_bool	ret;

  if (!(node->left))
    return (CONTINUE);
  if ((fd = open_file(node, O_WRONLY | O_CREAT | O_TRUNC, 00644)) < 0)
    return (CONTINUE);
  node->left->fd[STDIN_FILENO] = node->fd[STDIN_FILENO];
  node->left->fd[STDOUT_FILENO] = fd;
  node->left->fd[STDERR_FILENO] = (node->type == RDIR_ERR)
    ? (fd) : (node->fd[STDERR_FILENO]);
  ret = g_exec[node->left->type](node->left, shell);
  if (close(fd) < 0)
    return (FALSE);
  return (ret);
}

t_bool		exec_drdir(t_lexem *node, t_shell *shell)
{
  int		fd;
  t_bool	ret;

  if (!(node->left))
    return (CONTINUE);
  if ((fd = open_file(node, O_WRONLY | O_CREAT | O_APPEND, 00644)) < 0)
    return (CONTINUE);
  node->left->fd[STDIN_FILENO] = node->fd[STDIN_FILENO];
  node->left->fd[STDOUT_FILENO] = fd;
  node->left->fd[STDERR_FILENO] = (node->type == DRDIR_ERR)
    ? (fd) : (node->fd[STDERR_FILENO]);
  ret = g_exec[node->left->type](node->left, shell);
  if (close(fd) < 0)
    return (FALSE);
  return (ret);
}
