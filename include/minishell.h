/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kjolly <kjolly@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/10 12:17:10 by tzara             #+#    #+#             */
/*   Updated: 2025/04/14 10:53:04 by kjolly           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "../libft/libft.h"
# include <readline/history.h>
# include <readline/readline.h>
// readline
// rl_clear_history
// rl_om_new_line
// rl_replace_line
// rl_redisplay
// add_history

# include <unistd.h>
// write
// read
// access
// close
// fork
// getcwd
// chdir
// unlink
// execve
// dup
// dup2
// pipe
// isatty
// ttyname
// ttyslot

# include <string.h>
// strerror

# include <stdio.h>
// printf
// perror

# include <fcntl.h>
// open

# include <stdlib.h>
// malloc
// free
// exit
// getenv

# include <sys/wait.h>
// wait
// waitpid
// wait3
// wait4

# include <sys/stat.h>
// stat
// lstat
// fstat

# include <sys/ioctl.h>
// ioctl

# include <signal.h>
// signal
// sigaction
// sigemptyset
// sigaddset
// kill

# include <dirent.h>
// opendir
// readdir
// closedir

# include <termios.h>
// tcsetattr
// tcgetattr

# include <termcap.h>
// tgetent
// tgetflag
// tgetnum
// tgetstr
// tgoto
// tputs

# define G "\033[1;32m"
# define RST "\033[0m"

// # define WORD 1
// # define PIPE 2 // |
// # define REDIR_IN 3 // <
// # define REDIR_OUT 4 // >
// # define DELIMITER 5 // << (here_doc)
// # define APPEND 6 // >> (ajoue a la suite)

enum				type_token
{
	WORD,
	PIPE,
	REDIR_IN,
	REDIR_OUT,
	DELIMITER,
	APPEND
};

typedef struct s_env
{
	char			*env;
	struct s_env	*next;
}					t_env;

typedef struct s_token
{
	char			*data;
	enum type_token	token;
	int				exp;
	struct s_token	*next;
}					t_token;

typedef struct s_redir
{
	char			*arg;
	enum type_token	token;
	int				fd_here_doc;
	struct s_redir	*next;
}					t_redir;

typedef struct s_cmd
{
	char			**args;
	char			*cmd;
	t_redir			*redir;
	char			*value;
	struct s_cmd	*next;
}					t_cmd;
// ? le here_doc doit etre gerer direct apres ('<<')

typedef struct s_data
{
	t_cmd			*cmd;
	t_env			*env;
	int				signal;

}					t_data;

/********** utils **********/
// void    exit_error(char *str);
/********** main **********/
/********** parsing **********/
/*** pars_token ***/
char				*append_char(char *word, char c);
void				first_if(char *c, int *in_quote, int *exp,
						char *quote_char);
void				win_2_line(t_token **token, char **current_word, int *exp,
						t_env **env);
void				init_var(int *in_q, char *quote_c, char **cur_wrd,
						int *exp);
void				tokenizer(t_token **tokens, char *cmd, t_env **env);
/*** pars_token_2 ***/
int					count_line(char *line);
void				pre_token2(char **line, int *i, char **dest, int *j);
char				*pre_token(char *line);
/*** pars_token_3 ***/
int					check_type(char *src);
t_token				*last_token(t_token *token);
void				add_token(t_token **token, t_token *tmp);
t_token				*new_token(char *src, int exp, t_env **env);
void				compl_token_list(t_token **token, char *src, int exp,
						t_env **env);
/*** pars_syntax ***/
int					is_delimiteur(int type);
int					slovaquie(t_token *current);
int					violence_urbaine_emeute(t_token *current, t_token *prev);
int					syntax_node(int start, int end, t_token *current,
						t_token *prev);
int					check_syntax(t_token **token);
/*** pars_env ***/
t_env				*new_env(char *envp);
t_env				*last_env(t_env *env);
void				add_env(t_env **env, t_env *new);
void				fill_env(char *envp, t_env **env);
void				get_env(t_env **env, char **envp);
/*** pars_cmd ***/
void				init_data_cmd(t_token *token, t_cmd **cmd,
						t_token **current);
int					check_tok(t_token *current);
void				get_cmd(t_token *token, t_cmd **cmd);
void				get_cmd_2(t_token *current, t_cmd **cmd);
/*** pars_cmd_2 ***/
int					get_args_nb(t_token *token);
t_cmd				*new_cmd(t_token *current);
t_cmd				*last_cmd(t_cmd *cmd);
void				add_cmd(t_cmd **cmd, t_cmd *head);
void				fill_cmd(t_cmd **cmd, t_token *current);
/*** pars_cmd_3 ***/
t_redir				*new_redir(t_token *current);
t_redir				*last_redir(t_redir *redir);
void				add_redir(t_redir **redir, t_redir *new);
void				fill_redir(t_redir **redir, t_token *current);
/*** expand ***/
char				*handle_expand(char *src, t_env **env);
char				*expandables(char *src, t_env **env);
/*** here_doc ***/
void				handle_here_doc(t_cmd *cmd, t_env **env);
/********** print_utils **********/
void				print_token(t_token **token);
void				print_tab(char **tab);
void				print_cmd(t_cmd **cmd);
void				print_redir(t_redir **redir);
/********** free_utils **********/
void				free_token(t_token **token);
void				free_redir(t_redir **redir);
void				free_cmd(t_cmd **cmd);
void				free_env(t_env **env);
/**********Builtins***********/
int					ft_echo(t_data *data, t_cmd *cmd);
int					ft_pwd(t_cmd *cmd);
int					ft_isbuiltin(t_cmd *cmd);
int					ft_is_option(char *str);
int					ft_exec_builtin(t_data *data, t_cmd *cmd);
void				handle_sig_c(int signals);

#endif