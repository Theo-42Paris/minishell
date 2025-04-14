/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pars_token_2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tzara <tzara@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/11 11:57:23 by kjolly            #+#    #+#             */
/*   Updated: 2025/04/14 13:07:39 by tzara            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

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
	return (dest);
}
