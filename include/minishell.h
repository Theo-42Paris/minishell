/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kjolly <kjolly@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/10 12:17:10 by tzara             #+#    #+#             */
/*   Updated: 2025/04/21 12:38:37 by kjolly           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "../libft/libft.h"
# include "parsing.h"
# include "exec.h"
# include <readline/history.h>
# include <readline/readline.h>
# include <unistd.h>
# include <string.h>
# include <stdio.h>
# include <fcntl.h>
# include <stdlib.h>
# include <sys/wait.h>
# include <sys/stat.h>
# include <sys/ioctl.h>
# include <signal.h>
# include <dirent.h>
# include <termios.h>
# include <termcap.h>

# define G "\033[1;32m"
# define RST "\033[0m"

typedef enum	e_type_token
{
	WORD,
	PIPE,
	REDIR_IN,
	REDIR_OUT,
	DELIMITER,
	APPEND
} t_type_token;

typedef	struct s_pigeon
{
	void			*ptr;
	int				size;
	struct s_pigeon	*next;
}					t_pigeon;

typedef struct s_env
{
	char			*env;
	struct s_env	*next;
}					t_env;

typedef struct s_token
{
	char			*data;
	t_type_token	token;
	int				exp;
	struct s_token	*next;
}					t_token;

typedef struct s_redir
{
	char			*arg;
	t_type_token	token;
	int				fd_here_doc;
	int				exp_hd;
	struct s_redir	*next;
}					t_redir;

typedef struct s_cmd
{
	char			**args;
	char			*cmd;
	char			*value;
	t_redir			*redir;
	struct s_cmd	*next;
}					t_cmd;
// ? le here_doc doit etre gerer direct apres ('<<')

typedef struct s_data
{
	t_token	*token;
	t_cmd	*cmd;
	t_env	*env;
	int		signal;
}			t_data;

/********** utils **********/
int					is_delimiteur(int type);

/********** print_utils **********/
void				print_token(t_token **token);
void				print_tab(char **tab);
void				print_cmd(t_cmd **cmd);
void				print_redir(t_redir **redir);
void				print_env(t_env **env);

/********** free_utils **********/
void				free_token(t_token **token);
void				free_redir(t_redir **redir);
void				free_cmd(t_cmd **cmd);
void				free_env(t_env **env);
void				free_all(t_data *data, char *line, char *good_line);

#endif