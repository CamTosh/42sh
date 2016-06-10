/*
** kala.h for KalaSH in /home/guillaume/Documents/rendu/42sh/PSU_2015_42sh
**
** Made by Guillaume Benard
** Login   <guillaume@epitech.net>
**
** Started on  Mon May 30 13:31:39 2016 Guillaume Benard
** Last update Fri Jun 10 17:40:39 2016 Iulian Rotaru
*/

#ifndef KALA_H_
# define KALA_H_

/*
**  +------------------------------------+
**  |               Macros               |
**  +------------------------------------+
*/
# define UNUSED(v) __attribute__((unused))(v)

# include "my_dprintf.h"

# define PINK "\033[45m"
# define RED "\x1b[31m"
# define RES "\x1b[0m"

# define SPACE_CHAR (' ')
# define TAB_CHAR ('\t')
# define HISTORY_FILE (".kalash_history")

# ifndef FALSE
typedef enum	e_bool
  {
    FALSE,
    TRUE,
    CONTINUE
  }		t_bool;
# else
typedef enum	e_bool
  {
    K_FALSE,
    K_TRUE,
    K_CONTINUE
  }		t_bool;
# endif /* !FALSE */

typedef enum	e_opt
  {
    NCURSE,
    NB_OPT
  }		t_opt;

extern t_bool g_sigint;

typedef enum	e_type
  {
    COL,
    OR,
    AND,
    LDIR,
    DLDIR,
    PIPE,
    PIPE_ERR,
    RDIR,
    RDIR_ERR,
    DRDIR,
    DRDIR_ERR,
    AMPERSAND,
    STRING
  }		t_type;

# define USAGE "Usage: ./42sh"

# define NULL_VALUE 0

/*
**  +------------------------------------+
**  |              Structures            |
**  +------------------------------------+
*/
# include <termios.h>
# include "job.h"

typedef struct		s_lexem
{
  unsigned char		priority;
  t_bool		background;
  t_bool		is_pipe;
  t_bool		is_from_pipe;
  t_type		type;
  int			fd[3];
  char			*str;
  char			**av;
  struct s_lexem	*right;
  struct s_lexem	*left;
}			t_lexem;

typedef struct	s_exit
{
  unsigned char	status;
  t_bool	should_exit;
}		t_exit;

typedef struct	s_key
{
  char		*tabu;
  char		*left;
  char		*right;
  char		*bottom;
  char		*top;
  char		*nocurs;
  char		*curs;
  char		*end;
  char		*home;
  char		*pos;
  char		*clr_line;
  char		*clr;
  char		*clear;
}		t_key;

typedef struct	s_cmd
{
  const char	*str;
  struct s_cmd	*next;
  struct s_cmd	*prev;
}		t_cmd;

typedef struct	s_com
{
  t_cmd		*cursor;
  t_cmd		*cmd_l;
  char		**paths;
  int		y[2];
  int		st;
  t_bool	on;
}		t_com;

typedef struct		s_alias
{
  t_bool		replaced;
  char			*alias;
  char			*input;
  struct s_alias	*next;
  struct s_alias	*prev;
}			t_alias;

typedef struct		s_history
{
  char			*cmd;
  struct s_history	*next;
  struct s_history	*prev;
}			t_history;

typedef struct		s_shell
{
  t_key			key;
  t_com			com;
  t_bool		opt[NB_OPT];
  t_bool		history_on;
  char			*bufist;
  t_exit		exit;
  char			**env;
  t_alias		*alias;
  t_lexem		*lexem;
  t_history		*hist;
  t_history		*last_hist;
  int			term_fd;
  int			term_pgrp;
  t_job			*jobs;
  struct termios	term;
  int			rando;
}			t_shell;

/*
**  +------------------------------------+
**  |               Parser               |
**  +------------------------------------+
*/
t_bool	lets_pars(t_shell *shell, const char *line);

/*
**  +------------------------------------+
**  |                 Exec               |
**  +------------------------------------+
*/
t_bool	exec(t_shell *shell);
t_bool	exec_semi(t_lexem *lexem, t_shell *shell);
t_bool	exec_or(t_lexem *lexem, t_shell *shell);
t_bool	exec_and(t_lexem *lexem, t_shell *shell);
int	wtab_word_count(char *str);
void	ret_thr(char *refchar, char *str, int *new_idx, int *len);
int	first_part(const char *, int, int *, char *);
void	ret_scd(char *out, char *, char *, int *);

extern t_bool	(*const g_exec[])(t_lexem *lexem, t_shell *shell);

/*
**  +------------------------------------+
**  |               Ncurse               |
**  +------------------------------------+
*/
# define PAR 1
# define FUNC 2

