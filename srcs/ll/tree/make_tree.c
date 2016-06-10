/*
** make_tree.c for KalaSH in /home/rotaru_i/Coding/42sh/srcs/ll
**
** Made by ROTARU Iulian
** Login   <rotaru_i@epitech.net>
**
** Started on  Sat Jun  4 06:21:00 2016 ROTARU Iulian
** Last update Sun Jun  5 20:28:42 2016 ROTARU Iulian
*/

#include <stdlib.h>
#include "kala.h"
#include "ll.h"

void	*liberate_tree(t_lexem *tree)
{
  if (!tree)
    return (NULL);
  tree->left = liberate_tree(tree->left);
  tree->right = liberate_tree(tree->right);
  free(tree->str);
  free(tree);
  return (NULL);
}

static t_lexem	*plant_tree(t_lexem *tree, t_lexem **list)
{
  t_lexem	*elem;

  elem = *list;
  *list = (*list)->right;
  if (*list)
    (*list)->left = NULL;
  elem->left = tree;
  elem->right = NULL;
  while ((*list) && (*list)->priority > elem->priority)
    elem->right = plant_tree(elem->right, list);
  return (elem);
}

t_lexem		*build_tree(t_lexem *list)
{
  t_lexem	*tree;

  tree = NULL;
  while (list)
    tree = plant_tree(tree, &list);
  return (tree);
}
