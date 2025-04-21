/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kjolly <kjolly@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/21 12:34:40 by kjolly            #+#    #+#             */
/*   Updated: 2025/04/21 12:35:49 by kjolly           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
# define PARSING_H

#include "minishell.h"

/*** pars_token ***/
char				*append_char(char *word, char c);
void				first_if_token(char *c, int *in_quote, int *exp, char *quote_char);
void				win_2_line(t_token **token, char **current_word, int *exp);
void				init_var(int *in_q, char *quote_c, char **cur_wrd, int *exp);
void				tokenizer(t_token **tokens, char *cmd);
/*** pars_token_2 ***/
int					count_line(char *line);
void				pre_token2(char **line, int *i, char **dest, int *j);
char				*pre_token(char *line);
void				ft_strcpy(char *dst, char *src);
/*** pars_token_3 ***/
int					check_type(char *src);
t_token				*last_token(t_token *token);
void				add_token(t_token **token, t_token *tmp);
t_token				*new_token(char *src, int exp);
void				compl_token_list(t_token **token, char *src, int exp);
/*** pars_syntax ***/
int					slovaquie(t_token *current);
int					violence_urbaine_emeute(t_token *current, t_token *prev);
int					syntax_node(int start, int end, t_token *current, t_token *prev);
int					check_syntax(t_token **token);
/*** pars_env ***/
t_env				*last_env(t_env *env);
void				fill_env(char *envp, t_env **env);
void				get_env(t_env **env, char **envp);
/*** pars_cmd ***/
void				first_if_cmd(t_token **current, t_token **prev, t_cmd **cmd);
void				get_cmd(t_token *token, t_cmd **cmd, t_env **env);
void				get_cmd_2(t_token *current, t_cmd **cmd, t_env **env);
/*** pars_cmd_2 ***/
int					get_args_nb(t_token *token);
t_cmd				*last_cmd(t_cmd *cmd);
void				add_cmd(t_cmd **cmd, t_cmd *head);
void				fill_cmd(t_cmd **cmd, t_token *current);
/*** pars_cmd_3 ***/
t_redir				*last_redir(t_redir *redir);
void				fill_redir(t_redir **redir, t_token *current);
/*** expand ***/
char				*expandables(char *src, t_env **env);
char				*safe_strjoin(char *s1, const char *s2);
char				*append_result(char *result, char *src, int start, int end);
/*** here_doc ***/
void				handle_here_doc(t_cmd *cmd, t_env **env);

#endif
