/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tzara <tzara@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/09 17:00:42 by kjolly            #+#    #+#             */
/*   Updated: 2025/05/20 12:33:46 by tzara            ###   ########.fr       */
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

// void	print_heredoc(char *line, int *fd)
// {
// 	ft_putstr_fd(line, *fd);
// 	free(line);
// }

int	bad_line(char **line, char *limiteur)
{
	*line = readline("> ");
	if (!*line)
	{
		ft_printf("minishell: warning: here-document delimited by end-of-file (wanted `%s')\n",
			limiteur);
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
