/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pars_token.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tzara <tzara@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/13 13:38:05 by kjolly            #+#    #+#             */
/*   Updated: 2025/05/20 12:26:54 by tzara            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	t_exp(char *cmd, int *i, t_data *data, char **tmp);

char	*append_char(char *current_word, char c)
{
	int		len;
	char	*new_word;

	if (current_word != NULL)
		len = ft_strlen(current_word);
	else
		len = 0;
	new_word = malloc(len + 2);
	if (!new_word)
		return (NULL);
	if (current_word)
	{
		ft_strcpy(new_word, current_word);
		free(current_word);
	}
	else
		new_word[0] = '\0';
	new_word[len] = c;
	new_word[len + 1] = '\0';
	return (new_word);
}

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

char	*get_exp(char *name, t_env *env)
{
	t_env	*tmp;

	tmp = env;
	while (tmp)
	{
		if (ft_strncmp(tmp->env, name, ft_strlen(name)) == 0
			&& tmp->env[ft_strlen(name)] == '=')
		{
			return (ft_strdup(tmp->env + ft_strlen(name) + 1));
		}
		tmp = tmp->next;
	}
	return (NULL);
}

void	t_exp(char *cmd, int *i, t_data *data, char **tmp)
{
	int		start;
	int		end;
	char	*var_name;
	char	*joined;
	char	*value;

	start = ++(*i);
	if (cmd[start] == '?')
	{
		value = ft_itoa(data->exit_code);
		(*i)++;
		if (*tmp)
			joined = ft_strjoin(*tmp, value);
		else
			joined = ft_strdup(value);
		free(value);
		free(*tmp);
		*tmp = joined;
		return ;
	}
	end = start;
	while (cmd[end] && (ft_isalnum(cmd[end]) || cmd[end] == '_'))
		end++;
	if (start == end)
	{
		*tmp = append_char(*tmp, '$');
		return ;
	}
	var_name = ft_substr(cmd, start, end - start);
	*i = end;
	if (!var_name)
	{
		if (*tmp)
			free(*tmp);
		return ;
	}
	value = get_exp(var_name, data->env);
	free(var_name);
	if (value)
	{
		if (*tmp)
			joined = ft_strjoin(*tmp, value);
		else
			joined = ft_strdup(value);
		if (!joined)
		{
			free(value);
			return ;
		}
		free(value);
		free(*tmp);
		*tmp = joined;
	}
}

void	token_next(t_data *data, char *tmp)
{
	if (tmp && *tmp)
	{
		compl_token_list(&data->token, tmp);
		free(tmp);
	}
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

int	is_operator(char *s)
{
	if (!s)
		return (0);
	return (!ft_strncmp(s, "<<", 2) || !ft_strncmp(s, ">>", 2) || !ft_strncmp(s,
			"<", 1) || !ft_strncmp(s, ">", 1) || !ft_strncmp(s, "|", 1));
}

void	space_token(t_data *data, char **tmp, int *i)
{
	token_next(data, *tmp);
	*tmp = NULL;
	(*i)++;
}

void	normal_token(char **tmp, char *cmd, int *i, int *in_here_doc)
{
	*tmp = append_char(*tmp, cmd[*i]);
	(*i)++;
	if (*in_here_doc && (cmd[*i] == ' ' || cmd[*i] == '\t' || !cmd[*i]))
		*in_here_doc = 0;
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
