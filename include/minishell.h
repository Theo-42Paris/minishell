/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kjolly <kjolly@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/10 12:17:10 by tzara             #+#    #+#             */
/*   Updated: 2025/03/13 13:40:30 by kjolly           ###   ########.fr       */
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

typedef struct s_type_t
{
	int	delimiteur;
	int	commande;
	int	argument;
	int	pipe;
}	t_type_t;

typedef struct s_token
{
	t_type_t		type;
	char			*identifiant;
	struct s_token	*next;
}	t_token;

/********** utils **********/
void    exit_error(char *str);
/********** main **********/
/********** parsing **********/


#endif