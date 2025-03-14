/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kjolly <kjolly@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/13 13:38:05 by kjolly            #+#    #+#             */
/*   Updated: 2025/03/15 16:23:45 by kjolly           ###   ########.fr       */
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

char	*ft_strndup(char *src, int a)
{
	char	*dst;
	int		i;

	i = 0;
	dst = (char *)malloc(sizeof(char) * (a + 1));
	if (!dst)
		return (NULL);
	while (i < a)
	{
		dst[i] = src[i];
		i++;
	}
	dst[i] = '\0';
	return (dst);
}

int check_type(char *dup)
{
	if (!strncmp(dup, "|", ft_strlen(dup)))
		return (PIPE);
	else if (!strncmp(dup, "<", ft_strlen(dup)))
		return (REDIR_IN);
	else if (!strncmp(dup, ">", ft_strlen(dup)))
		return (REDIR_OUT);
	else if (!strncmp(dup, "<<", ft_strlen(dup)))
		return (DELIMITER);
	else if (!strncmp(dup, ">>", ft_strlen(dup)))
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

t_token	*new_token(char *dup)
{
	t_token	*tmp;

	tmp = malloc(sizeof(t_token));
	if (!tmp)
		return (NULL);
	tmp->data = dup;
	tmp->type = check_type(dup);
	tmp->cmd = -1;
	tmp->next = NULL;
	return (tmp);
}

void	compl_token_list(t_token **token, char *dup)
{
	t_token	*tmp;

	tmp = new_token(dup);
	if (!tmp)
		return ;
	add_token(token, tmp);
}

void	tokenizer(t_token **token, char *str)
{
	int		i;
	char	*dup;
	char	quote;
	int		start;

	i = 0;
	while (str[i] == ' ' || str[i] == '\t')
		i++;
	while (str[i])
	{
		start = i;
		if (str[i] == '\'' || str[i] == '"')
		{
			quote = str[i++];
			start = i;
			while (str[i] && quote != str[i])
				i++;
			dup = ft_strndup(str + start, i - start);
			if (!dup)
				return ;
			i++;
		}
		else
		{
			while (str[i] && str[i] != ' ' && str[i] != '\'' && str[i] != '"')
				i++;
			dup = ft_strndup(str + start, i - start);
			if (!dup)
				return ;
		}
		// printf("%s\n", dup);
		// printf("----------------\n");
		compl_token_list(token, dup);
		i++;
	}
}

// void	parsing(t_token *token, char *str)
// {
// 	if (open_quote(str))
// 	{
// 		ft_ptintf("Error : open quote\n");
// 		return ;
// 	}
// 	tokenizer(token, str);
//}

// int	main(void)
// {
// 	char	*test1;

// 	test1 = "echo 'Hello world' > file.txt | cat -e";
// 	tokenizer(test1);
// 	return (0);
// }
