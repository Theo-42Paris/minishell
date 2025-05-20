/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_exec_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kjolly <kjolly@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/23 11:39:22 by kjolly            #+#    #+#             */
/*   Updated: 2025/05/20 17:53:07 by kjolly           ###   ########.fr       */
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

int	open_in(t_redir *tmp_r)
{
	int	in;

	in = 0;
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

// int	hd_in(t_cmd *tmp_cmd)
// {
// 	t_cmd *tmp;

// 	tmp = tmp_cmd;
// 	while (tmp)
// 	{
// 		while (tmp->redir)
// 		{
// 			if (tmp->redir->token == DELIMITER)
// 				return (1);
// 			tmp->redir = tmp->redir->next;
// 		}
// 		tmp = tmp->next;
// 	}
// 	return (0);
// }
