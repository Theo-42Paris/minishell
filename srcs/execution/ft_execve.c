/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_execve.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kjolly <kjolly@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/01 13:31:37 by kjolly            #+#    #+#             */
/*   Updated: 2025/05/19 13:30:29 by kjolly           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

char	*find_path_exec(t_env *env)
{
	t_env	*tmp;

	tmp = env;
	while (tmp)
	{
		if (ft_strncmp(tmp->env, "PATH=", 5) == 0)
			return (tmp->env + 5);
		tmp = tmp->next;
	}
	return (NULL);
}

char	*concat_path(char *path, char *cmd)
{
	char	*tmp;
	char	*full_path;

	tmp = ft_strjoin(path, "/");
	if (!tmp)
		return (NULL);
	full_path = ft_strjoin(tmp, cmd);
	free(tmp);
	return (full_path);
}

char	*get_path(char *cmd, t_env *env)
{
	int		i;
	char	*first_path;
	char	**new_path;
	char	*full_path;
	
	i = 0;
	if (!cmd || cmd[0] == '\0')
		return (NULL);
	if (ft_strchr(cmd, '/'))
		return (ft_strdup(cmd));
	first_path = find_path_exec(env);
	if (!first_path)
		return (NULL);
	new_path = ft_split(first_path, ':');
	if (!new_path)
		return (NULL);
	while (new_path[i])
	{
		full_path = concat_path(new_path[i], cmd);
		if (!full_path)
			return (free_str(new_path), NULL);
		if (access(full_path, F_OK | X_OK) == 0)
			return (free_str(new_path), full_path);
		free(full_path);
		i++;
	}
	free_str(new_path);
	return (NULL);
}

char	**env_for_exec(t_env *env)
{
	int		count;
	int		i;
	char	**prep_env;
	t_env	*tmp1;
	t_env	*tmp2;

	i = 0;
	count = 0;
	tmp1 = env;
	tmp2 = env;
	while (tmp1)
	{
		count++;
		tmp1 = tmp1->next;
	}
	prep_env = (char **)malloc(sizeof(char *) * (count + 1));
	if (!prep_env)
		return (NULL);
	while (tmp2)
	{
		prep_env[i] = ft_strdup(tmp2->env);
		if (!prep_env[i])
		{
			while (--i >= 0)
				free(prep_env[i]);
			free(prep_env);
			return (NULL);
		}
		i++;
		tmp2 = tmp2->next;
	}
	prep_env[i] = NULL;
	return (prep_env);
}

void	do_execve_bonus(t_exec *mini, t_cmd *tmp_cmd, char *path, t_data *data)
{
	char	**exec_env;

	exec_env = env_for_exec((*data).env);
	if (!exec_env)
	{
		free(mini->pidarray);
		free(path);
		free_all(data);
		ft_putstr_fd("malloc error: environment setup failed\n", 2);
		data->exit_code = 1;
		rl_clear_history();
		exit(1);
	}
	if (execve(path, tmp_cmd->args, exec_env) == -1)
	{
		free(mini->pidarray);
		free_str(exec_env);
		perror(tmp_cmd->args[0]);
		if (access(path, F_OK) == -1)
		{
			data->exit_code = 127;
			free(path);
			free_all(data);
			free_env(&data->env);
			rl_clear_history();
			exit(127);
		}
		else
		{
			data->exit_code = 126;
			free(path);
			free_all(data);
			free_env(&data->env);
			rl_clear_history();
			exit(126);
		}
	}
}

void	exec(t_exec *mini, t_cmd *tmp_cmd, t_data *data)
{
	char *path = NULL;

	if (is_builtin(tmp_cmd))
	{
		int ret = ft_exec_builtin(data, tmp_cmd, mini);
		free(mini->pidarray);
		data->exit_code = ret;
		free_all(data);
		free_env(&data->env);
		free(data);
		rl_clear_history();
		exit(ret);
	}
	if (!tmp_cmd->args[0] || tmp_cmd->args[0][0] == '\0')
	{
		free(mini->pidarray);
		ft_putstr_fd("command not found: ", 2);
		ft_putendl_fd("", 2);
		data->exit_code = 127;
		free_all(data);
		free_env(&data->env);
		free(data);
		rl_clear_history();
		exit(127);
	}
	if (ft_strchr(tmp_cmd->args[0], '/')) // ?? chemin relatif/absolu
		path = ft_strdup(tmp_cmd->args[0]);
	else
	{
		path = get_path(tmp_cmd->args[0], data->env);
		if (!path)
		{
			free(mini->pidarray);
			ft_putstr_fd("command not found: ", 2);
			ft_putendl_fd(tmp_cmd->args[0], 2);
			data->exit_code = 127;
			free_all(data);
			free_env(&data->env);
			free(data);
			rl_clear_history();
			exit(127);
		}
	}
	do_execve_bonus(mini, tmp_cmd, path, data);
}