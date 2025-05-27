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
AZUR    = \033[38;5;45m

SRC = srcs/main.c \
       srcs/main_utils.c \
       srcs/utils/print_utils.c \
       srcs/utils/utils.c \
       srcs/utils/free.c \
       srcs/parsing/pars_token.c \
       srcs/parsing/pars_token_2.c \
       srcs/parsing/pars_token_3.c \
       srcs/parsing/pars_token_4.c \
       srcs/parsing/pars_syntax.c \
       srcs/parsing/prep_env.c \
       srcs/parsing/pars_cmd.c \
       srcs/parsing/pars_cmd_2.c \
       srcs/parsing/pars_cmd_3.c \
       srcs/signal/signal.c \
       srcs/parsing/expand.c \
       srcs/parsing/here_doc.c \
       srcs/execution/redir_exec.c \
       srcs/execution/ft_execve.c \
       srcs/execution/ft_execve_utils.c \
       srcs/execution/execution.c \
       srcs/execution/alone_cmd.c \
       srcs/execution/rest_cmd_exec.c \
       srcs/execution/last_cmd_exec.c \
       srcs/execution/last_cmd_exec_utils.c \
       srcs/execution/infile_utils.c \
       srcs/execution/outfile_utils.c \
       srcs/builtin/builtins.c \
       srcs/builtin/ft_exit.c \
       srcs/builtin/ft_export.c \
       srcs/builtin/ft_export_utils.c \
       srcs/builtin/ft_export_utils_2.c \
       srcs/builtin/ft_unset.c \
       srcs/builtin/ft_atoll.c \
       srcs/builtin/ft_cd.c \
       srcs/builtin/ft_echo.c \
       srcs/builtin/ft_pwd.c \
       srcs/builtin/ft_builtins_utils.c \
       srcs/parsing/here_doc_utils.c \
       srcs/parsing/pars_token_utils.c \

OBJ_DIR = obj
OBJ = $(SRC:srcs/%.c=$(OBJ_DIR)/%.o)

MINI = \
"\n	 $(AZUR)███╗   ███╗██╗███╗   ██╗██╗███████╗██╗  ██╗███████╗██╗     ██╗       "\
"\n	 $(AZUR)████╗ ████║██║████╗  ██║██║██╔════╝██║  ██║██╔════╝██║     ██║       "\
"\n	 $(AZUR)██╔████╔██║██║██╔██╗ ██║██║███████╗███████║█████╗  ██║     ██║       "\
"\n	 $(AZUR)██║╚██╔╝██║██║██║╚██╗██║██║╚════██║██╔══██║██╔══╝  ██║     ██║       "\
"\n	 $(AZUR)██║ ╚═╝ ██║██║██║ ╚████║██║███████║██║  ██║███████╗███████╗███████╗  "\
"\n	 $(AZUR)╚═╝     ╚═╝╚═╝╚═╝  ╚═══╝╚═╝╚══════╝╚═╝  ╚═╝╚══════╝╚══════╝╚══════╝  "


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
