/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kjolly <kjolly@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/15 16:56:33 by kjolly            #+#    #+#             */
/*   Updated: 2025/03/24 09:27:49 by kjolly           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"


// int	get_nb_cmd(t_token **token)
// {
// 	t_token	*current;
// 	int		i;

// 	if (!token);
// 		return (NULL);
// 	i = 1;
// 	current = *token;
// 	while (current)
// 	{
// 		if (current->type == 2)
// 			i++;
// 		current = current->next;
// 	}
// 	return (i);
// }

// int		get_size_cmd(t_token **token, int count_cmd)
// {
// 	t_token	*current;
// 	int		size;

// 	size = 0;
// 	current = *token;
// 	while (current)
// 	{
		
// 		if (current->type == 2)
// 			compl_cmd();
// 		current = current->next;
// 	}
// 	return (size);
// }

// void	init_cmd(t_cmd **cmd, t_token **token, int count_cmd)
// {
// 	t_cmd	*head;
// 	int		size_cmd;

// 	size_cmd = get_size_cmd(token, count_cmd);
// 	head = new_cmd(size_cmd);
// }

// void	token_to_cmd(t_cmd **cmd, t_token **token)
// {
// 	int		count_cmd;
// 	int		count_args;
// 	t_token	*current;

// 	if (!token)
// 		return ;
// 	current = *token;
// 	count_cmd = get_nb_cmd(token);
// 	while (count_cmd)
// 	{
// 		init_cmd(token, cmd, count_cmd);
// 		count_cmd--;
// 	}
// }
/**************************************************************************/



//todo | prendre tout dans une chaine jusqu'a un pipe
//todo | puis separer dans la liste chainer cmd

int	is_delimiteur(int type)
{
	if (type == 1 || type == 2)
		return (0);
	else
		return (1);
}

int	syntax_node(int start, int end, t_token *current, t_token *prev)
{
	//todo | ecrire les erreurs dans le stderror putstr_fd(3)
	if (start)
	{
		if (current->type == 2)
		{
			ft_printf("minishell: syntax error near unexepted token '|'\n");
			return (0);
		}
		else if (current->next == NULL && is_delimiteur(current->type))
		{
			ft_printf("minishell: syntax error near unexepted token 'newline'\n");
			return (0);
		}
	}
	else if (!start)
	{
		if (current->type == 2 && is_delimiteur(prev->type))
		{
			ft_printf("minishell: syntax error near unexepted token '|'\n");
			return (0);
		}
		else if (current->type == 2 && prev->type == 2)
		{
			ft_printf("minishell: syntax error near unexepted token '|'\n");
			return (0);
		}
	}
	else if (end)
	{
		if (current->type == 2)
		{
			ft_printf("minishell: syntax error near unexepted token '|'\n");
			return (0);
		}
		else if (is_delimiteur(current->type))
		{
			ft_printf("minishell: syntax error near unexepted token 'newline'\n");
			return (0);			
		}
	}
	return (1);
}

void	check_syntax(t_token **token)
{
	t_token	*current;
	t_token *prev;
	int		start;
	int		end;

	start = 1;
	end = 0;
	prev = NULL;
	current = *token;
	while (current)
	{
		if (current->next == NULL && start == 0)
			end = 1;
		if (!syntax_node(start, end, current, prev))
			break ;
		start = 0;
		prev = current;
		current = current->next;
	}
}
