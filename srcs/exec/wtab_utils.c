/*
** wtab_utils.c for 42sh in /home/alif_m/tek1/PSU/PSU_2015_42sh/srcs/exec
**
** Made by ALIF Matthias
** Login   <alif_m@epitech.net>
**
** Started on  Sun Jun 05 18:21:52 2016 ALIF Matthias
** Last update Sun Jun  5 20:13:33 2016 ROTARU Iulian
*/

#include "kala.h"

int	wtab_word_count(char *str)
{
  int	i;
  int	out;
  char	refchar;

  i = -1;
  out = 0;
  refchar = 0;
  while (*(str + ++i))
    {
      if (first_part(str, i, &out, &refchar) == 1)
	continue;
      if (*(str + i) && !refchar && *(str + i) == '\\'
	  && (i - 1) > 0 && *(str + i - 1) != '\\')
	continue;
    }
  return (out);
}

void	ret_scd(char *out, char *refchar, char *str, int *i)
{
  int	len;

  len = -1;
  while (*(str + ++*i))
    {
      if (!*refchar && (*(str + *i) == '\"' || *(str + *i) == '\''))
	{
	  *refchar = *(str + *i);
	  continue;
	}
      else if (*refchar && *(str + *i) == *refchar)
	{
	  *refchar = 0;
	  continue;
	}
      if ((!*refchar && (*(str + *i) == SPACE_CHAR || *(str + *i) == TAB_CHAR)
	   && *i && *(str + *i - 1) != '\\') || !*(str + *i))
	break ;
      if (str[*i] && !*refchar && str[*i] == '\\')
	++*i;
      if (!*refchar || (*refchar && str[*i] && *(str + *i) != *refchar))
	*(out + ++len) = *(str + *i);
    }
  *(out + len + 1) = 0;
}

void	ret_thr(char *refchar, char *str, int *new_idx, int *len)
{
  while (*(str + ++*new_idx))
    {
      if (!*refchar && (*(str + *new_idx) == '\"'
			|| *(str + *new_idx) == '\''))
	{
	  *refchar = *(str + *new_idx);
	  continue;
	}
      else if (*refchar && *(str + *new_idx) == *refchar)
	{
	  *refchar = 0;
	  continue;
	}
      if ((!*refchar && (*(str + *new_idx) == SPACE_CHAR
			 || *(str + *new_idx) == TAB_CHAR) && *new_idx
	   && *(str + *new_idx - 1) != '\\') || !*(str + *new_idx))
	break ;
      if (str[*new_idx] && !*refchar && str[*new_idx] == '\\')
	++*new_idx;
      if (!*refchar || (*refchar && *(str + *new_idx) != *refchar))
	++*len;
    }
}

int	first_part(const char *str, int i, int *out, char *refchar)
{
  if (!*refchar && (*(str + i) == '\"' || *(str + i) == '\''))
    {
      *refchar = *(str + i);
      if ((i == 0) || (i && (*(str + i - 1) == TAB_CHAR
			     || *(str + i - 1) == SPACE_CHAR)
		       && (!(i - 1) || *(str + i - 2) != '\\')))
	++*out;
      return (1);
    }
  else if (*refchar && *(str + i) == *refchar)
    {
      *refchar = 0;
      return (1);
    }
  if (*(str + i) && (!*refchar && (!i && *(str + i) != SPACE_CHAR
				   && *(str + i) != TAB_CHAR)))
    ++*out;
  if (*(str + i) && (!*refchar && i && (*(str + i) != SPACE_CHAR
					&& *(str + i) != TAB_CHAR)
		     && ((*(str + i - 1) == SPACE_CHAR || *(str + i - 1)
			  == TAB_CHAR) && (i - 1) > 0
			 && *(str + i - 2) != '\\')))
    ++*out;
  return (0);
}
