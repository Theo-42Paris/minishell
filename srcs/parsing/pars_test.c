/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pars_test.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kjolly <kjolly@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/24 09:09:42 by kjolly            #+#    #+#             */
/*   Updated: 2025/03/24 15:45:09 by kjolly           ###   ########.fr       */
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
		if (tmp->type == 1)
			i++;
		tmp = tmp->next;
	}
	return (i);
}

t_cmd	*new_cmd(t_token *current)
{
	t_cmd	*cmd;
	int		i;

	i = get_args_nb(current);
	cmd = malloc(sizeof(t_cmd));
	if (!cmd)
		return (NULL);
	cmd->args = malloc(sizeof(char *) * (i + 1));
	cmd->cmd = NULL;
	cmd->redir = NULL;
	cmd->next = NULL;
	cmd->args[i] = NULL;
	return (cmd);
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

void    fill_cmd(t_cmd **cmd, t_token *current)
{
	t_cmd *head;

	head = new_cmd(current);
	if (!head)
		return ;
	add_cmd(cmd, head);
}

void    test(t_token **token, t_cmd **cmd)
{
	t_token	*current;
	int		i;

	i = 0;
	current = *token;
	if (!token || !*token || !cmd)
		return ;
	if (!(*cmd))
		fill_cmd(cmd, current);
	while (current && current->type != PIPE)
	{
		if (current->type == 3 || current->type == 4 ||
			current->type == 5 || current->type == 6)
		{
			if (!(*cmd)->redir)
			{
				(*cmd)->redir = malloc(sizeof(t_redir));
				if (!(*cmd)->redir)
					return ;
				(*cmd)->redir->next = NULL;
			}
			if (current->next)
				(*cmd)->redir->arg = ft_strdup(current->next->data);
			else
				(*cmd)->redir->arg = NULL;
			(*cmd)->redir->type = current->type;
			(*cmd)->redir = (*cmd)->redir->next;
		}
		if (current->type == 1)
		{
			if (current->cmd == 1)
				(*cmd)->cmd = ft_strdup(current->data);
			(*cmd)->args[i] = ft_strdup(current->data);
			i++;
		}
		current = current->next;
	}
	if (current)
	{
		fill_cmd(&((*cmd)->next), current);
		test(&current, &((*cmd)->next));
	}
}
