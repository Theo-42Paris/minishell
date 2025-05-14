/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kjolly <kjolly@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/09 17:00:42 by kjolly            #+#    #+#             */
/*   Updated: 2025/05/14 14:44:21 by kjolly           ###   ########.fr       */
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

void	print_heredoc(char *line, int *fd)
{
	ft_putstr_fd(line, *fd);
	free(line);
}

void	make_here_doc(char *limiteur, int *fd, t_env **env, t_data *data)
{
	char	*line;
	char	*good_line;

	while (1)
	{
		line = readline("> ");
		if (!line || ft_strcmp(line, limiteur) == 0)
		{
			free(line);
			break ;
		}
		if (exp_in_hd(line))
		{
			good_line = expandables(line, env, data);
			free(line);
			if (!good_line)
				return ;
			ft_putstr_fd(good_line, *fd);
		}
		else
			print_heredoc(line, fd);
		ft_putstr_fd("\n", *fd);
	}
}

void	handle_here_doc(t_cmd *cmd, t_env **env, t_data *data)
{
	t_cmd	*tmp;
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
				make_here_doc(tmp_r->arg, &pipe_fd[1], env, data);
				close(pipe_fd[1]);
				tmp_r->fd_here_doc = pipe_fd[0];
			}
			tmp_r = tmp_r->next;
		}
		tmp = tmp->next;
	}
}
