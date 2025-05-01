/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_execve.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kjolly <kjolly@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/01 13:31:37 by kjolly            #+#    #+#             */
/*   Updated: 2025/05/01 18:19:04 by kjolly           ###   ########.fr       */
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
	first_path = find_path_exec(env);
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
	while (tmp2)
	{
		prep_env[i] = ft_strdup(tmp2->env);
		i++;
		tmp2 = tmp2->next;
	}
	prep_env[i] = NULL;
	return (prep_env);
}

void	do_execve_bonus(t_exec *mini, t_cmd *tmp_cmd, char *path, t_env *env)
{
	char	**exec_env;
	
	exec_env = env_for_exec(env);
	if (execve(path, tmp_cmd->args, exec_env) == -1)
	{
		free(mini->pidarray);
		perror(tmp_cmd->args[0]);
		free(path);
		exit(126);
	}
}

void    exec(t_exec *mini, t_cmd *tmp_cmd, t_data *data)
{
	char	*path;
	
	if (ft_isbuiltin(data->cmd))
	{
		ft_exec_builtin(data, data->cmd);
		return ;
	}
	if (access(tmp_cmd->args[0], F_OK) == 0)
		path = tmp_cmd->args[0];
	else
	{
		path = get_path(tmp_cmd->args[0], (*data).env);
		if (!path)
		{
			free(mini->pidarray);
			ft_putstr_fd("command not found: ", 2);
			ft_putendl_fd(tmp_cmd->args[0], 2);
			exit(127);
		}
	}
	do_execve_bonus(mini, tmp_cmd, path, (*data).env);
}
