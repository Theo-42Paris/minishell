/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kjolly <kjolly@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/10 12:17:10 by tzara             #+#    #+#             */
/*   Updated: 2025/05/14 17:08:57 by kjolly           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "../libft/libft.h"
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
	t_redir			*redir;
	struct s_cmd	*next;
}					t_cmd;

typedef struct s_exec
{
	int				cmd_count;
	int				fd_transfer;
	pid_t			*pidarray;
}					t_exec;

typedef struct s_data
{
	t_token	*token;
	t_cmd	*cmd;
	t_env	*env;
	int		signal;
	int		exit_code;
}			t_data;

extern t_data *ctrl_c_signal;

/*** PARSING ***/
char				*append_char(char *word, char c);
// void				first_if_token(char *c, int *in_quote, int *exp, char *quote_char);
// void				win_2_line(t_token **token, char **current_word, int *exp);
// void				init_var(int *in_q, char *quote_c, char **cur_wrd, int *exp);
void				tokenizer(t_data *data, char *line);
// pars_token_2
int					count_line(char *line);
void				pre_token2(char **line, int *i, char **dest, int *j);
char				*pre_token(char *line);
void				ft_strcpy(char *dst, char *src);
// pars_token_3
int					check_type(char *src);
t_token				*last_token(t_token *token);
void				add_token(t_token **token, t_token *tmp);
t_token				*new_token(char *src);
void				compl_token_list(t_token **token, char *src);
// pars_syntax
int					slovaquie(t_token *current);
int					violence_urbaine_emeute(t_token *current, t_token *prev);
int					syntax_node(int start, int end, t_token *current, t_token *prev);
int					check_syntax(t_token **token);
// pars_env
t_env				*last_env(t_env *env);
void				fill_env(char *envp, t_env **env);
void				get_env(t_env **env, char **envp);
// pars_cmd
void				first_if_cmd(t_token **current, t_token **prev, t_cmd **cmd);
void				get_cmd(t_token *token, t_cmd **cmd, t_env **env, t_data *data);
void				get_cmd_2(t_token *current, t_cmd **cmd, t_env **env, t_data *data);
// pars_cmd_2
int					get_args_nb(t_token *token);
t_cmd				*last_cmd(t_cmd *cmd);
void				add_cmd(t_cmd **cmd, t_cmd *head);
void				fill_cmd(t_cmd **cmd, t_token *current);
// pars_cmd_3
t_redir				*last_redir(t_redir *redir);
void				fill_redir(t_redir **redir, t_token *current);
// expand
char				*expandables(char *src, t_env **env, t_data *data);
char				*safe_strjoin(char *s1, const char *s2);
char				*append_result(char *result, char *src, int start, int end);
// here_doc
void				handle_here_doc(t_cmd *cmd, t_env **env, t_data *data);

/*** UTILS ***/
int					is_delimiteur(int type);
int					is_redir_delim(char c);
void				free_str(char **str);

// print_utils
void				print_token(t_token **token);
void				print_tab(char **tab);
void				print_cmd(t_cmd **cmd);
void				print_redir(t_redir **redir);
void				print_env(t_env **env);

// free_utils
void				free_token(t_token **token);
void				free_redir(t_redir **redir);
void				free_cmd(t_cmd **cmd);
void				free_env(t_env **env);
void				free_all(t_data *data, char *line, char *good_line);

/*** SIGNAL ***/
void				handle_sig_c(int signals);

/*** BUILTIN ***/
int                 ft_echo(t_cmd *cmd);
int					ft_pwd(t_cmd *cmd);
int					child_builtin(t_cmd *cmd);
int					parent_builtin(t_cmd *cmd);
int                 ft_is_option(char *str);
int					ft_exec_builtin(t_data *data, t_cmd *cmd);
int                 ft_exit(t_data *data, t_cmd *cmd);
int					ft_export(char **args, t_env **env_ptr);
void				print_export_error(const char *arg);
int					is_valid_identifier(const char *arg);
int					ft_unset(char **args, t_env **env_ptr);
long long			ft_atoll(const char *s);
void				print_env_array(char **env_array, int size);
void				print_export_line(char *entry);
char				**create_env_array(t_env *env, int size);
void				sort_env_array(char **env_array, int size);
void				swap_str(char **a, char **b);
int					env_list_size(t_env *env);
t_env				*find_env_var(char *arg, t_env *env);
int					process_export_arg(char *arg, t_env **env_ptr);
int					ft_cd(t_env *env, t_cmd *cmd);

/*** EXEC ***/
void                exec_mini(t_data *data);
t_exec				setup_exec_data(t_data *data);
int					count_cmd(t_data *data);
int					is_builtin(t_cmd *cmd);

// cmd_exec
void				rest_cmd_exec(t_cmd *tmp_cmd, t_exec *mini, int count, t_data *data);
void				first_or_last_cmd(t_cmd *tmp_cmd, t_exec *mini, int count, t_data *data);
int					should_run_in_parent(t_cmd *cmd);

// cmd_exec_utils
int					find_outfile(t_cmd **tmp_cmd);
int					find_infile(t_cmd **tmp_cmd);
int					open_in(t_redir *tmp_r);
int					find_outfile(t_cmd **tmp_cmd);
int					open_out(t_redir *tmp_r);
int					has_outfile(t_cmd **tmp_cmd);
int					has_infile(t_cmd **tmp_cmd);

// redir_exec
void				redir_last(int in, int out, t_exec *mini);
void				redir_rest(int in, int out, t_exec *mini, int *pipe_fd);

// execve
void				exec(t_exec *mini, t_cmd *tmp_cmd, t_data *data);
void				do_execve_bonus(t_exec *mini, t_cmd *tmp_cmd, char *path, t_env *env, t_data *data);
char				*concat_path(char *path, char *cmd);
char				*find_path_exec(t_env *env);

#endif