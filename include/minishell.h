/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kjolly <kjolly@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/10 12:17:10 by tzara             #+#    #+#             */
/*   Updated: 2025/04/09 18:04:39 by kjolly           ###   ########.fr       */
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

enum	type_token
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
	t_cmd	*cmd;
	t_env	*env;
	int		signal;
	
}	t_data;

/********** utils **********/
// void    exit_error(char *str);
/********** main **********/
/********** parsing **********/
/*** pars_token ***/
void	tokenizer(t_token **token, char *str);
char	*pre_token(char *line);
/*** pars_syntax ***/
int		check_syntax(t_token **token);
int		is_delimiteur(int type);
/*** pars_env ***/
void	get_env(t_env **env, char **envp);
/*** pars_cmd ***/
void	get_cmd(t_token *token, t_cmd **cmd);
/*** expand ***/
char	*handle_expand(char	*src, t_env **env);
char	*expandables(char *src, t_env **env);
/*** here_doc ***/
void	handle_here_doc(t_cmd *cmd);
/********** print_utils **********/
void	print_token(t_token **token);
void	print_tab(char **tab);
void	print_cmd(t_cmd **cmd);
void	print_redir(t_redir **redir);
/********** free_utils **********/
void	free_token(t_token **token);
void	free_redir(t_redir **redir);
void	free_cmd(t_cmd **cmd);
/**********Builtins***********/
int		ft_echo(t_data *data, t_cmd *cmd);
int		ft_pwd(t_cmd *cmd);
int		ft_isbuiltin(t_cmd *cmd);
int		ft_is_option(char *str);
int		ft_exec_builtin(t_data *data, t_cmd *cmd);

#endif