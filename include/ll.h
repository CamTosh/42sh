/*
** ll.h for KalaSH in /home/guillaume/Documents/rendu/42sh/PSU_2015_42sh
**
** Made by Guillaume Benard
** Login   <guillaume@epitech.net>
**
** Started on  Mon May 30 14:02:28 2016 Guillaume Benard
** Last update Sun Jun  5 19:55:54 2016 ROTARU Iulian
*/

#ifndef LL_H_
# define LL_H_

# define COM_CHAR '#'

# define AND_LEN 2
# define OR_LEN 2
# define SEMI_LEN 1
# define PIPE_LEN 1
# define AMP_LEN 1
# define LDIR_LEN 1
# define RDIR_LEN 1
# define DLDIR_LEN 2
# define DRDIR_LEN 2

typedef struct	s_lexer_tab
{
  unsigned char	priority;
  unsigned char	len;
  t_type	type;
  const char	*flag;
  char		*(*fct)(t_lexem **lex, char *str,
			const struct s_lexer_tab *info);
}		t_lexer_tab;

typedef struct	s_built_tab
{
  const char	*str;
  t_bool	(*fct)(t_lexem *node, t_shell *shell);
}		t_built_tab;

# define G_TAB_SIZE (sizeof(g_tab) / sizeof(g_tab[0]))
# define G_DIR_SIZE (int)(sizeof(g_dir) / sizeof(g_dir[0]))
# define BUILT_SIZE (sizeof(g_built) / sizeof(g_built[0]))

/*
**  +------------------------------------+
**  |             Manage Name            |
**  +------------------------------------+
*/
char	*replace_var_env(const char *in, char **env);
void	replace_quote(char *str);

/*
**  +------------------------------------+
**  |            Lexer Management        |
**  +------------------------------------+
*/
# define NEW 1
# define B_SLASH '\\'

t_lexem	*new_lexem(void);
void	*free_lexem_list(t_lexem *list);
void	add_in_lexer_list(t_lexem **list, t_lexem *lex);
char	*rep_glob(char *str, t_bool *ret);

/*
**  +------------------------------------+
**  |             Lexeriser !            |
**  +------------------------------------+
*/
# define IS_SPACE(c) (((c) == ' ' || (c) == '\t') ? (TRUE) : (FALSE))

# define IS_QUOTE(c) (((c) == '"' || (c) == '\'') ? (TRUE) : (FALSE))

# define IS_DIR(c) (((c) == '<' || (c) == '>') ? (TRUE) : (FALSE))

# define DELIM_2(c) (((c) == ';') ? (TRUE) : (IS_DIR(c)))
# define IS_DELIM(c) (((c) == '&' || (c) == '|') ? (TRUE) : (DELIM_2(c)))

# define GOOD_DIR_TAB 6

t_bool	cut_lexer(t_lexem **lex, const char *str);
char	*cut_that(t_lexem **lex, char *str,
		  const t_lexer_tab *info);
char	*cut_dir(t_lexem **lex, char *str,
		 const t_lexer_tab *info);
char	*cut_cmd(t_lexem **lex, char *str,
		 const t_lexer_tab *info);
int	pass_quote(const char *str);
int	return_error(const char *msg, const char c);

t_bool	check_list(t_shell *shell);
t_bool	set_rdir_at_the_end(t_shell *shell);

# define IS_LDIR(t) (((t) == LDIR || (t) == DLDIR) ? (TRUE) : (FALSE))
# define IS_RDIR(t) ((t) == RDIR || (t) == DRDIR)

# define AMP_2(t) (((t) == OR || (t) == AND) ? (TRUE) : (IS_LDIR(t)))
# define IS_AMP_ERR(t) (((t) == COL || (t) == AMPERSAND) ? (TRUE) : (AMP_2(t)))

# define IS_DEL(t) (((t) >= COL && (t) <= AND) || (t) == OR)

# define AMP_REP(t) ((t) == PIPE || (t) == RDIR || (t) == DRDIR)

t_bool	check_empty_cmd(t_lexem *lexem);

# define SEPA(t) (t <= AND || t == PIPE || t == PIPE_ERR || t == AMPERSAND)
# define IS_EASY(t) (t == COL || t == AMPERSAND)

/*
**  +------------------------------------+
**  |                 Exec               |
**  +------------------------------------+
*/
t_lexem	*build_tree(t_lexem *lexem);
void	*liberate_tree(t_lexem *tree);

t_bool	exec_semi(t_lexem *node, t_shell *shell);
t_bool	exec_or(t_lexem *node, t_shell *shell);
t_bool	exec_and(t_lexem *node, t_shell *shell);
t_bool	exec_ldir(t_lexem *node, t_shell *shell);
t_bool	exec_dldir(t_lexem *node, t_shell *shell);
t_bool	exec_rdir(t_lexem *node, t_shell *shell);
t_bool	exec_drdir(t_lexem *node, t_shell *shell);
t_bool	exec_pipe(t_lexem *node, t_shell *shell);
t_bool	exec_cmd(t_lexem *node, t_shell *shell);

char	**wtab(const char *str);

/*
**  +------------------------------------+
**  |                 Misc               |
**  +------------------------------------+
*/
t_bool	access_copy(const char *buffer, t_lexem *node);
t_bool	slashed(const char *str);
t_bool	slashed_ret(t_lexem *node, char **path, t_shell *shell);
t_bool	too_long(char *buffer, char **path, t_lexem *node, int i);
t_bool	check_command(t_lexem *node, t_shell *shell);
t_bool	reset_dup(t_lexem *node, int *save);
t_bool	launch_dup(t_lexem *node, int *save);
t_bool	my_select(t_lexem *node, t_shell *shell);
t_bool	exec_it(t_lexem *node, t_shell *shell);
void	check_status_cases(int status, pid_t ret,
			   t_shell *shell, t_lexem *node);

/*
**  +------------------------------------+
**  |            Error Messages          |
**  +------------------------------------+
*/
# define UNMATCH_QUOTE "Unmatched"
# define MISS_NAME_DIR "Missing name for redirect"
# define MISS_SLASH "Empty '\\'"

# define PERMISSION_DENIED "Permission denied."
# define NO_SUCH "No such file or directory."

#endif /* !LL_H_ */
