##
## Makefile for 42sh in /home/guillaume/Documents/rendu/42sh/PSU_2015_42sh
##
## Made by Guillaume Benard
## Login   <guillaume@epitech.net>
##
## Started on  Mon May 30 13:24:42 2016 Guillaume Benard
## Last update Sun Jun  5 21:57:53 2016 pierre said

NAME		=	42sh

CC		=	gcc

CFLAGS		+=	-W -Wall -Wextra -Werror
CPPFLAGS	+=	-Iinclude

LDFLAGS		+=	-Llib

LDLIB		+=	-lncurses -ldprintf

SRCS		=	srcs/main.c					\
			srcs/exec/builtin/unsetenv.c			\
			srcs/exec/builtin/echo.c			\
			srcs/exec/builtin/setenv.c			\
			srcs/exec/builtin/cd.c				\
			srcs/exec/builtin/alias_handle.c		\
			srcs/ll/lexer.c					\
			srcs/ll/check.c					\
			srcs/ll/check_second.c				\
			srcs/ll/parsing.c				\
			srcs/ll/rep_glob.c				\
			srcs/ll/replace_env.c				\
			srcs/ll/cut_lexer/cut_cmd.c			\
			srcs/ll/cut_lexer/cut_lexer.c			\
			srcs/ll/cut_lexer/cut_delim.c			\
			srcs/ll/tree/make_tree.c			\
			srcs/ll/exec/dir.c				\
			srcs/ll/exec/exec.c				\
			srcs/ll/exec/exec_cmd.c				\
			srcs/ll/exec/exec_end.c				\
			srcs/ll/exec/access_copy.c			\
			srcs/ll/exec/pipe.c				\
			srcs/ll/alias/alias.c				\
			srcs/ll/alias/replace_alias.c			\
			srcs/ll/alias/alias_util.c			\
			srcs/ll/alias/unalias.c				\
			srcs/exec/wtab.c				\
			srcs/exec/wtab_utils.c				\
			srcs/history/get_history.c			\
			srcs/history/read_history.c			\
			srcs/history/write_history.c			\
			srcs/ncurse/ncurse_3.c				\
			srcs/ncurse/ncurse_2.c				\
			srcs/ncurse/ncurse.c				\
			srcs/ncurse/zsh.c				\
			srcs/ncurse/load_keys.c				\
			srcs/ncurse/diff_param.c			\
			srcs/ncurse/create_path_tab.c			\
			srcs/ncurse/put_in_buff.c			\
			srcs/ncurse/complete_param.c			\
			srcs/ncurse/complete_cmd.c			\
			srcs/ncurse/manage_list.c			\
			srcs/ncurse/fcts.c				\
			srcs/utils/gnl.c				\
			srcs/utils/my_dup_wordtab.c			\
			srcs/utils/wordtab.c				\
			srcs/utils/my_getenv.c				\
			srcs/utils/my_getnbr.c				\
			srcs/utils/my_perror.c				\
			srcs/utils/cut_insert.c				\
			srcs/utils/concat_av.c				\
			srcs/utils/env_field_to_wortdtab.c		\

OBJS		=	$(SRCS:.c=.o)

all:		print $(NAME)

print:
		@make -C lib/libdprintf/ --no-print-directory

$(NAME):	$(OBJS)
		$(CC) -o $(NAME) $(OBJS) $(LDFLAGS) $(LDLIB)
		@if [ -e .signa ] ; then cat .signa ; fi

debug:		CFLAGS += -g -g3
debug:		all

redebug:	fclean debug

clean:
		@make clean -C lib/libdprintf/ --no-print-directory
		$(RM) $(OBJS)

fclean:		clean
		@make fclean -C lib/libdprintf/ --no-print-directory
		$(RM) $(NAME)

re:		fclean all

.PHONY:		all clean fclean re debug redebug bonus
