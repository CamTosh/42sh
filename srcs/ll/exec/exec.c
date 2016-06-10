/*
** exec.c for KalaSH in /home/guillaume/Documents/rendu/42sh/PSU_2015_42sh/
**
** Made by Guillaume Benard
** Login   <guillaume@epitech.net>
**
** Started on  Sun Jun  5 01:21:17 2016 Guillaume Benard
** Last update Sun Jun  5 23:20:02 2016 Guillaume Benard
*/

#include <stdlib.h>
#include "kala.h"
#include "ll.h"

t_bool	(*const g_exec[])(t_lexem *node, t_shell *shell) = {
  &exec_semi,
  &exec_or,
  &exec_and,
  &exec_ldir,
  &exec_dldir,
  &exec_pipe,
  &exec_pipe,
  &exec_rdir,
  &exec_rdir,
  &exec_drdir,
  &exec_drdir,
  &exec_semi,
  &exec_cmd
};

t_bool		exec_semi(t_lexem *node, t_shell *shell)
{
  t_bool	ret;

  if (!(node->left) || !(node->right))
    return (CONTINUE);
  if ((node->left)
      && ((ret = g_exec[node->left->type](node->left, shell)) != CONTINUE))
    return (ret);
  if ((node->right)
      && ((ret = g_exec[node->right->type](node->right, shell)) != CONTINUE))
    return (ret);
  return (CONTINUE);
}

t_bool		exec_or(t_lexem *node, t_shell *shell)
{
  t_bool	ret;

  if (!(node->left) || !(node->right))
    return (CONTINUE);
  if ((node->left)
      && ((ret = g_exec[node->left->type](node->left, shell)) != CONTINUE))
    return (ret);
  if ((node->right) && (shell->exit.status != EXIT_SUCCESS)
      && ((ret = g_exec[node->right->type](node->right, shell)) != CONTINUE))
    return (ret);
  return (CONTINUE);
}

t_bool		exec_and(t_lexem *node, t_shell *shell)
{
  t_bool	ret;

  if (!(node->left) || !(node->right))
    return (CONTINUE);
  if ((node->left)
      && ((ret = g_exec[node->left->type](node->left, shell)) != CONTINUE))
    return (ret);
  if ((node->right) && (shell->exit.status == EXIT_SUCCESS)
      && ((ret = g_exec[node->right->type](node->right, shell)) != CONTINUE))
    return (ret);
  return (CONTINUE);
}

t_bool	exec(t_shell *shell)
{
  if (!shell->lexem)
    return (CONTINUE);
  return (g_exec[shell->lexem->type](shell->lexem, shell));
}
