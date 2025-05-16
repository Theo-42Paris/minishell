/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kjolly <kjolly@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/09 17:00:42 by kjolly            #+#    #+#             */
/*   Updated: 2025/05/16 16:00:34 by kjolly           ###   ########.fr       */
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

void	read_here_doc(t_data *data, char *limiteur, int *fd)
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
			good_line = expandables(line, &data->env, data);
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

void	make_here_doc(char *limiteur, int *fd, t_data *data)
{
	int		pipe_fd[2];
	pid_t	pid;
	int		status;

	if (pipe(pipe_fd) == -1)
	{
		perror("pipe");
		return ;
	}
	pid = fork();
	if (pid == -1)
	{
		close(pipe_fd[0]);
		close(pipe_fd[1]);
		perror("fork fail");
	}
	else if (pid == 0)
	{
		signal(SIGINT, SIG_DFL);
		signal(SIGQUIT, SIG_IGN);
		close(pipe_fd[0]);
		read_here_doc(data, limiteur, &pipe_fd[1]);
		close(pipe_fd[1]);
		exit(0);
	}
	else
	{
		signal(SIGINT, SIG_IGN);
		close(pipe_fd[1]);
		waitpid(pid, &status, 0);
		signal(SIGINT, handle_sig_c);
		if (WIFSIGNALED(status) && WTERMSIG(status) == SIGINT)
		{
			close(pipe_fd[0]);
			*fd = -1;
			data->exit_code = 130;
			write(1, "\n", 1);
			return ;
		}
		*fd = pipe_fd[0];
	}
}

void	handle_here_doc(t_cmd *cmd, t_data *data)
{
	t_cmd	*tmp = cmd;
	t_redir	*tmp_r;

	while (tmp)
	{
		tmp_r = tmp->redir;
		while (tmp_r)
		{
			if (tmp_r->token == DELIMITER)
				make_here_doc(tmp_r->arg, &tmp_r->fd_here_doc, data);
			tmp_r = tmp_r->next;
		}
		tmp = tmp->next;
	}
}
