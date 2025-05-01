/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kjolly <kjolly@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/21 15:22:39 by kjolly            #+#    #+#             */
/*   Updated: 2025/05/01 18:14:18 by kjolly           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

// ? peut importe ou se trouve la derniere redir in, elle est prioritaire
// ? idem pour le outfile

int count_cmd(t_data *data)
{
	t_cmd   *tmp;
	int     count;

	count = 0;
	tmp = data->cmd;
	while (tmp)
	{
		count++;
		tmp = tmp->next;
	}
	return (count);
}

t_exec  setup_exec_data(t_data *data)
{
	t_exec	tmp;
	
	tmp.cmd_count = count_cmd(data);
	tmp.fd_transfer = -1;
	tmp.pidarray = malloc(sizeof(pid_t) * tmp.cmd_count);
	if (!tmp.pidarray)
		perror("malloc");
	return (tmp);
}

void    exec_mini(t_data *data)
{
	t_exec  mini;
	t_cmd	*cmd_tmp;
	int		count;
	int		j;

	count = 0;
	j = -1;
	if (!data)
		return;
	cmd_tmp = (*data).cmd;
	mini = setup_exec_data(data);
	// if (ft_isbuiltin(data->cmd))
		// ft_exec_builtin(data, data->cmd);
	while (cmd_tmp)
	{
		// if (count == 0)
		// 	first_cmd_exec(cmd_tmp, &mini, count);
		if (count == mini.cmd_count - 1)
			dor_et_de_platine(cmd_tmp, &mini, count, data);
		// else
		// 	rest_cmd_exec(cmd_tmp, &mini, count);
		count++;
		cmd_tmp = cmd_tmp->next;
	}
	while (++j < mini.cmd_count)
		waitpid(mini.pidarray[j], NULL, 0);
	// close(mini.fd_transfer);
	// free(mini.pidarray);
}
