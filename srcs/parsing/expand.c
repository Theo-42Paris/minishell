/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kjolly <kjolly@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/09 11:56:16 by kjolly            #+#    #+#             */
/*   Updated: 2025/05/27 15:38:10 by kjolly           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

// ! JE T'AI MIT UNE VERSION A LA NORME DE CLAUDE EN BAS
// ! A VERIF. SI ELLE TE CONVIENT GARDE. JSP SI ELLE MARCHE
// ! FAUT UNE STRUCT EN PLUS C CHIANT
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

int	handle_variable_i(char *src, int i, char **result, t_data *data)
{
	int		var_start;
	char	*tmp;
	char	*env_find;
	char	*exit_str;

	if (src[i] == '?')
	{
		exit_str = ft_itoa(data->exit_code);
		if (!exit_str)
			return (i + 1);
		*result = safe_strjoin(*result, exit_str);
		free(exit_str);
		return (i + 1);
	}
	var_start = i;
	while (src[i] && (ft_isalnum(src[i]) || src[i] == '_'))
		i++;
	tmp = ft_substr(src, var_start, i - var_start);
	env_find = find_path(&data->env, tmp);
	if (env_find)
		*result = safe_strjoin(*result, env_find);
	free(tmp);
	return (i);
}

char	*expandables(char *src, t_data *data)
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
			i = handle_variable_i(src, i + 1, &result, data);
			start = i;
		}
		else
			i++;
	}
	if (start < i)
		result = append_result(result, src, start, i);
	return (result);
}
