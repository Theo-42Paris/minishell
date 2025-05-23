/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_execve_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tzara <tzara@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/23 14:01:27 by tzara             #+#    #+#             */
/*   Updated: 2025/05/23 15:21:47 by tzara            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static char	*ft_lignes_path(char **new_path, int i, char *cmd)
{
	char	*full_path;

	full_path = concat_path(new_path[i], cmd);
	if (!full_path)
		return (free_str(new_path), NULL);
	if (access(full_path, F_OK | X_OK) == 0)
		return (free_str(new_path), full_path);
	free(full_path);
	return (NULL);
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
		full_path = ft_lignes_path(new_path, i, cmd);
		if (full_path)
			return (full_path);
		i++;
	}
	free_str(new_path);
	return (NULL);
}

static int	ft_ligne_env_ex(char **prep_env, int i, t_env *tmp2)
{
	prep_env[i] = ft_strdup(tmp2->env);
	if (!prep_env[i])
	{
		while (--i >= 0)
			free(prep_env[i]);
		free(prep_env);
		return (0);
	}
	return (1);
}

void	init_var_env_for_exec(int *i, int *count, t_env **tmp1, t_env *env)
{
	*i = 0;
	*count = 0;
	*tmp1 = env;
}

char	**env_for_exec(t_env *env)
{
	int		count;
	int		i;
	char	**prep_env;
	t_env	*tmp1;
	t_env	*tmp2;

	init_var_env_for_exec(&i, &count, &tmp1, env);
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
		if (!ft_ligne_env_ex(prep_env, i, tmp2))
			return (NULL);
		i++;
		tmp2 = tmp2->next;
	}
	prep_env[i] = NULL;
	return (prep_env);
}
