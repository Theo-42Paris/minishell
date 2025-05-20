/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pars_syntax.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tzara <tzara@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/15 16:56:33 by kjolly            #+#    #+#             */
/*   Updated: 2025/05/20 12:27:01 by tzara            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	slovaquie(t_token *current)
{
	if (current->token == PIPE)
	{
		ft_putstr_fd("minishell: syntax error near unexepted token '|'\n", 2);
		return (0);
	}
	else if (current->next == NULL && is_delimiteur(current->token))
	{
		ft_putstr_fd("minishell: syntax error near unexepted token 'newline'\n",
			2);
		return (0);
	}
	else if (is_delimiteur(current->token)
		&& is_delimiteur(current->next->token))
	{
		ft_putstr_fd("minishell: syntax error near unexepted token 'newline'\n",
			2);
		return (0);
	}
	return (1);
}

int	violence_urbaine_emeute(t_token *current, t_token *prev)
{
	if (current->token == PIPE && is_delimiteur(prev->token))
	{
		ft_putstr_fd("minishell: syntax error near unexepted token '|'\n", 2);
		return (0);
	}
	else if (current->token == 2 && prev->token == 2)
	{
		ft_putstr_fd("minishell: syntax error near unexepted token '|'\n", 2);
		return (0);
	}
	else if (is_delimiteur(current->token) && is_delimiteur(prev->token))
	{
		ft_putstr_fd("minishell: syntax error near unexepted token 'newline'\n",
			2);
		return (0);
	}
	return (1);
}

int	potato_salad(t_token *current)
{
	if (current->token == PIPE)
	{
		ft_putstr_fd("minishell: syntax error near unexepted token '|'\n", 2);
		return (0);
	}
	else if (is_delimiteur(current->token))
	{
		ft_putstr_fd("minishell: syntax error near unexepted token 'newline'\n",
			2);
		return (0);
	}
	return (1);
}

int	syntax_node(int start, int end, t_token *current, t_token *prev)
{
	if (start)
	{
		if (!slovaquie(current))
			return (0);
	}
	else if (!start && !end)
	{
		if (!violence_urbaine_emeute(current, prev))
			return (0);
	}
	else if (end)
	{
		if (!potato_salad(current))
			return (0);
	}
	return (1);
}

int	check_syntax(t_token **token)
{
	t_token	*current;
	t_token	*prev;
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
			return (0);
		start = 0;
		prev = current;
		current = current->next;
	}
	return (1);
}
