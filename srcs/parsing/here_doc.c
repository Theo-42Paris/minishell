/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kjolly <kjolly@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/09 17:00:42 by kjolly            #+#    #+#             */
/*   Updated: 2025/05/21 19:04:28 by kjolly           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	close_fd_red(t_cmd *cmd)
{
	t_cmd	*tmp;
	t_redir	*tmp_r;

	tmp = cmd;
	while (tmp)
	{
		tmp_r = tmp->redir;
		while (tmp_r)
		{
			if (tmp_r->token == DELIMITER && tmp_r->fd_here_doc >= 0)
				close(tmp_r->fd_here_doc);
			tmp_r = tmp_r->next;
		}
		tmp = tmp->next;
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
			good_line = expandables(line, &data->env, data);
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
		return ;
	}
	else if (pid == 0)
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
	else
	{
		signal(SIGINT, SIG_IGN);
		close(pipe_fd[1]);
		waitpid(pid, &status, 0);
		signal(SIGINT, handle_sig_c);
		if (WIFEXITED(status) && WEXITSTATUS(status) == 130)
		{
			close(pipe_fd[0]);
			*fd = -1;
			data->exit_code = 130;
			data->signal = 1;
			return ;
		}
		*fd = pipe_fd[0];
	}
}

void	handle_here_doc(t_cmd *cmd, t_data *data)
{
	t_cmd	*tmp;
	t_redir	*tmp_r;

	tmp = cmd;
	while (tmp)
	{
		tmp_r = tmp->redir;
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
		tmp = tmp->next;
	}
}
