/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_exec.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kjolly <kjolly@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/22 16:16:29 by kjolly            #+#    #+#             */
/*   Updated: 2025/04/23 14:02:45 by kjolly           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

// ? count sert a : "mini.pidarray[count] = fork()"

void	first_no_pipe(t_cmd *tmp_cmd, t_exec *mini, int count)
{
	
}

void	first_with_pipe(t_cmd *tmp_cmd, t_exec *mini, int count)
{
	
}

void    first_cmd_exec(t_cmd *tmp_cmd, t_exec *mini, int count)
{
	int here_doc;

	(void)count;
	(void)mini;
	if  (!hd_in(tmp_cmd))
		here_doc = 0;
	else
		here_doc = 1;
	printf("%d\n", here_doc);
	if (mini->cmd_count == 1)
	    first_no_pipe(tmp_cmd, mini, count);
	else
	    first_with_pipe(tmp_cmd, mini, count);
}

void    rest_cmd_exec(t_cmd *tmp_cmd, t_exec *mini, int count)
{
	
}

void    last_cmd_exec(t_cmd *tmp_cmd, t_exec *mini, int count)
{
	
}