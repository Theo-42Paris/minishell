/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pars_token.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kjolly <kjolly@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/13 13:38:05 by kjolly            #+#    #+#             */
/*   Updated: 2025/05/13 17:32:24 by kjolly           ###   ########.fr       */
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
	char	c = cmd[(*i)++];
	int		single_quote = (c == '\'');

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

char *get_exp(char *name, t_env *env)
{
    while (env)
    {
        if (ft_strncmp(env->env, name, ft_strlen(name)) == 0 && 
            env->env[ft_strlen(name)] == '=')
        {
            return ft_strdup(env->env + ft_strlen(name) + 1);
        }
        env = env->next;
    }
    return NULL;
}

void	t_exp(char *cmd, int *i, t_data *data, char **tmp)
{
	int		start;
	int		end;
	char	*var_name;
	char	*joined;
	char	*value;

	start = ++(*i);
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


void	tokenizer(t_data *data, char *cmd)
{
	int		i = 0;
	char	*tmp = NULL;
	int		in_here_doc = 0;

	if (!cmd)
		return ;

	while (cmd[i])
	{
		if (cmd[i] == '\'' || cmd[i] == '"')
			quote(cmd, &i, data, &tmp);
		else if (!in_here_doc && cmd[i] == '$')
			t_exp(cmd, &i, data, &tmp);
		else if (cmd[i] == ' ' || cmd[i] == '\t')
		{
			token_next(data, tmp);
			tmp = NULL;
			i++;
		}
		else if (!ft_strncmp(&cmd[i], "<<", 2) || !ft_strncmp(&cmd[i], ">>", 2))
		{
			token_next(data, tmp);
			tmp = NULL;
			if (!ft_strncmp(&cmd[i], "<<", 2))
				in_here_doc = 1;
			compl_token_list(&data->token, ft_substr(&cmd[i], 0, 2));
			i += 2;
		}
		else if (cmd[i] == '|' || cmd[i] == '<' || cmd[i] == '>')
		{
			token_next(data, tmp);
			tmp = NULL;
			in_here_doc = 0;
			compl_token_list(&data->token, ft_substr(&cmd[i], 0, 1));
			i++;
		}
		else
		{
			tmp = append_char(tmp, cmd[i]);
			i++;
			if (in_here_doc && (cmd[i] == ' ' || cmd[i] == '\t' || !cmd[i]))
				in_here_doc = 0;
		}
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
