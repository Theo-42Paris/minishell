/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kjolly <kjolly@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/10 12:17:10 by tzara             #+#    #+#             */
/*   Updated: 2025/03/18 15:51:27 by kjolly           ###   ########.fr       */
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

# define WORD 1
# define PIPE 2 // |
# define REDIR_IN 3 // <
# define REDIR_OUT 4 // >
# define DELIMITER 5 // << (here_doc)
# define APPEND 6 // >> (ajoue a la suite)

typedef struct s_token
{
	char			*data;
	int				type;
	int				cmd;
	struct s_token	*next;
}	t_token;

typedef struct s_data
{
	char			*line;
	struct s_data	*next;
}	t_data;

typedef struct s_cmd
{
    char			**args;
    char 			*infile;
    char			*outfile;
    int				append; // 1 si '>>' 0 sinon
    struct s_cmd	*next;
} t_cmd;
// ? le here_doc doit etre gerer a part ('<<')

/********** utils **********/
void    exit_error(char *str);
/********** main **********/
/********** parsing **********/
void	tokenizer(t_token **token, char *str);
char	*ft_strndup(char *src, int a);
/********** parsing2 **********/
void    check_cmd_args(t_token **token);
void	token_to_cmd(t_token **token, t_cmd **cmd)
// void	check_syntax(t_token **token);

#endif