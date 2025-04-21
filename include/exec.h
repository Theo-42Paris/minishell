/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kjolly <kjolly@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/21 12:37:08 by kjolly            #+#    #+#             */
/*   Updated: 2025/04/21 12:38:15 by kjolly           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXEC_H
# define EXEC_H

#include "minishell.h"

/**********Builtins***********/
int					ft_echo(t_data *data, t_cmd *cmd);
int					ft_pwd(t_cmd *cmd);
int					ft_isbuiltin(t_cmd *cmd);
int					ft_is_option(char *str);
int					ft_exec_builtin(t_data *data, t_cmd *cmd);
void				handle_sig_c(int signals);

#endif