# include <sys/types.h>
# include <dirent.h>

void		mv_curs(t_shell *shell, int *i, char *buff);
void		aff_prompt(t_shell *shell);
void		may_act(t_shell *shell, char *buff, int *i, char *c);
void		print_buff(t_shell *, char *buff, int *curs_pos);
int		get_actual_pos(t_shell *shell);
t_bool		complete_part(t_shell *shell, char *buff, int *i, char *c);
void		process_keys(t_shell *shell, int *i, char *c, char *buff);
t_bool		my_getnbr(const char *str, int *nb);
void		aff_cmpl(t_shell *shell);
void		put_in_buff(char *buff, const char *str, int *i);
int		select_param(const char *str, int pos);
int		invlen(const char *str, int i);
char		*isol_wrd(const char *str, int i);
t_bool		complet_par(t_shell *shell, const char *str, int pos);
t_bool		read_it(t_com *com, DIR *dir, const char *str, int par);
t_bool		is_wrd(char c);
t_bool		creat_list(t_com *com, const char *str);
void		delete_list(t_com *com);
t_bool		completion(t_shell *shell, const char *str, int pos);
char		**cup_path(const char *path);
const char	*my_search_env(char *const tab_env[], const char *str);
t_bool		load_keys(t_shell *shell, char *const env[]);
void		aff_com(t_com *);
char		*gnl_ncurse(t_shell *shell);
void		gotoyx(t_shell *, int, int);

# include <term.h>

int	gogo_ncurse(struct termios *);

# define BUFF_SIZE (4096)
# define RD_SIZE (10)

typedef struct	s_ncu
{
  const char	*key;
  int		(*fct)(t_shell *, char *, int *);
}		t_ncu;

int		tabu(t_shell *, char *, int *);
int		left(t_shell *, char *, int *);
int		right(t_shell *, char *, int *);
int		down(t_shell *, char *, int *);
int		up(t_shell *, char *, int *);
int		del(t_shell *, char *, int *);
int		backspace(t_shell *, char *, int *);
int		end(t_shell *, char *, int *);
int		home(t_shell *, char *, int *);
t_bool		job_pipe(t_lexem *lex, t_shell *shell, t_job *job);
t_bool		job_rdir(t_lexem *lex, t_shell *shell, t_job *job);
t_bool		job_drdir(t_lexem *lex, t_shell *shell, t_job *job);
t_bool		job_dldir(t_lexem *lexem, t_shell *shell, t_job *job);
t_bool		job_ldir(t_lexem *lex, t_shell *shell, t_job *job);

/*
**  +------------------------------------+
**  |               History              |
**  +------------------------------------+
*/

t_history	*create_history();
void		free_history(t_history **);
t_bool		add_in_hist(t_history **, char *);
t_bool		write_history(t_history *);
char		*get_history(t_history *, t_bool, t_shell *);
/*
**  +------------------------------------+
**  |              Built-in              |
**  +------------------------------------+
*/

# define NB_BUILTIN (sizeof(g_builtin) / sizeof(g_builtin[0]))

# define ENV_USAGE "env\n"
# define EXIT_USAGE "exit: Expression Syntax.\n"
# define CD_USAGE "cd: Too many arguments.\n"
# define UNALIAS_HANDLE "unalias: Too few arguments.\n"
# define SETENV_USAGE "setenv: Too many arguments.\n"
# define UNSETENV_USAGE "unsetenv: Too few arguments.\n"

int	locate_env_var(const char *field, char **env);

t_bool	my_env(t_lexem *node, t_shell *sh);
t_bool	my_setenv(t_lexem *node, t_shell *sh);
t_bool	my_unsetenv(t_lexem *node, t_shell *sh);
t_bool	my_cd(t_lexem *node, t_shell *sh);
t_bool	my_exit(t_lexem *node, t_shell *sh);
t_bool	my_echo(t_lexem *lex, t_shell *sh);
t_bool	alias_handle(t_lexem *lex, t_shell *shell);
t_bool	unalias_handle(t_lexem *lex, t_shell *shell);

/*
**  +------------------------------------+
**  |               Alias                |
**  +------------------------------------+
*/
t_bool	make_alias(t_lexem **lex, t_alias *alias, t_alias *last);
void	unalias(t_alias **alias, const char *in);
int	replace_alias(t_lexem **lex,
		      t_alias *alias, t_alias **replaced, t_alias *last);
void	show_alias(t_alias *alias);
int	add_alias(t_alias **list, char *alias, char *input);
void	free_alias(t_alias *list);

#endif /* !KALA_H_ */
