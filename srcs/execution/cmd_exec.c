/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_exec.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kjolly <kjolly@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/22 16:16:29 by kjolly            #+#    #+#             */
/*   Updated: 2025/04/28 16:01:57 by kjolly           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

// ? count sert a : "mini.pidarray[count] = fork()"

int	last_cmd_exec(t_cmd *tmp_cmd, t_exec *mini, int count)
{
	int	in;
	int	out;

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
