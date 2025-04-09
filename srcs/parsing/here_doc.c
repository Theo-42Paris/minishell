/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kjolly <kjolly@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/09 17:00:42 by kjolly            #+#    #+#             */
/*   Updated: 2025/04/09 18:39:20 by kjolly           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	make_here_doc(char *limiteur, int *fd)
{
	char	*line;

	while (1)
	{
		line = readline("> ");
		if (!line || ft_strcmp(line, limiteur) == 0)
		{
			free(line);
			break ;
		}
		ft_putstr_fd(line, *fd);
		free(line);
	}
}

void handle_here_doc(t_cmd *cmd)
{
	t_cmd 	*tmp;
	t_redir	*tmp_r;
	int		pipe_fd[2];

	tmp = cmd;
	while (tmp)
	{
		tmp_r = tmp->redir;
		while (tmp_r)
		{
			if (tmp_r->token == DELIMITER)
			{
				if (pipe(pipe_fd) == -1)
					return (perror("pipe"));
				make_here_doc(tmp_r->arg, &pipe_fd[1]);
				close(pipe_fd[1]);
				tmp_r->fd_here_doc = pipe_fd[0];
			}
			tmp_r = tmp_r->next;
		}
		tmp = tmp->next;
	}
}
