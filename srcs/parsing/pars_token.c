/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pars_token.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kjolly <kjolly@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/13 13:38:05 by kjolly            #+#    #+#             */
/*   Updated: 2025/04/07 15:04:24 by kjolly           ###   ########.fr       */
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

int check_type(char *src)
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
	t_token *last;

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

t_token	*new_token(char *src, int exp, t_env **env)
{
	t_token	*tmp;
	char	*expand_word;

	tmp = malloc(sizeof(t_token));
	if (!tmp)
		return (NULL);
	printf("je suis la\n");
	if (exp == 1)
	{
		expand_word = handle_expand(src, env);
		if (!expand_word)
			return (NULL);
		tmp->data =expand_word;
	}
	else
		tmp->data = src;
	tmp->token = check_type(tmp->data);
	tmp->next = NULL;
	return (tmp);
}

void	compl_token_list(t_token **token, char *src, int exp, t_env **env)
{
	t_token	*tmp;

	tmp = new_token(src, exp, env);
	if (!tmp)
		return ;
	add_token(token, tmp);
}

int count_line(char *line)
{
	int i = 0;
	int count = 0;

	while (line[i])
	{
		if ((line[i] == '>' && line[i + 1] == '>') || (line[i] == '<' && line[i + 1] == '<'))
		{
			count += 3;
			i++;
		}
		else if (line[i] == '>' || line[i] == '<' || line[i] == '|')
			count += 2; 
		count++;
		i++;
	}
	return count;
}

char    *pre_token(char *line)
{
	int i = 0, j = 0;
	int size = count_line(line);
	char *dest = malloc(sizeof(char) * (size + 1));

	if (!dest)
		return NULL;
	while (line[i])
	{
		if ((line[i] == '>' && line[i + 1] == '>') || (line[i] == '<' && line[i + 1] == '<'))
		{
			dest[j++] = ' ';
			dest[j++] = line[i++];
			dest[j++] = line[i];
			dest[j++] = ' ';
		}
		else if (line[i] == '>' || line[i] == '<' || line[i] == '|')
		{
			dest[j++] = ' ';
			dest[j++] = line[i];
			dest[j++] = ' ';
		}
		else
			dest[j++] = line[i];
		i++;
	}
	dest[j] = '\0';
	return dest;
}

char *append_char(char *word, char c)
{
    int len = (word ? strlen(word) : 0);
    char *new_word = malloc(len + 2);
    
    if (!new_word) {
        perror("malloc");
        exit(EXIT_FAILURE);
    }

    if (word) 
    { 
        strcpy(new_word, word);
        free(word);
    } else 
    {
        new_word[0] = '\0';
    }

    new_word[len] = c;
    new_word[len + 1] = '\0';
    return new_word;
}

// Fonction pour ajouter un token à la liste chaînée
// void add_token(t_token **head, char *word)
// {
//     if (!word) return;  // Éviter d'ajouter un token vide
//     t_token *new_token = malloc(sizeof(t_token));
//     if (!new_token) {
//         perror("malloc");
//         exit(EXIT_FAILURE);
//     }
//     new_token->data = word;
//     new_token->next = NULL;
//     if (*head == NULL)
//     {
//         *head = new_token;
//     }
// 	else
// 	{
//         t_token *temp = *head;
//         while (temp->next)
//             temp = temp->next;
//         temp->next = new_token;
//     }
// }

void	tokenizer(t_token **tokens, t_env **env, char *cmd)
{
    int in_quotes = 0;
    char quote_char = 0;
    char *current_word = NULL;
    char c;
	int exp = 1;

    while (*cmd) 
    {
        c = *cmd;
        if ((c == '"' || c == '\'') && (!in_quotes || quote_char == c)) 
        {
            if (in_quotes) 
                in_quotes = 0;
            else
            {
				if (c == '\'')
					exp = 0;
				else
					exp = 1;
                in_quotes = 1;
                quote_char = c;
            }
        }
        else if (isspace(c)) 
		{
            if (in_quotes)
                current_word = append_char(current_word, c);
			else if (current_word)
			{
                compl_token_list(tokens, current_word, exp, env);
                current_word = NULL;
            }
        }
        else
            current_word = append_char(current_word, c);
        cmd++;
    }
    if (current_word)
        compl_token_list(tokens, current_word, exp, env);
}


// void    check_cmd_args(t_token **token)
// {
// 	int		count;
// 	t_token	*current;
// 	t_token *prev;

// 	current = *token;
// 	prev = NULL;
// 	count = 0;
// 	while (current)
// 	{
// 		if (((count == 0 && current->token == WORD) || (prev && (!strncmp(prev->data,
// 			"|", ft_strlen(prev->data)) && current->token == WORD))))
// 			current->cmd = 1;
// 		else
// 			current->cmd = 0;
// 		count++;
// 		prev = current;
// 		current = current->next;
// 	}
// }

