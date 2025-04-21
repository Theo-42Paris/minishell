/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kjolly <kjolly@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/09 11:56:16 by kjolly            #+#    #+#             */
/*   Updated: 2025/04/21 10:55:57 by kjolly           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

char	*append_result(char *result, char *src, int start, int end)
{
	char	*tmp;
	char	*new_result;

	tmp = ft_substr(src, start, end - start);
	if (!tmp)
		return (result);
	new_result = ft_strjoin(result, tmp);
	free(result);
	free(tmp);
	return (new_result);
}

char	*safe_strjoin(char *s1, const char *s2)
{
	char	*res;

	if (!s1)
		return (ft_strdup(s2));
	res = ft_strjoin(s1, s2);
	free(s1);
	return (res);
}

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
	while (src[i] && src[i] != ' ' && src[i] != '\t' && src[i] != '$' && ft_isalnum(src[i]))
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
