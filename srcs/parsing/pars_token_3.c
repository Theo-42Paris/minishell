/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pars_token_3.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tzara <tzara@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/11 12:01:27 by kjolly            #+#    #+#             */
/*   Updated: 2025/05/20 12:26:56 by tzara            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	check_type(char *src)
{
	if (!strncmp(src, "|", ft_strlen(src)))
		return (PIPE);
	else if (!strncmp(src, "<", ft_strlen(src)))
		return (REDIR_IN);
	else if (!strncmp(src, ">", ft_strlen(src)))
		return (REDIR_OUT);
	else if (!strncmp(src, "<<", ft_strlen(src)))
		return (DELIMITER);
	else if (!strncmp(src, ">>", ft_strlen(src)))
		return (APPEND);
	else
		return (WORD);
}

t_token	*last_token(t_token *token)
{
	while (token)
	{
		if (token->next == NULL)
			return (token);
		token = token->next;
	}
	return (token);
}

void	add_token(t_token **token, t_token *tmp)
{
	t_token	*last;

	if (token)
	{
		if (*token)
		{
			last = last_token(*token);
			last->next = tmp;
		}
		else
			*token = tmp;
	}
}

t_token	*new_token(char *src)
{
	t_token	*tmp;

	tmp = malloc(sizeof(t_token));
	if (!tmp)
		return (NULL);
	tmp->data = ft_strdup(src);
	if (!tmp->data)
	{
		free(tmp);
		return (NULL);
	}
	tmp->token = check_type(tmp->data);
	tmp->next = NULL;
	return (tmp);
}

void	compl_token_list(t_token **token, char *src)
{
	t_token	*tmp;

	tmp = new_token(src);
	if (!tmp)
		return ;
	add_token(token, tmp);
}
