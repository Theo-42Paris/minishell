/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   infile_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kjolly <kjolly@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/23 11:39:22 by kjolly            #+#    #+#             */
/*   Updated: 2025/05/29 10:32:14 by kjolly           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	has_infile(t_cmd **tmp_cmd)
{
	t_redir	*tmp_r;

	tmp_r = (*tmp_cmd)->redir;
	while (tmp_r)
	{
		if (tmp_r->token == REDIR_IN || tmp_r->token == DELIMITER)
			return (1);
		tmp_r = tmp_r->next;
	}
	return (0);
}

int	open_in(t_redir *tmp_r)
{
	int	in;

	in = -1;
	if (tmp_r->token == DELIMITER)
		in = tmp_r->fd_here_doc;
	else if (tmp_r->token == REDIR_IN)
	{
		if (access(tmp_r->arg, F_OK) == -1)
		{
			perror("infile");
			return (-1);
		}
		if (access(tmp_r->arg, R_OK) == -1)
		{
			perror("infile");
			return (-1);
		}
		in = open(tmp_r->arg, O_RDONLY);
		if (in == -1)
		{
			perror("infile");
			return (-1);
		}
	}
	return (in);
}

int	find_infile(t_cmd **tmp_cmd)
{
	t_redir	*tmp_r;
	int		in;

	in = -1;
	tmp_r = (*tmp_cmd)->redir;
	while (tmp_r)
	{
		if (tmp_r->token == REDIR_IN || tmp_r->token == DELIMITER)
		{
			if (in >= 0)
				close(in);
			in = open_in(tmp_r);
			if (in == -1)
				return (-1);
		}
		tmp_r = tmp_r->next;
	}
	return (in);
}
