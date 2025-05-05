/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pars_token.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kjolly <kjolly@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/13 13:38:05 by kjolly            #+#    #+#             */
/*   Updated: 2025/05/05 13:31:05 by kjolly           ###   ########.fr       */
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
// // void	quote(char *cmd, int *i, t_data *data, char *tmp)
// // {
// // 	char	c;
// // 	int		sq;

// // 	c = cmd[*i++];
// // 	if (c == '\'')
// // 		sq = 1;
// // 	while (cmd[*i] && cmd[*i] != c)
// // 	{
// // 		if (cmd[*i] == '$' && !sq)
// // 			exp(cmd, i, data, tmp);
// // 		*tmp = append_char(*tmp, cmd[*i]);
// // 		*i++;
// // 	}
// // }

// void	quote(char *cmd, int *i, t_data *data, char **tmp)
// {
// 	char	c = cmd[(*i)++];
// 	int		sq = (c == '\'');

// 	while (cmd[*i] && cmd[*i] != c)
// 	{
// 		if (cmd[*i] == '$' && !sq)
// 			t_exp(cmd, i, data, tmp);
// 		else
// 		{
// 			*tmp = append_char(*tmp, cmd[*i]);
// 			(*i)++;
// 		}
// 	}
// 	if (cmd[*i] == c)
// 		(*i)++;
// }

// char	*get_exp(char *tp, t_env *env)
// {
// 	t_env	*tmp_e;
// 	(void)tp;
// 	tmp_e = env;
// 	while (tmp_e)
// 	{
// 		tmp_e = tmp_e->next;
// 	}
// 	return (NULL);
// }

// void	t_exp(char *cmd, int *i, t_data *data, char **tmp)
// {
// 	int		j;
// 	int		k;
// 	char	*tp;
// 	char	*var;
// 	char	*joined;
	
// 	printf("la\n");
// 	j = *i;
// 	while (cmd[j] && (ft_isalpha(cmd[j]) || cmd[j] == '_'))
// 		j++;
// 	tp = malloc(sizeof(char) * (j - *i + 1));
// 	if (!tp)
// 		return ;
// 	k = 0;
// 	while (cmd[*i] && (ft_isalpha(cmd[*i]) || cmd[*i] == '_'))
// 	{
// 		tp[k++] = cmd[*i++];
// 	}
// 	tp[k] = '\0';
// 	var = get_exp(tp, data->env);
// 	free(tp);
// 	if (var)
// 	{
// 		if (*tmp)
// 			joined = ft_strjoin(*tmp, var);
// 		else
// 			joined = ft_strjoin("", var);
// 		free(*tmp);
// 		*tmp = joined;
// 	}
// }

// void	token_next(t_data *data, char *tmp)
// {
// 	if (*tmp)
// 	{
// 		compl_token_list(&data->token, tmp);
// 		free(tmp);
// 		tmp = NULL;
// 	}
// }

// void	tokenizer(t_data *data, char *cmd)
// {
// 	int		i;
// 	char	*tmp;

// 	if (!cmd)
// 		return ;
// 	i = 0;
// 	tmp = NULL;
// 	while (cmd[i])
// 	{
// 		if (cmd[i] == '\'' || cmd[i] == '"')
// 			quote(cmd, &i, data, &tmp);
// 		else if (cmd[i] == '$')
// 			t_exp(cmd, &i, data, &tmp);
// 		else if (cmd[i] == ' ' || cmd[i] == '\t')
// 			token_next(data, tmp);
// 		else
// 			tmp = append_char(tmp, cmd[i]);
// 		i++;
// 	}
// 	if (tmp)
// 	compl_token_list(&data->token, tmp);
// }

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
	int		start = ++(*i);
	int		end = start;

	while (cmd[end] && (ft_isalnum(cmd[end]) || cmd[end] == '_'))
		end++;

	if (start == end)
		return ;
	char *var_name = ft_substr(cmd, start, end - start);
	*i = end;
	if (!var_name)
		return ;
	char *value = get_exp(var_name, data->env);
	free(var_name);
	if (value)
	{
		char *joined = *tmp ? ft_strjoin(*tmp, value) : ft_strdup(value);
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

	if (!cmd)
		return ;
	while (cmd[i])
	{
		if (cmd[i] == '\'' || cmd[i] == '"')
			quote(cmd, &i, data, &tmp);
		else if (cmd[i] == '$')
			t_exp(cmd, &i, data, &tmp);
		else if (cmd[i] == ' ' || cmd[i] == '\t')
		{
			token_next(data, tmp);
			tmp = NULL;
			i++;
		}
		else
		{
			tmp = append_char(tmp, cmd[i]);
			i++;
		}
	}
	if (tmp)
		compl_token_list(&data->token, tmp);
}


// void	win_2_line(t_token **token, char **current_word, int *exp)
// {
// 	compl_token_list(token, *current_word, *exp);
// 	*current_word = NULL;
// }

// void	init_var(int *in_q, char *quote_c, char **cur_wrd, int *exp)
// {
// 	*in_q = 0;
// 	*quote_c = 0;
// 	*cur_wrd = NULL;
// 	*exp = -1;
// }

// void	first_if_token(char *c, int *in_quote, int *exp, char *quote_char)
// {
// 	if (*in_quote)
// 		*in_quote = 0;
// 	else
// 	{
// 		*in_quote = 1;
// 		*quote_char = *c;
// 		if (*c == '\'' && *exp == -1)
// 			*exp = 0;
// 		else if (*exp == -1 || *exp == 0)
// 			*exp = 1;
// 	}
// }

// void	tokenizer(t_token **tokens, char *cmd)
// {
// 	int		in_quotes;
// 	char	quote_char;
// 	char	*current_word;
// 	char	c;
// 	int		exp;

// 	init_var(&in_quotes, &quote_char, &current_word, &exp);
// 	while (*cmd)
// 	{
// 		c = *cmd;
// 		if ((c == '"' || c == '\'') && (!in_quotes || quote_char == c))
// 			first_if_token(&c, &in_quotes, &exp, &quote_char);
// 		else if (isspace(c))
// 		{
// 			if (in_quotes)
// 				current_word = append_char(current_word, c);
// 			else if (current_word)
// 				win_2_line(tokens, &current_word, &exp);
// 		}
// 		else
// 			current_word = append_char(current_word, c);
// 		cmd++;
// 	}
// 	if (current_word)
// 		compl_token_list(tokens, current_word, exp);
// }
