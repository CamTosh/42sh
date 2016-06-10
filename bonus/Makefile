##
## Makefile for minishell2 in /home/rotaru_i/Coding/PSU/minishell_reborn
## 
## Made by Iulian Rotaru
## Login   <rotaru_i@epitech.net>
## 
## Started on  Mon Mar 14 22:16:05 2016 Iulian Rotaru
## Last update Sun Jun  5 21:14:10 2016 Alif Matthias
##

CC		= 	gcc

CPPFLAGS	+=	-I./inc				\
		   	-I/home/${USER}/.froot/include

LDLIB		+=	-llapin -lsfml-audio -lsfml-graphics	\
	   		-lsfml-window -lsfml-system -lstdc++	\
	   		-ldl -lm

LDFLAGS		+= 	-L/home/${USER}/.froot/lib     		\

CFLAGS		+=	-O2					\
	   		-Wall -Wextra -Werror

RM		= 	rm -f

NAME		= 	KalaTerm

SRCS		= 	./src/the_main.c 			\
			./src/my_blitstr.c 			\
			./src/my_bunny_blit.c 		\
			./src/my_blitstr_end.c		\
			./src/kala_key.c			\
			./src/color_mixer.c			\
			./src/the_misc.c			\
			./src/pty_setup.c			\
			./src/read_pars.c			\
			./src/process_it.c			\
			./src/the_loop.c			\
			./src/kala_style.c			\
			./src/the_blitst.c			\

OBJ		= 	$(SRCS:.c=.o)

PROJ		= 	-K-Term-

REDDARK		=	\033[31;2m

RED		= 	\033[31;1m

GREEN		= 	\033[32;1m

YEL		= 	\033[33;1m

BLUE		= 	\033[34;1m

PINK		= 	\033[35;1m

CYAN		= 	\033[36;1m

RES		= 	\033[0m

all: 		$(NAME)

$(NAME):	 $(OBJ)
	@$(CC) -o $(NAME) $(OBJ) $(CFLAGS) $(CPPFLAGS) $(LDFLAGS) $(LDLIB)
	@cp $(NAME) ..
	@printf "\n\t\t$(BLUE)•••••••••••••••••••••••••••••••••••••••••$(RES)\n"
	@printf "\t\t$(BLUE)••► $(GREEN)Compilation done for $(CYAN)$(NAME)$(GREEN) ! $(YEL)[$(GREEN)✓$(YEL)]$(BLUE) ◂••$(RES)\n"
	@printf "\t\t$(BLUE)•••••••••••••••••••••••••••••••••••••••••$(RED)\n"
	@if [ -e .signa ]; then cat .signa; fi
	@printf "$(RES)"
	@cp $(NAME) ..

clean:
	@$(foreach var, $(OBJ), if [ -e $(var) ] ; then \
	printf "$(RED) ✗ $(YEL)[$(BLUE)$(PROJ)$(YEL)] •• $(GREEN)$(dir $(var))$(notdir $(var))$(RES) $(YEL): \t[$(BLUE)RM$(YEL)]$(RES)\n" \
	&& $(RM) $(var) ; fi ;)

fclean: 	clean
	@if [ -e $(NAME) ] ; then \
	printf "$(RED) ✗ $(YEL)[$(BLUE)$(PROJ)$(YEL)] •• $(GREEN)$(notdir $(NAME))$(RES) $(YEL): \t\t[$(BLUE)RM$(YEL)]$(RES)\n" \
	&& $(RM) $(NAME) && $(RM) ../$(NAME); fi ;


re: 	fclean all

%.o: 		%.c
	@$(CC) -o $@ -c $< $(CFLAGS) $(CPPFLAGS) $(LDFLAGS) $(LDLIB) && \
	printf "$(YEL) ► [$(BLUE)$(PROJ)$(YEL)] •• $(RED)$(dir $<)$(GREEN)$(notdir $<)$(RES) $(YEL): \t[$(GREEN)✓✓$(YEL)]$(RES)\n" || printf "$(YEL) ► [$(BLUE)$(PROJ)$(YEL)] •• $(RED)$(dir $<)$(GREEN)$(notdir $<)$(RES) $(YEL): \t[$(RED)✗$(YEL)]$(RES)\n"

.PHONY: all clean fclean re
