/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   last_cmd_exec_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kjolly <kjolly@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/23 22:25:18 by tzara             #+#    #+#             */
/*   Updated: 2025/05/27 14:50:35 by kjolly           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	prepare_builtin_redirs(t_exec *mini, int *fd, int *backup)
{
	backup[0] = -1;
	backup[1] = -1;
	if (fd[0] >= 0 || mini->fd_transfer >= 0)
		backup[0] = dup(STDIN_FILENO);
	if (fd[1] >= 0)
		backup[1] = dup(STDOUT_FILENO);
	if (fd[0] >= 0)
	{
		dup2(fd[0], STDIN_FILENO);
		close(fd[0]);
	}
	else if (mini->fd_transfer >= 0)
	{
		dup2(mini->fd_transfer, STDIN_FILENO);
		close(mini->fd_transfer);
		mini->fd_transfer = -1;
	}
	if (fd[1] >= 0)
	{
		dup2(fd[1], STDOUT_FILENO);
		close(fd[1]);
	}
}

void	restore_builtin_redirs(int *backup)
{
	if (backup[0] >= 0)
	{
		dup2(backup[0], STDIN_FILENO);
		close(backup[0]);
	}
	if (backup[1] >= 0)
	{
		dup2(backup[1], STDOUT_FILENO);
		close(backup[1]);
	}
}

void	close_fds_after_fork(t_exec *mini, int *fd)
{
	if (mini->fd_transfer >= 0)
		close(mini->fd_transfer);
	if (fd[1] >= 0)
		close(fd[1]);
	if (fd[0] >= 0)
		close(fd[0]);
}

void	child_process_exec(t_cmd *cmd, t_exec *mini, t_data *data, int *fd)
{
	redir_last(fd[0], fd[1], mini);
	close_fd_red(data->cmd);
	exec(mini, cmd, data);
	data->exit_code = 1;
	free_all(data);
	free_env(&data->env);
	free(data);
	rl_clear_history();
	exit(1);
}
