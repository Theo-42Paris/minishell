/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pars_token.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kjolly <kjolly@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/13 13:38:05 by kjolly            #+#    #+#             */
/*   Updated: 2025/03/31 16:58:09 by kjolly           ###   ########.fr       */
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
	tmp->token = check_type(dup);
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

void tokenizer(t_token **token, char *str)
{
    int i;
    char *dup;
    int start;
    char buffer[1024];
    int buf_index = 0;
    char quote;

    i = 0;
    while (str[i] == ' ' || str[i] == '\t')
        i++;    
    while (str[i])
    {
        buf_index = 0;
        start = i;
        while (str[i] && str[i] != ' ' && str[i] != '\t')
        {
            if (str[i] == '\'' || str[i] == '"')
            {
                quote = str[i++];
                while (str[i] && str[i] != quote)
				{
					if (buf_index < 1023)
                    	buffer[buf_index++] = str[i++];
				}
                if (str[i] == quote)
                    i++;
            }
            else
			{
				if (buf_index < 1023)
                	buffer[buf_index++] = str[i++];
			}
        }
        if (buf_index > 0)
		{
            buffer[buf_index] = '\0';
            dup = ft_strdup(buffer);
            if (!dup)
                return;
            compl_token_list(token, dup);
        }
        while (str[i] && (str[i] == ' ' || str[i] == '\t'))
            i++;
    }
}

// void    tokenizer(t_token **token, char *str)
// {
//     int i;
//     char *dup;
//     char quote;
//     int start;
    
//     i = 0;
//     while (str[i] == ' ' || str[i] == '\t')
//         i++;    
//     while (str[i])
//     {
//         start = i;
//         if (str[i] == '\'' || str[i] == '"')
//         {
//             quote = str[i++];
//             start = i;
//             while (str[i] && quote != str[i])
//                 i++;
//             dup = ft_strndup(str + start, i - start);
//             if (!dup)
//                 return;
//             if (str[i] != '\0') // Vérifier si on n'est pas à la fin de la chaîne
//                 i++;
//         }
//         else
//         {
//             while (str[i] && (str[i] != ' ' && str[i] != '\t' && str[i] != '\'' && str[i] != '"'))
//                 i++;            
//             dup = ft_strndup(str + start, i - start);
//             if (!dup)
//                 return;
//         }
//         compl_token_list(token, dup);
//         // Avancer seulement si on a des espaces ou des tabulations
//         while (str[i] && (str[i] == ' ' || str[i] == '\t'))
//             i++;
//     }
// }

// void    tokenizer(t_token **token, char *str)
// {
// 	int     i;
// 	int		start;
// 	int     exp;
// 	char    quote;
// 	char	*dup;

// 	i = 0;
// 	while (str[i] && (str[i] == ' ' || str[i] == '\t'))
// 		i++;
// 	while(str[i])
// 	{
// 		start = i;
// 		if (str[i] == '\'')
// 		{
// 			if (str[i + 1] == '$')
// 			{
// 				quote = str[i++];
// 				exp = 1;
// 			}
// 			else
// 				quote = str[i++];
// 			start = i;
// 			while (str[i] && quote != str[i])
// 				i++;
// 			if (str[i] == quote)
// 				i++;
// 		}
// 		else if (str[i] == '"')
// 		{
// 			quote = str[i];
// 			start = i;
// 			while (str[i] && quote != str[i])
// 				i++;
// 			if (str[i] == quote)
// 			i++;
// 		}
// 		else
// 		{
// 			start = i;
// 			while (str[i] && (str[i] != ' ' && str[i] != '\t'))
//                 i++;
// 		}
// 		if ( i > start)
// 		{
// 			dup = ft_strndup(str + start, i - start);
// 			if (!dup)
// 				return ;
// 			compl_token_list(token, dup);
// 		}
//         while (str[i] && (str[i] == ' ' || str[i] == '\t'))
//             i++;
// 	}
// }

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

// void	tokenizer(t_token **token, char *str)
// {
// 	int		i;
// 	char	*dup;
// 	char	quote;
// 	int		start;

// 	i = 0;
// 	while (str[i] == ' ' || str[i] == '\t')
// 		i++;
// 	while (str[i])
// 	{
// 		start = i;
// 		if (str[i] == '\'' || str[i] == '"')
// 		{
// 			quote = str[i++];
// 			start = i;
// 			while (str[i] && quote != str[i])
// 				i++;
// 			dup = ft_strndup(str + start, i - start);
// 			if (!dup)
// 				return ;
// 			i++;
// 		}
// 		else
// 		{
// 			while (str[i] && (str[i] != ' ' && str[i] != '\'' && str[i] != '"'))
// 			{
// 				i++;
// 			}
// 			dup = ft_strndup(str + start, i - start);
// 			if (!dup)
// 				return ;
// 		}
// 		compl_token_list(token, dup);
// 		i++;
// 	}
// }

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
