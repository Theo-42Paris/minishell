/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pars_token.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kjolly <kjolly@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/13 13:38:05 by kjolly            #+#    #+#             */
/*   Updated: 2025/04/11 12:02:49 by kjolly           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

// int	open_quote(char *str)
// {
// 	int	i;
// 	int	single_quote;
// 	int	double_quote;

// 	i = 0;
// 	single_quote = 0;
// 	double_quote = 0;
// 	while (str[i])
// 	{
// 		if (str[i] == '\'' && double_quote == 0)
// 			single_quote = !single_quote;
// 		else if (str[i] == '"' && single_quote == 0)
// 			double_quote = !double_quote;
// 		i++;
// 	}
// 	return (single_quote || double_quote);
// }

char	*append_char(char *word, char c)
{
	int		len;
	char	*new_word;

	len = (word ? strlen(word) : 0);
	new_word = malloc(len + 2);
	if (!new_word)
	{
		perror("malloc");
		exit(EXIT_FAILURE);
	}
	if (word)
	{
		strcpy(new_word, word);
		free(word);
	}
	else
	{
		new_word[0] = '\0';
	}
	new_word[len] = c;
	new_word[len + 1] = '\0';
	return (new_word);
}

void	first_if(char *c, int *in_quote, int *exp, char *quote_char)
{
	if (*in_quote)
		*in_quote = 0;
	else
	{
		if (*c == '\'')
			*exp = 0;
		else
			*exp = 1;
		*in_quote = 1;
		*quote_char = *c;
	}
}

void	win_2_line(t_token **token, char **current_word, int *exp)
{
	compl_token_list(token, *current_word, *exp);
	*current_word = NULL;
}

void	init_var(int *in_q, char *quote_c, char **cur_wrd, int *exp)
{
	*in_q = 0;
	*quote_c = 0;
	*cur_wrd = NULL;
	*exp = 1;
}

// todo | il vas falloir gerer un in_sq et un in_dq
void	tokenizer(t_token **tokens, char *cmd)
{
	int		in_quotes;
	char	quote_char;
	char	*current_word;
	char	c;
	int		exp;

	init_var(&in_quotes, &quote_char, &current_word, &exp);
	while (*cmd)
	{
		c = *cmd;
		if ((c == '"' || c == '\'') && (!in_quotes || quote_char == c))
			first_if(&c, &in_quotes, &exp, &quote_char);
		else if (isspace(c))
		{
			if (in_quotes)
				current_word = append_char(current_word, c);
			else if (current_word)
				win_2_line(tokens, &current_word, &exp);
		}
		else
			current_word = append_char(current_word, c);
		cmd++;
	}
	if (current_word)
		compl_token_list(tokens, current_word, exp);
}
