/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tzara <tzara@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/20 15:24:45 by tzara             #+#    #+#             */
/*   Updated: 2025/05/20 15:28:45 by tzara            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	exp_in_hd(char *line)
{
	int	i;

	i = 0;
	while (line[i])
	{
		if (line[i] == '$' && line[i + 1] && (line[i + 1] == '?'
				|| ft_isalpha(line[i + 1])))
			return (1);
		i++;
	}
	return (0);
}

int	bad_line(char **line, char *limiteur)
{
	*line = readline("> ");
	if (!*line)
	{
		ft_printf("minishell: warning: here-document delimited");
		ft_printf(" by end-of-file (wanted `%s')\n", limiteur);
		free(*line);
		return (1);
	}
	if (ft_strcmp(*line, limiteur) == 0)
	{
		free(*line);
		return (1);
	}
	return (0);
}
