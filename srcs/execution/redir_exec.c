/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_exec.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kjolly <kjolly@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/28 16:33:42 by kjolly            #+#    #+#             */
/*   Updated: 2025/05/27 12:13:20 by kjolly           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	redir_last(int in, int out, t_exec *mini)
{
	if (in >= 0)
	{
		if (mini->fd_transfer >= 0)
			close(mini->fd_transfer);
		dup2(in, STDIN_FILENO);
		close(in);
	}
	else if (mini->fd_transfer >= 0)
	{
		dup2(mini->fd_transfer, STDIN_FILENO);
		close(mini->fd_transfer);
	}
	if (out >= 0)
	{
		dup2(out, STDOUT_FILENO);
		close(out);
	}
}

void	redir_rest(int in, int out, t_exec *mini, int *pipe_fd)
{
	if (in >= 0)
	{
		if (mini->fd_transfer >= 0)
			close(mini->fd_transfer);
		dup2(in, STDIN_FILENO);
		close(in);
	}
	else if (mini->fd_transfer >= 0)
	{
		dup2(mini->fd_transfer, STDIN_FILENO);
		close(mini->fd_transfer);
	}
	if (out >= 0)
	{
		dup2(out, STDOUT_FILENO);
		close(out);
	}
	else
		dup2(pipe_fd[1], STDOUT_FILENO);
	close(pipe_fd[1]);
	close(pipe_fd[0]);
}
