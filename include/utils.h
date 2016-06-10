/*
** utils.h for KalaSH in /home/guillaume/Documents/rendu/42sh/PSU_2015_42sh
**
** Made by Guillaume Benard
** Login   <guillaume@epitech.net>
**
** Started on  Wed Jun  1 15:48:46 2016 Guillaume Benard
** Last update Sun Jun  5 04:00:17 2016 pierre said
*/

#ifndef UTILS_H_
# define UTILS_H_

# ifndef NULL_VALUE
#  define NULL_VALUE 0
# endif /* !NULL_VALUE */

# ifndef MY_NULL
#  define MY_NULL ((void *)0)
# endif /* !MY_NULL */

# define MATCH 0

/*
**  +------------------------------------+
**  |             Get Next Line          |
**  +------------------------------------+
*/
# define READ_SIZE 256

# define END_CHAR '\0'

char	*get_next_line(const int fd);

/*
**  +------------------------------------+
**  |           Print Management         |
**  +------------------------------------+
*/
int	my_perror(const char *str, int ret);

/*
**  +------------------------------------+
**  |              Get Nbr               |
**  +------------------------------------+
*/
# define SIGN_CHAR '-'
# define IS_DIGIT(d) (((d) >= '0' && (d) <= '9') ? (TRUE) : (FALSE))
# define CAN_GO_UP(n, d) ((2147483647 - (d) + '0') / 10 >= (n))
# define CAN_GO_DOWN(n, d) ((-2147483648 + (d) - '0') / 10 <= (n))

t_bool	my_getnbr(const char *str, int *nbr);

/*
**  +------------------------------------+
**  |               Wordtab              |
**  +------------------------------------+
*/
char	**free_wordtab(char *wordtab[]);
int	wordtab_len(char *const wordtab[]);
char	**dup_wordtab(char *const wordtab[]);
void	show_wordtab(char *const wordtab[]);
int	my_count_wordtab(char **wordtab);
char	*concat_av(char **av);

/*
**  +------------------------------------+
**  |                 Env                |
**  +------------------------------------+
*/
# define VALUE_CHAR '='
# define SEPARATOR_ENV_CHAR ':'

# define DEFAULT_PATH "/bin:/usr/bin"
# define PATH_FIELD "PATH"

char	*my_getenv(const char *field, char *const env[]);
char	**env_field_to_wordtab(const char *field, char *const env[]);

/*
**  +------------------------------------+
**  |                 String             |
**  +------------------------------------+
*/

char	*insert(char *s, int i, const char *ins);
int	cut(char *s, int i, int size);

#endif /* !UTILS_H_ */
