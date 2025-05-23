/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kjolly <kjolly@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/21 15:22:39 by kjolly            #+#    #+#             */
/*   Updated: 2025/05/23 11:22:58 by kjolly           ###   ########.fr       */
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
	tmp.pidarray = malloc(sizeof(pid_t) * tmp.cmd_count);
	if (!tmp.pidarray)
		perror("malloc");
	return (tmp);
}

int	first_loop(t_cmd *cmd_tmp, t_exec mini, t_data *data)
{
	int	count;

	count = 0;
	while (cmd_tmp)
	{
		if (count == mini.cmd_count - 1)
			first_or_last_cmd(cmd_tmp, &mini, count, data);
		else
			rest_cmd_exec(cmd_tmp, &mini, count, data);
		count++;
		cmd_tmp = cmd_tmp->next;
	}
	return (count);
}

void	exec_mini(t_data *data)
{
	t_exec	mini;
	t_cmd	*cmd_tmp;
	int		j;
	int		status;

	j = -1;
	status = 0;
	if (!data || !data->cmd)
		return ;
	cmd_tmp = data->cmd;
	mini = setup_exec_data(data);
	first_loop(cmd_tmp, mini, data);
	while (++j < mini.cmd_count)
	{
		if (mini.pidarray[j] > 0 && waitpid(mini.pidarray[j], &status, 0) > 0)
		{
			if (WIFEXITED(status))
				data->exit_code = WEXITSTATUS(status);
			else if (WIFSIGNALED(status))
				data->exit_code = 128 + WTERMSIG(status);
		}
	}
	if (mini.fd_transfer >= 0)
		close(mini.fd_transfer);
	free(mini.pidarray);
}
