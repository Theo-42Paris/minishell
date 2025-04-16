/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pars_cmd_3.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kjolly <kjolly@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/11 14:46:54 by kjolly            #+#    #+#             */
/*   Updated: 2025/04/16 17:08:42 by kjolly           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

t_redir	*last_redir(t_redir *redir)
{
	while (redir)
	{
		if (redir->next == NULL)
			return (redir);
		redir = redir->next;
	}
	return (redir);
}

void	fill_redir(t_redir **redir, t_token *current)
{
	t_redir	*new;
	t_redir	*last;

	new = malloc(sizeof(t_redir));
	if (!new)
		return ;
	new->arg = ft_strdup(current->next->data);
	if (!new->arg)
	{
		free(new);
		return ;
	}
	new->token = current->token;
	new->fd_here_doc = -1;
	new->next = NULL;
	if (redir)
	{
		if (*redir)
		{
			last = last_redir(*redir);
			last->next = new;
		}
		else
			*redir = new;
	}
}
