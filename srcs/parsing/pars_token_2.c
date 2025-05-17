/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pars_token_2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kjolly <kjolly@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/11 11:57:23 by kjolly            #+#    #+#             */
/*   Updated: 2025/05/17 10:37:12 by kjolly           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	ft_strcpy(char *dst, char *src)
{
	int	i;

	i = 0;
	while(src[i])
	{
		dst[i] = src[i];
		i++;
	}
	dst[i] = '\0';
}

int	count_line(char *line)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (line[i])
	{
		if ((line[i] == '>' && line[i + 1] == '>') || (line[i] == '<' && line[i
				+ 1] == '<'))
		{
			count += 3;
			i++;
		}
		else if (line[i] == '>' || line[i] == '<' || line[i] == '|')
			count += 2;
		count++;
		i++;
	}
	return (count);
}

char	*clean_spaces(char *str)
{
	int		i = 0;
	int		j = 0;
	int		in_quote = 0;
	char	quote_char = 0;
	char	*new = malloc(sizeof(char) * (strlen(str) + 1));
	if (!new)
		return (NULL);
	while (str[i])
	{
		if ((str[i] == '\'' || str[i] == '"') && !in_quote)
		{
			in_quote = 1;
			quote_char = str[i];
		}
		else if (str[i] == quote_char && in_quote)
		{
			in_quote = 0;
			quote_char = 0;
		}
		if (!in_quote && (str[i] == ' ' || str[i] == '\t'))
		{
			while (str[i + 1] == ' ' || str[i + 1] == '\t')
				i++;
			new[j++] = ' ';
		}
		else
			new[j++] = str[i];
		i++;
	}
	new[j] = '\0';
	return (new);
}


void	pre_token2(char **line, int *i, char **dest, int *j)
{
	if (((*line)[*i] == '>' && (*line)[*i + 1] == '>') || ((*line)[*i] == '<'
			&& (*line)[*i + 1] == '<'))
	{
		(*dest)[(*j)++] = ' ';
		(*dest)[(*j)++] = (*line)[(*i)++];
		(*dest)[(*j)++] = (*line)[*i];
		(*dest)[(*j)++] = ' ';
	}
	else if ((*line)[*i] == '>' || (*line)[*i] == '<' || (*line)[*i] == '|')
	{
		(*dest)[(*j)++] = ' ';
		(*dest)[(*j)++] = (*line)[*i];
		(*dest)[(*j)++] = ' ';
	}
	else
		(*dest)[(*j)++] = (*line)[*i];
}

char	*pre_token(char *line)
{
	int		i;
	int		j;
	int		size;
	char	*dest;
	char	*clean;

	i = 0;
	j = 0;
	size = count_line(line);
	dest = malloc(sizeof(char) * (size + 1));
	if (!dest)
		return (NULL);
	while (line[i])
	{
		pre_token2(&line, &i, &dest, &j);
		i++;
	}
	dest[j] = '\0';
	clean = clean_spaces(dest);
	free(dest);
	return (clean);
}
