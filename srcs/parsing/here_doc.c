/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tzara <tzara@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/09 17:00:42 by kjolly            #+#    #+#             */
/*   Updated: 2025/05/27 20:32:38 by tzara            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	close_fd_red(t_cmd *cmd)
{
	t_redir	*tmp_r;

	while (cmd)
	{
		tmp_r = cmd->redir;
		while (tmp_r)
		{
			if (tmp_r->token == DELIMITER && tmp_r->fd_here_doc >= 0)
				close(tmp_r->fd_here_doc);
			tmp_r = tmp_r->next;
		}
		cmd = cmd->next;
	}
}

void	read_here_doc(t_data *data, char *limiteur, int *fd)
{
	char	*line;
	char	*good_line;

	while (1)
	{
		if (bad_line(&line, limiteur))
			break ;
		if (exp_in_hd(line))
		{
			good_line = expandables(line, data);
			free(line);
			if (!good_line)
				return ;
			ft_putstr_fd(good_line, *fd);
			free(good_line);
		}
		else
		{
			ft_putstr_fd(line, *fd);
			free(line);
		}
		ft_putstr_fd("\n", *fd);
	}
}

void	child_h_d(t_data *data, int *pipe_fd, char *limiteur)
{
	g_ctrl_c_signal = data;
	g_ctrl_c_signal->fd_hd = pipe_fd[1];
	close_fd_red(data->cmd);
	signal(SIGINT, sig_c_child_hd);
	signal(SIGQUIT, SIG_IGN);
	close(pipe_fd[0]);
	read_here_doc(data, limiteur, &pipe_fd[1]);
	close(pipe_fd[1]);
	free_all(data);
	free_env(&data->env);
	free(data);
	rl_clear_history();
	exit(0);
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
	if (pid == -1 || pid == 0)
	{
		if (!other_pid(data, pid, pipe_fd, limiteur))
			return ;
	}
	else
	{
		signal(SIGINT, SIG_IGN);
		close(pipe_fd[1]);
		waitpid(pid, &status, 0);
		signal(SIGINT, handle_sig_c);
		if (signal_h_d(data, &pipe_fd[0], fd, status))
			return ;
		*fd = pipe_fd[0];
	}
}

void	handle_here_doc(t_cmd *cmd, t_data *data)
{
	t_redir	*tmp_r;

	while (cmd)
	{
		tmp_r = cmd->redir;
		while (tmp_r)
		{
			if (tmp_r->token == DELIMITER)
			{
				make_here_doc(tmp_r->arg, &tmp_r->fd_here_doc, data);
				if (data->signal == 1)
					return ;
			}
			tmp_r = tmp_r->next;
		}
		cmd = cmd->next;
	}
}
