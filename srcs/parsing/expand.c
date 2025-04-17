/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kjolly <kjolly@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/09 11:56:16 by kjolly            #+#    #+#             */
/*   Updated: 2025/04/17 17:30:21 by kjolly           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

// char	*handle_expand(char *src, t_env **env)
// {
// 	char	*final;
// 	final = expandables(src, env);
// 	if (!final)
// 		return (NULL);
// 	return (final);
// }

char	*find_path(t_env **env, char *tmp)
{
	t_env	*env_tmp;

	env_tmp = *env;
	while (env_tmp)
	{
		if (ft_strncmp(env_tmp->env, tmp, ft_strlen(tmp)) == 0
			&& env_tmp->env[ft_strlen(tmp)] == '=')
			return (env_tmp->env + ft_strlen(tmp) + 1);
		env_tmp = env_tmp->next;
	}
	return (NULL);
}

int	handle_variable_i(char *src, int i, t_env **env, char **result)
{
	int		var_start;
	char	*tmp;
	char	*env_find;

	if (src[i] == '?')
	{
		printf("pas encore gerer");
		return (i + 1);
	}
	var_start = i;
	while (src[i] && src[i] != ' ' && src[i] != '\t' && src[i] != '$')
		i++;
	tmp = ft_substr(src, var_start, i - var_start);
	env_find = find_path(env, tmp);
	if (env_find)
		*result = safe_strjoin(*result, env_find);
	free(tmp);
	return (i);
}

char	*expandables(char *src, t_env **env)
{
	int		i;
	int		start;
	char	*result;

	i = 0;
	start = 0;
	result = ft_strdup("");
	if (!result)
		return (NULL);
	while (src[i])
	{
		if (src[i] == '$')
		{
			result = append_result(result, src, start, i);
			i = handle_variable_i(src, i + 1, env, &result);
			start = i;
		}
		else
			i++;
	}
	if (start < i)
		result = append_result(result, src, start, i);
	return (result);
}

// int last_exit_status(int status)
// {
//     if (WIFEXITED(status))
//         return (WEXITSTATUS(status));
//     return (1);
// }