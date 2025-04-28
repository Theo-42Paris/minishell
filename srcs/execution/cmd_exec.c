/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_exec.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kjolly <kjolly@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/22 16:16:29 by kjolly            #+#    #+#             */
/*   Updated: 2025/04/28 16:39:53 by kjolly           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

// ? count sert a : "mini.pidarray[count] = fork()"

int	last_cmd_exec(t_cmd *tmp_cmd, t_exec *mini, int count)
{
	int	in;
	int	out;
//! revoir ca car certains cas n'ont pas besoin d'infile et/ou outfile
	in = find_infile(tmp_cmd); //? si  pas de infile, on n'ouvre pas le outfile
	if (!in)
		return (0);
	out	= find_outfile(tmp_cmd); //? si outfile pas accessible, on ferme in on s'arrete
	if (!out)
	{
		close(in);
		return (0);
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
		redir(in, out, mini);
		exec(mini, tmp_cmd);
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
