NAME = minishell

CFLAGS = -std=gnu99 -Wall -Werror -Wextra -g3

SRC = srcs/main.c \
	srcs/print_utils.c \
	srcs/parsing/pars_token.c \
	srcs/parsing/pars_syntax.c \
	srcs/parsing/prep_env.c \
	srcs/parsing/pars_cmd.c \
	srcs/parsing/expand.c \
	srcs/parsing/here_doc.c \
	srcs/free.c \
	srcs/builtin/ft_echo.c \
	srcs/builtin/ft_pwd.c \
	srcs/builtin/builtins.c \

MINI = \
	"\n	 ███╗   ███╗██╗███╗   ██╗██╗███████╗██╗  ██╗███████╗██╗     ██╗       "\
	"\n	 ████╗ ████║██║████╗  ██║██║██╔════╝██║  ██║██╔════╝██║     ██║       "\
	"\n	 ██╔████╔██║██║██╔██╗ ██║██║███████╗███████║█████╗  ██║     ██║       "\
	"\n	 ██║╚██╔╝██║██║██║╚██╗██║██║╚════██║██╔══██║██╔══╝  ██║     ██║       "\
	"\n	 ██║ ╚═╝ ██║██║██║ ╚████║██║███████║██║  ██║███████╗███████╗███████╗  "\
	"\n	 ╚═╝     ╚═╝╚═╝╚═╝  ╚═══╝╚═╝╚══════╝╚═╝  ╚═╝╚══════╝╚══════╝╚══════╝  "\
                                                                       

HEAD = -I ./libft

LIBFT = ./libft/libft.a

OBJ = $(SRC:.c=.o)

all: ${NAME}
	@echo ${MINI}

${NAME}: ${OBJ} ${LIBFT}
	@cc ${CFLAGS} ${OBJ} -lreadline -lft -L./libft -o ${NAME}

%.o: %.c
	cc ${CFLAGS} -c $< ${HEAD} -o $@

${LIBFT}:
	@make --silent -C ./libft

clean:
	@rm -f ${OBJ}
	@make --silent -C ./libft clean

fclean: clean
	@rm -f ${NAME}
	@make --silent -C ./libft fclean

re: fclean all

.PHONY: all clean fclean re