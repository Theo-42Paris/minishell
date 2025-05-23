/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   outfile_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kjolly <kjolly@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/23 11:25:03 by kjolly            #+#    #+#             */
/*   Updated: 2025/05/23 11:25:19 by kjolly           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	has_outfile(t_cmd **tmp_cmd)
{
	t_redir	*tmp_r;

	tmp_r = (*tmp_cmd)->redir;
	while (tmp_r)
	{
		if (tmp_r->token == REDIR_OUT || tmp_r->token == APPEND)
			return (1);
		tmp_r = tmp_r->next;
	}
	return (0);
}

int	open_out(t_redir *tmp_r)
{
	int	out;

	out = -1;
	if (access(tmp_r->arg, F_OK) == 0)
	{
		if (access(tmp_r->arg, W_OK) == -1)
		{
			perror("outfile");
			return (-1);
		}
	}
	if (tmp_r->token == REDIR_OUT)
		out = open(tmp_r->arg, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	else if (tmp_r->token == APPEND)
		out = open(tmp_r->arg, O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (out == -1)
		perror("outfile");
	return (out);
}

int	find_outfile(t_cmd **tmp_cmd)
{
	t_redir	*tmp_r;
	int		out;

	out = -1;
	tmp_r = (*tmp_cmd)->redir;
	while (tmp_r)
	{
		if (tmp_r->token == REDIR_OUT || tmp_r->token == APPEND)
		{
			if (out >= 0)
				close(out);
			out = open_out(tmp_r);
			if (out == -1)
				return (-1);
		}
		tmp_r = tmp_r->next;
	}
	return (out);
}
