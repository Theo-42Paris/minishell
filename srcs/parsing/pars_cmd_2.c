/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pars_cmd_2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tzara <tzara@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/11 14:45:11 by kjolly            #+#    #+#             */
/*   Updated: 2025/05/20 12:27:24 by tzara            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	get_args_nb(t_token *token)
{
	t_token	*tmp;
	int		i;

	i = 0;
	tmp = token;
	while (tmp)
	{
		if (tmp->token == WORD)
			i++;
		tmp = tmp->next;
	}
	return (i);
}

t_cmd	*last_cmd(t_cmd *cmd)
{
	while (cmd)
	{
		if (cmd->next == NULL)
			return (cmd);
		cmd = cmd->next;
	}
	return (cmd);
}

void	add_cmd(t_cmd **cmd, t_cmd *head)
{
	t_cmd	*last;

	if (cmd)
	{
		if (*cmd)
		{
			last = last_cmd(*cmd);
			last->next = head;
		}
		else
			*cmd = head;
	}
}

void	fill_cmd(t_cmd **cmd, t_token *current)
{
	t_cmd	*head;
	int		i;

	i = get_args_nb(current);
	head = malloc(sizeof(t_cmd));
	if (!head)
		return ;
	head->args = malloc(sizeof(char *) * (i + 1));
	if (!head->args)
	{
		free(head);
		return ;
	}
	head->args[i] = NULL;
	head->redir = NULL;
	head->next = NULL;
	add_cmd(cmd, head);
}
