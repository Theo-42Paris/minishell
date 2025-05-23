/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pars_token.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tzara <tzara@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/13 13:38:05 by kjolly            #+#    #+#             */
/*   Updated: 2025/05/23 21:59:20 by tzara            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	t_exp(char *cmd, int *i, t_data *data, char **tmp);

void	quote(char *cmd, int *i, t_data *data, char **tmp)
{
	char	c;
	int		single_quote;

	c = cmd[(*i)++];
	single_quote = (c == '\'');
	while (cmd[*i] && cmd[*i] != c)
	{
		if (cmd[*i] == '$' && !single_quote)
			t_exp(cmd, i, data, tmp);
		else
		{
			*tmp = append_char(*tmp, cmd[*i]);
			(*i)++;
		}
	}
	if (cmd[*i] == c)
		(*i)++;
}

void	t_exp(char *cmd, int *i, t_data *data, char **tmp)
{
	int	start;

	start = ++(*i);
	if (cmd[start] == '\'' || cmd[start] == '"')
		return ;
	if (cmd[start] == '?')
	{
		handle_exit_code(i, data, tmp);
		return ;
	}
	handle_variable(cmd, i, data, tmp);
}

void	win_line(t_data *data, char **tmp, int *h_d)
{
	token_next(data, *tmp);
	free(*tmp);
	*tmp = NULL;
	h_d = 0;
}

int	handle_operator(char *cmd, int *i, t_data *data, char **tmp)
{
	int		h_d;
	char	*op;

	h_d = 0;
	if (!ft_strncmp(&cmd[*i], "<<", 2) || !ft_strncmp(&cmd[*i], ">>", 2))
	{
		token_next(data, *tmp);
		free(*tmp);
		*tmp = NULL;
		if (!ft_strncmp(&cmd[*i], "<<", 2))
			h_d = 1;
		op = ft_substr(cmd, *i, 2);
		compl_token_list(&data->token, op);
		free(op);
		*i += 2;
	}
	else if (cmd[*i] == '|' || cmd[*i] == '<' || cmd[*i] == '>')
	{
		win_line(data, tmp, &h_d);
		op = ft_substr(cmd, *i, 1);
		compl_token_list(&data->token, op);
		free(op);
		(*i)++;
	}
	return (h_d);
}

void	tokenizer(t_data *data, char *cmd)
{
	int		i;
	char	*tmp;
	int		in_here_doc;

	i = 0;
	tmp = NULL;
	in_here_doc = 0;
	while (cmd[i])
	{
		if (cmd[i] == '\'' || cmd[i] == '"')
			quote(cmd, &i, data, &tmp);
		else if (!in_here_doc && cmd[i] == '$')
			t_exp(cmd, &i, data, &tmp);
		else if (cmd[i] == ' ' || cmd[i] == '\t')
			space_token(data, &tmp, &i);
		else if (is_operator(&cmd[i]))
			in_here_doc = handle_operator(cmd, &i, data, &tmp);
		else
			normal_token(&tmp, cmd, &i, &in_here_doc);
	}
	if (tmp)
	{
		compl_token_list(&data->token, tmp);
		free(tmp);
	}
}

// void	tokenizer(t_data *data, char *cmd)
// {
// 	int		i = 0;
// 	char	*tmp = NULL;
// 	int		here_doc = 0;

// 	if (!cmd)
// 		return ;
// 	while (cmd[i])
// 	{
// 		if (cmd[i] == '\'' || cmd[i] == '"')
// 			quote(cmd, &i, data, &tmp);
// 		else if (cmd[i] == '$' && !here_doc)
// 			t_exp(cmd, &i, data, &tmp);
// 		else if (cmd[i] == ' ' || cmd[i] == '\t')
// 		{
// 			token_next(data, tmp);
// 			if (data->token->token == DELIMITER)
// 				here_doc = 1;
// 			else
// 				here_doc = 0;
// 			tmp = NULL;
// 			i++;
// 		}
// 		else
// 		{
// 			tmp = append_char(tmp, cmd[i]);
// 			i++;
// 		}
// 	}
// 	if (tmp)
// 		compl_token_list(&data->token, tmp);
// }
