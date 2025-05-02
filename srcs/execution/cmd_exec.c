/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_exec.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kjolly <kjolly@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/22 16:16:29 by kjolly            #+#    #+#             */
/*   Updated: 2025/05/02 14:38:41 by kjolly           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

// ? count sert a : "mini.pidarray[count] = fork()"
int	first_or_last_cmd(t_cmd *tmp_cmd, t_exec *mini, int count, t_data *data)
{
	int	in;
	int	out;

	in = -1;
	out = -1;
	if (has_infile(&tmp_cmd))
	{
		in = find_infile(&tmp_cmd); //? si  pas de infile, on n'ouvre pas le outfile
		if (in == -1)
			return (0);
	}
	if (has_outfile(&tmp_cmd))
	{
		out	= find_outfile(&tmp_cmd); //? si outfile pas accessible, on ferme in on s'arrete
		if (out == -1)
		{
			if (in)
				close(in);
			return (0);
		}
	}
	if (parent_builtin(data->cmd))
	{
		ft_exec_builtin(data, data->cmd);
		return (1);
	}
	mini->pidarray[count] = fork();
	if (mini->pidarray[count] == -1)
	{
		if (out >= 0)
			close(out);
		if (in >= 0)
			close (in);
		perror("fork fail");
	}
	else if (mini->pidarray[count] == 0)
	{
		redir_last(in, out, mini);
		exec(mini, tmp_cmd, data);
	}
	else
	{
		if (mini->fd_transfer >= 0)
			close(mini->fd_transfer);
		if (out >= 0)
			close(out);
		if (in >= 0)
			close (in);
	}
	return (1);
}

// void	first_with_pipe(t_cmd *tmp_cmd, t_exec *mini, int count)
// {
		
// }

// void    first_cmd_exec(t_cmd *tmp_cmd, t_exec *mini, int count)
// {
// 	(void)count;
// 	(void)mini;
// 	if (mini->cmd_count == 1)
// 	    first_no_pipe(tmp_cmd/*, mini, count*/);
// 	// else
// 	    // first_with_pipe(tmp_cmd, mini, count);
// }

// void	rest_cmd_exec(t_cmd *tmp_cmd, t_exec *mini, int count)
// {
	
// }

// void	last_cmd_exec()
// {
	
// }
