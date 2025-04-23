/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_exec_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kjolly <kjolly@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/23 11:39:22 by kjolly            #+#    #+#             */
/*   Updated: 2025/04/23 14:00:38 by kjolly           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	hd_in(t_cmd *tmp_cmd)
{
	t_cmd *tmp;

	tmp = tmp_cmd;
	while (tmp)
	{
		while (tmp->redir)
		{
			if (tmp->redir->token == DELIMITER)
				return (1);
			tmp->redir = tmp->redir->next;
		}
		tmp = tmp->next;
	}
	return (0);
}
