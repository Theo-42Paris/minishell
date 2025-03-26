NAME = minishell

CFLAGS = -Wall -Werror -Wextra -g

SRC = 	srcs/main.c \
		srcs/print_utils.c \
		srcs/parsing/parsing.c \
		srcs/parsing/parsing2.c \
		srcs/parsing/pars_test.c \
		srcs/free.c \

HEAD = -I ./libft

LIBFT = ./libft/libft.a

OBJ = $(SRC:.c=.o)

all : ${NAME}

${NAME} : ${OBJ} ${LIBFT}
	@cc ${CFLAGS} ${OBJ} -lreadline -lft -L./libft -o ${NAME}

%.o: %.c
	cc ${CFLAGS} -c $< ${HEAD} -o $@

${LIBFT} :
	@make --silent -C ./libft

clean :
	@rm -f ${OBJ}
	@make --silent -C ./libft clean

fclean : clean
	@rm -f ${NAME}
	@make --silent -C ./libft fclean

re : fclean all

.PHONY : all clean fclean re