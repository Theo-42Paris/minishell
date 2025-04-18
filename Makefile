NAME    = minishell

CC      = cc
CFLAGS  = -std=gnu99 -Wall -Werror -Wextra -g3
HEAD    = -I ./libft
LIBFT   = ./libft/libft.a

YELLOW  = \033[1;33m
GREEN   = \033[1;32m
BLUE    = \033[1;34m
RED     = \033[1;31m
RESET   = \033[0m

SRC = srcs/main.c \
       srcs/print_utils.c \
       srcs/utils.c \
       srcs/parsing/pars_token.c \
       srcs/parsing/pars_token_2.c \
       srcs/parsing/pars_token_3.c \
       srcs/parsing/pars_syntax.c \
       srcs/parsing/prep_env.c \
       srcs/parsing/pars_cmd.c \
       srcs/parsing/pars_cmd_2.c \
       srcs/parsing/pars_cmd_3.c \
       srcs/parsing/expand.c \
       srcs/parsing/expand_2.c \
       srcs/parsing/here_doc.c \
       srcs/free.c \
       srcs/builtin/ft_echo.c \
       srcs/builtin/ft_pwd.c \
       srcs/builtin/builtins.c \
       srcs/signal/signal.c

OBJ_DIR = obj
OBJ = $(SRC:srcs/%.c=$(OBJ_DIR)/%.o)

MINI = \
"\n	 $(RED)███╗   ███╗██╗███╗   ██╗██╗███████╗██╗  ██╗███████╗██╗     ██╗       "\
"\n	 $(RED)████╗ ████║██║████╗  ██║██║██╔════╝██║  ██║██╔════╝██║     ██║       "\
"\n	 $(RED)██╔████╔██║██║██╔██╗ ██║██║███████╗███████║█████╗  ██║     ██║       "\
"\n	 $(RED)██║╚██╔╝██║██║██║╚██╗██║██║╚════██║██╔══██║██╔══╝  ██║     ██║       "\
"\n	 $(RED)██║ ╚═╝ ██║██║██║ ╚████║██║███████║██║  ██║███████╗███████╗███████╗  "\
"\n	 $(RED)╚═╝     ╚═╝╚═╝╚═╝  ╚═══╝╚═╝╚══════╝╚═╝  ╚═╝╚══════╝╚══════╝╚══════╝  "


all: $(NAME)
	@echo "$(GREEN)✅ Build complete!$(RESET)"
	@echo $(MINI)

$(NAME): $(OBJ) $(LIBFT)
	@$(CC) $(CFLAGS) $(OBJ) -L./libft -lreadline -lft -o $(NAME)

$(OBJ_DIR)/%.o: srcs/%.c
	@mkdir -p $(dir $@)
	@echo "$(BLUE)📦 Compiling $<$(RESET)"
	@$(CC) $(CFLAGS) -c $< $(HEAD) -o $@

$(LIBFT):
	@echo "$(YELLOW)📚 Building libft...$(RESET)"
	@make -C ./libft --silent

clean:
	@echo "$(RED)🧹 Cleaning object files...$(RESET)"
	@rm -rf $(OBJ_DIR)
	@make -C ./libft clean --silent

fclean: clean
	@echo "$(RED)🗑️ Removing executable...$(RESET)"
	@rm -f $(NAME)
	@make -C ./libft fclean --silent

re: fclean all

.PHONY: all clean fclean re
