/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   alone_cmd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tzara <tzara@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/27 12:30:09 by kjolly            #+#    #+#             */
/*   Updated: 2025/05/27 21:01:57 by tzara            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	alone_child(t_data *data, t_cmd *tmp_cmd, t_exec *mini)
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

void	redir_alone(int in, int out)
{
	if (in >= 0)
	{
		dup2(in, STDIN_FILENO);
		close(in);
	}
	if (out >= 0)
	{
		dup2(out, STDOUT_FILENO);
		close(out);
	}
}

void	fork_error_alone(int out, int in)
{
	if (out >= 0)
		close(out);
	if (in >= 0)
		close(in);
	perror("fork fail");
}

void	alone_cmd(t_cmd *tmp_cmd, t_exec *mini, int count, t_data *data)
{
	int	in;
	int	out;

	if (parent_builtin(tmp_cmd))
	{
		ft_file(&in, &out, tmp_cmd);
		ft_exec_builtin(data, tmp_cmd, mini);
		return ;
	}
	if (!ft_file(&in, &out, tmp_cmd))
		return ;
	mini->pidarray[count] = fork();
	if (mini->pidarray[count] == -1)
		fork_error_alone(out, in);
	else if (mini->pidarray[count] == 0)
	{
		redir_alone(in, out);
		alone_child(data, tmp_cmd, mini);
	}
	if (out >= 0)
		close(out);
	if (in >= 0)
		close(in);
}
