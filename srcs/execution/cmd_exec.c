/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_exec.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kjolly <kjolly@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/22 16:16:29 by kjolly            #+#    #+#             */
/*   Updated: 2025/05/01 18:15:17 by kjolly           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

// ? count sert a : "mini.pidarray[count] = fork()"
int	dor_et_de_platine(t_cmd *tmp_cmd, t_exec *mini, int count, t_data *data)
{
	int	in;
	int	out;

	if (has_infile(tmp_cmd))
	{
		in = find_infile(tmp_cmd); //? si  pas de infile, on n'ouvre pas le outfile
		if (in == -1)
			return (0);
	}
	if (has_outfile(tmp_cmd))
	{
		out	= find_outfile(tmp_cmd); //? si outfile pas accessible, on ferme in on s'arrete
		if (out == -1)
		{
			if (in)
				close(in);
			return (0);
		}
	}
	mini->pidarray[count] = fork();
	if (mini->pidarray[count] == -1)
	{
		close(in);
		close(out);
		perror("pipe fail");
	}
	else if (mini->pidarray[count] == 0)
	{
		redir_last(in, out, mini);
		exec(mini, tmp_cmd, data);
	}
	else
	{
		if (mini->fd_transfer)
			close(mini->fd_transfer);
		if (out)
			close(out);
		if (in)
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
