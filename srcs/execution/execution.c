/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kjolly <kjolly@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/21 15:22:39 by kjolly            #+#    #+#             */
/*   Updated: 2025/04/21 17:50:15 by kjolly           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

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

void    exec_mini(t_data *data)
{
    int cmd_count;

    if (!data)
        return;
    cmd_count = count_cmd(data);
    if (cmd_count == 1 && ft_isbuiltin(data->cmd))
        ft_exec_builtin(data, data->cmd);
}
