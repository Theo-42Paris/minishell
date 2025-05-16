/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kjolly <kjolly@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/21 15:22:39 by kjolly            #+#    #+#             */
/*   Updated: 2025/05/16 16:44:07 by kjolly           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

// ? peut importe ou se trouve la derniere redir in, elle est prioritaire
// ? idem pour le outfile

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

void	exec_mini(t_data *data)
{
	t_exec	mini;
	t_cmd	*cmd_tmp;
	int		count;
	int		j;
	int 	status;

	count = 0;
	j = -1;
	status = 0;
	if (!data || !data->cmd)
		return ;
	cmd_tmp = data->cmd;
	mini = setup_exec_data(data);
	if (mini.cmd_count == 1 && parent_builtin(data->cmd))
	{
		data->exit_code = ft_exec_builtin(data, data->cmd);
		free(mini.pidarray);
		return ;
	}
	while (cmd_tmp)
	{
		if (count == mini.cmd_count - 1)
			first_or_last_cmd(cmd_tmp, &mini, count, data);
		else
			rest_cmd_exec(cmd_tmp, &mini, count, data);
		count++;
		cmd_tmp = cmd_tmp->next;
	}
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
