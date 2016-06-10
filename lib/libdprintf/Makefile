##
## Makefile for my_dprintf in /home/guillaume/Documents/Libraries/my_dprintf
##
## Made by Benard Guillaume
## Login   <guillaume@epitech.net>
##
## Started on  Wed Mar 16 20:46:02 2016 Benard Guillaume
## Last update Wed May  4 12:17:16 2016 Guillaume Benard
##

NAME	=	../libdprintf.a

CC	=	gcc

CFLAGS	+=	-W -Wall -Wextra -Werror
CFLAGS	+=	-I../../include

RM	=	rm -f

SRCS	=	my_dprintf.c						\
		printf_str.c						\
		printf_put_nbr.c					\
		printf_putnbr_base.c					\
		printf_ptr.c						\

OBJS	=	$(SRCS:.c=.o)

RED	=	\033[31;1m
GREEN	=	\033[32;1m
YEL	=	\033[33;1m
BLUE	=	\033[34;1m
CYAN	=	\033[36;1m
RST	=	\033[0m

all:		$(NAME)

$(NAME):	$(OBJS)
		@ar rc $(NAME) $(OBJS)
		@ranlib $(NAME)
		@printf "$(GREEN)[LIBDPRINTF] $(BLUE)$(notdir $(NAME))$(RST)\n"

clean:
		@$(foreach var, $(OBJS), if [ -e $(var) ] ; then 	\
		printf "$(CYAN)[DEL] $(YEL)$(notdir $(var))$(RST)\n"	\
		&& $(RM) $(var) ; fi ; )				\

fclean:		clean
		@if [ -e $(NAME) ] ; then				\
		printf "$(CYAN)[DEL] $(RED)$(notdir $(NAME))$(RST)\n"	\
		&& $(RM) $(NAME) ; fi ;					\

re:		fclean all

%.o:		%.c
		@$(CC) -o $@ -c $< $(CFLAGS)
		@printf "$(GREEN)[LIBDPRINTF] $(CYAN)$(notdir $<)$(RST)\n"

.PHONY:		all clean fclean re
