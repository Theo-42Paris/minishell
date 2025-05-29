/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rest_cmd_exec.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kjolly <kjolly@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/22 16:16:29 by kjolly            #+#    #+#             */
/*   Updated: 2025/05/29 10:40:41 by kjolly           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	ft_file(int *in, int *out, t_cmd *tmp_cmd)
{
	*in = -1;
	*out = -1;
	if (has_infile(&tmp_cmd))
	{
		*in = find_infile(&tmp_cmd);
		if (*in == -1)
			return (0);
	}
	if (has_outfile(&tmp_cmd))
	{
		*out = find_outfile(&tmp_cmd);
		if (*out == -1)
		{
			if (*in >= 0)
				close(*in);
			return (0);
		}
	}
	return (1);
}

void	exec_rest_parent(t_exec *mini, int out, int in, int *pipe_fd)
{
	if (mini->fd_transfer >= 0)
		close(mini->fd_transfer);
	if (out >= 0)
		close(out);
	if (in >= 0)
		close(in);
	close(pipe_fd[1]);
	mini->fd_transfer = pipe_fd[0];
}

void	fork_error(int out, int in, int *pipe_fd)
{
	if (out >= 0)
		close(out);
	if (in >= 0)
		close(in);
	close(pipe_fd[0]);
	close(pipe_fd[1]);
	perror("fork fail");
}

void	follow_rest_child(t_data *data, t_cmd *tmp_cmd, t_exec *mini)
{
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
	close_fd_red(data->cmd);
	exec(mini, tmp_cmd, data);
	data->exit_code = 1;
	free_all(data);
	free_env(&data->env);
	free(data);
	rl_clear_history();
	exit(1);
}

int	rest_cmd_exec(t_cmd *tmp_cmd, t_exec *mini, int count, t_data *data)
{
	int	in;
	int	out;
	int	pipe_fd[2];

	if (!ft_file(&in, &out, tmp_cmd))
		return (0);
	if (pipe(pipe_fd) == -1)
	{
		if (in >= 0)
			close(in);
		if (out >= 0)
			close(out);
		return (perror("pipe"), 0);
	}
	mini->pidarray[count] = fork();
	if (mini->pidarray[count] == -1)
		fork_error(in, out, pipe_fd);
	else if (mini->pidarray[count] == 0)
	{
		redir_rest(in, out, mini, pipe_fd);
		follow_rest_child(data, tmp_cmd, mini);
	}
	else
		exec_rest_parent(mini, out, in, pipe_fd);
	return (1);
}
