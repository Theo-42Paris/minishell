/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pars_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tzara <tzara@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/24 09:09:42 by kjolly            #+#    #+#             */
/*   Updated: 2025/05/20 12:27:20 by tzara            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

// char	*safe_dup(t_token *current, t_token *prev, t_env **env, t_data *data)
// {
// 	char	*tmp;

// 	if ((current->token == WORD && current->exp == 1)
// 		&& (!prev || !is_delimiteur(prev->token)))
// 	{
// 		tmp = expandables(current->data, env, data);
// 		if (!tmp)
// 			return (NULL);
// 		return (tmp);
// 	}
// 	else
// 		return (ft_strdup(current->data));
// }

void	first_if_cmd(t_token **current, t_token **prev, t_cmd **cmd)
{
	if ((*current)->token == REDIR_IN || (*current)->token == REDIR_OUT
		|| (*current)->token == DELIMITER || (*current)->token == APPEND)
	{
		if ((*current)->next)
			fill_redir(&((*cmd)->redir), *current);
		*prev = *current;
		*current = (*current)->next;
	}
}

void	get_cmd(t_token *token, t_cmd **cmd, t_data *data)
{
	t_token	*current;
	t_token	*prev;
	int		i;

	i = 0;
	prev = NULL;
	current = token;
	if (!(*cmd))
		fill_cmd(cmd, current);
	while (current && current->token != PIPE)
	{
		first_if_cmd(&current, &prev, cmd);
		if (current && current->token == WORD && (!prev
				|| !is_delimiteur(prev->token)))
			(*cmd)->args[i++] = ft_strdup(current->data);
		prev = current;
		current = current->next;
	}
	(*cmd)->args[i] = NULL;
	get_cmd_2(current, cmd, data);
}

void	get_cmd_2(t_token *current, t_cmd **cmd, t_data *data)
{
	if (current && current->token == PIPE)
		current = current->next;
	if (current)
	{
		fill_cmd(&((*cmd)->next), current);
		get_cmd(current, &((*cmd)->next), data);
	}
}

// void	init_data_cmd(t_token *token, t_cmd **cmd, t_token **current)
// {
// 	*current = token;
// 	if (!token || !cmd)
// 		return ;
// 	if (!(*cmd))
// 		fill_cmd(cmd, *current);
// }

// int	check_tok(t_token *current)
// {
// 	if (current->token == REDIR_IN || current->token == REDIR_OUT
// 		|| current->token == DELIMITER || current->token == APPEND)
// 		return (1);
// 	else
// 		return (0);
// }

// void	win_2_line_2(t_token **prev, t_token **current)
// {
// 	*prev = *current;
// 	*current = (*current)->next;
// }

// void	get_cmd(t_token *token, t_cmd **cmd)
// {
// 	t_token	*current;
// 	t_token	*prev;
// 	int		i;

// 	i = 0;
// 	prev = NULL;
// 	init_data_cmd(token, cmd, &current);
// 	if (!token || !cmd)
// 		return ;
// 	while (current && current->token != PIPE)
// 	{
// 		if (check_tok(current) == 1)
// 		{
// 			if (current->next)
// 				fill_redir(&((*cmd)->redir), current);
// 			prev = current;
// 			current = current->next;
// 		}
// 		if (current && current->token == WORD && (!prev
// 				|| !is_delimiteur(prev->token)))
// 			(*cmd)->args[i++] = ft_strdup(current->data);
// 		win_2_line_2(&prev, &current);
// 	}
// 	(*cmd)->args[i] = NULL;
// 	get_cmd_2(current, cmd);
// }

// void	get_cmd_2(t_token *current, t_cmd **cmd)
// {
// 	if (current && current->token == PIPE)
// 		current = current->next;
// 	if (current)
// 	{
// 		fill_cmd(&((*cmd)->next), current);
// 		get_cmd(current, &((*cmd)->next));
// 	}
// }
//-------------------------------------------------------------------------/
// void	get_cmd(t_token *token, t_cmd **cmd)
// {
// 	t_token	*current;
// 	t_token	*prev;
// 	int		i;

// 	i = 0;
// 	prev = NULL;
// 	init_data_cmd(token, cmd, &current);
// 	while (current && current->token != PIPE)
// 	{
// 		if (check_tok(current) == 1)
// 		{
// 			if (current->next)
// 				fill_redir(&((*cmd)->redir), current);
// 			prev = current;
// 			current = current->next;
// 		}
// 		if (current && current->token == WORD && (!prev
//|| !is_delimiteur(prev->token)))
// 			(*cmd)->args[i++] = ft_strdup(current->data);
// 		prev = current;
// 		current = current->next;
// 	}
// 	(*cmd)->args[i] = NULL;
// 	if (current && current->token == PIPE)
// 		current = current->next;
// 	if (current)
// 	{
// 		fill_cmd(&((*cmd)->next), current);
// 		get_cmd(current, &((*cmd)->next));
// 	}
// }
