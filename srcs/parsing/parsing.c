/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kjolly <kjolly@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/13 13:38:05 by kjolly            #+#    #+#             */
/*   Updated: 2025/03/13 16:43:40 by kjolly           ###   ########.fr       */
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
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	dst = (char *)malloc(sizeof(char) * (a + 1));
	if (!dst)
		return (NULL);
	while(i < a)
	{
		dst[j++] = src[i++];
	}
	dst[j] = '\0';
	return (dst);
}


void	tokenizer(/*t_token *token, */char *str)
{
	int		i;
	char	*dup;
	char	quote;
	int 	start;

	i = 0;
	while(str[i] == ' ' || str[i] == '\t')
		i++;
	while(str[i])
	{
		start = i;
		if (str[i] == '\'' || str[i] == '"')
		{
			quote = str[i++];
			start = i;
			while(str[i] && quote != str[i])
				i++;
			dup = ft_strndup(str + start, i - start);
			i++;
		}
		else
		{ 
			while(str[i] && str[i] != ' ' && str[i] != '\'' && str[i] != '"' )
				i++;
			dup = ft_strndup(str + start, i - start);
		}
		printf("%s\n", dup);
		printf("----------------\n");
		free(dup);
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

int	main()
{
	char *test1 = "je suis kyllian";
	tokenizer(test1);
	return (0);
}
