/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kjolly <kjolly@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/20 15:24:45 by tzara             #+#    #+#             */
/*   Updated: 2025/05/22 18:05:31 by kjolly           ###   ########.fr       */
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

int	other_pid(t_data *data, pid_t pid, int *pipe_fd, char *limiteur)
{
	if (pid == -1)
	{
		close(pipe_fd[0]);
		close(pipe_fd[1]);
		perror("fork fail");
		return (0);
	}
	else if (pid == 0)
		child_h_d(data, pipe_fd, limiteur);
	return (1);
}

int	signal_h_d(t_data *data, int *pipe_fd, int *fd, int status)
{
	if (WIFEXITED(status) && WEXITSTATUS(status) == 130)
	{
		close(pipe_fd[0]);
		*fd = -1;
		data->exit_code = 130;
		data->signal = 1;
		return (1);
	}
	else
		return (0);
}
