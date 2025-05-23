/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   last_cmd_exec.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kjolly <kjolly@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/23 13:30:58 by kjolly            #+#    #+#             */
/*   Updated: 2025/05/23 13:31:29 by kjolly           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	first_or_last_cmd(t_cmd *tmp_cmd, t_exec *mini, int count, t_data *data)
{
	int	in;
	int	out;
	int	stdin_backup;
	int	stdout_backup;

	in = -1;
	out = -1;
	if (has_infile(&tmp_cmd))
	{
		in = find_infile(&tmp_cmd);
		if (in == -1)
			return ;
	}
	if (has_outfile(&tmp_cmd))
	{
		out = find_outfile(&tmp_cmd);
		if (out == -1)
		{
			if (in >= 0)
				close(in);
			return ;
		}
	}
	if (count == mini->cmd_count - 1 && parent_builtin(tmp_cmd))
	{
		stdin_backup = -1;
		stdout_backup = -1;
		if (in >= 0 || mini->fd_transfer >= 0)
			stdin_backup = dup(STDIN_FILENO);
		if (out >= 0)
			stdout_backup = dup(STDOUT_FILENO);
		if (in >= 0)
		{
			dup2(in, STDIN_FILENO);
			close(in);
		}
		else if (mini->fd_transfer >= 0)
		{
			dup2(mini->fd_transfer, STDIN_FILENO);
			close(mini->fd_transfer);
			mini->fd_transfer = -1;
		}
		if (out >= 0)
		{
			dup2(out, STDOUT_FILENO);
			close(out);
		}
		data->exit_code = ft_exec_builtin(data, tmp_cmd, mini);
		if (stdin_backup >= 0)
		{
			dup2(stdin_backup, STDIN_FILENO);
			close(stdin_backup);
		}
		if (stdout_backup >= 0)
		{
			dup2(stdout_backup, STDOUT_FILENO);
			close(stdout_backup);
		}
		return ;
	}
	mini->pidarray[count] = fork();
	if (mini->pidarray[count] == -1)
	{
		if (out >= 0)
			close(out);
		if (in >= 0)
			close(in);
		perror("fork fail");
	}
	else if (mini->pidarray[count] == 0)
	{
		redir_last(in, out, mini);
		close_fd_red(data->cmd);
		exec(mini, tmp_cmd, data);
		data->exit_code = 1;
		free_all(data);
		free_env(&data->env);
		free(data);
		rl_clear_history();
		exit(1);
	}
	else
	{
		if (mini->fd_transfer >= 0)
			close(mini->fd_transfer);
		if (out >= 0)
			close(out);
		if (in >= 0)
			close(in);
	}
}
