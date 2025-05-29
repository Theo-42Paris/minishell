/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kjolly <kjolly@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/21 15:22:39 by kjolly            #+#    #+#             */
/*   Updated: 2025/05/29 10:46:47 by kjolly           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	count_cmd(t_data *data)
{
	t_cmd	*tmp;
	int		count;

	count = 0;
	tmp = data->cmd;
	while (tmp)
	{
		count++;
		tmp = tmp->next;
	}
	return (count);
}

t_exec	setup_exec_data(t_data *data)
{
	t_exec	tmp;

	tmp.cmd_count = count_cmd(data);
	tmp.fd_transfer = -1;
	tmp.pidarray = ft_calloc(tmp.cmd_count, sizeof(pid_t));
	if (!tmp.pidarray)
		perror("malloc");
	return (tmp);
}

int	first_loop(t_cmd *cmd_tmp, t_exec mini, t_data *data)
{
	int	count;

	count = 0;
	if (mini.cmd_count == 1)
		alone_cmd(cmd_tmp, &mini, count, data);
	else
	{
		while (cmd_tmp)
		{
			if (count == mini.cmd_count - 1)
			{
				if (!last_cmd_exec(cmd_tmp, &mini, count, data))
					break ;
			}
			else
			{
				if (!rest_cmd_exec(cmd_tmp, &mini, count, data))
					break ;
			}
			count++;
			cmd_tmp = cmd_tmp->next;
		}
	}
	return (count);
}

static void	handle_exit_status(t_data *data, int status)
{
	int	sig;

	if (WIFEXITED(status))
		data->exit_code = WEXITSTATUS(status);
	else if (WIFSIGNALED(status))
	{
		sig = WTERMSIG(status);
		if (sig == SIGQUIT)
			write(1, "\nQuit (core dumped)\n", 20);
		else if (sig == SIGINT)
			write(1, "\n", 1);
		data->exit_code = 128 + sig;
	}
}

void	exec_mini(t_data *data)
{
	t_exec	mini;
	t_cmd	*cmd_tmp;
	int		j;
	int		status;

	if (!data || !data->cmd)
		return ;
	signal(SIGINT, SIG_IGN);
	signal(SIGQUIT, SIG_IGN);
	cmd_tmp = data->cmd;
	mini = setup_exec_data(data);
	first_loop(cmd_tmp, mini, data);
	j = -1;
	while (++j < mini.cmd_count)
		if (mini.pidarray[j] > 0 && waitpid(mini.pidarray[j], &status, 0) > 0)
			handle_exit_status(data, status);
	signal(SIGINT, handle_sig_c);
	signal(SIGQUIT, SIG_IGN);
	if (mini.fd_transfer >= 0)
		close(mini.fd_transfer);
	free(mini.pidarray);
}
