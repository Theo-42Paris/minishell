/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tzara <tzara@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/09 11:56:16 by kjolly            #+#    #+#             */
/*   Updated: 2025/05/23 22:49:41 by tzara            ###   ########.fr       */
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

int	handle_variable_i(char *src, int i, t_env **env, char **result,
		t_data *data)
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
	env_find = find_path(env, tmp);
	if (env_find)
		*result = safe_strjoin(*result, env_find);
	free(tmp);
	return (i);
}

char	*expandables(char *src, t_env **env, t_data *data)
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
			i = handle_variable_i(src, i + 1, env, &result, data);
			start = i;
		}
		else
			i++;
	}
	if (start < i)
		result = append_result(result, src, start, i);
	return (result);
}

// typedef struct s_expand_params
// {
// 	char	*src;
// 	t_env	**env;
// 	char	**result;
// 	t_data	*data;
// }	t_expand_params;

// char	*append_result(char *result, char *src, int start, int end)
// {
// 	char	*tmp;
// 	char	*new_result;

// 	tmp = ft_substr(src, start, end - start);
// 	if (!tmp)
// 		return (result);
// 	new_result = ft_strjoin(result, tmp);
// 	free(result);
// 	free(tmp);
// 	return (new_result);
// }

// char	*safe_strjoin(char *s1, const char *s2)
// {
// 	char	*res;

// 	if (!s1)
// 		return (ft_strdup(s2));
// 	res = ft_strjoin(s1, s2);
// 	free(s1);
// 	return (res);
// }

// char	*find_path(t_env **env, char *tmp)
// {
// 	t_env	*env_tmp;

// 	env_tmp = *env;
// 	while (env_tmp)
// 	{
// 		if (ft_strncmp(env_tmp->env, tmp, ft_strlen(tmp)) == 0
// 			&& env_tmp->env[ft_strlen(tmp)] == '=')
// 			return (env_tmp->env + ft_strlen(tmp) + 1);
// 		env_tmp = env_tmp->next;
// 	}
// 	return (NULL);
// }

// static int	handle_exit_code(t_expand_params *params, int i)
// {
// 	char	*exit_str;

// 	exit_str = ft_itoa(params->data->exit_code);
// 	if (!exit_str)
// 		return (i + 1);
// 	*(params->result) = safe_strjoin(*(params->result), exit_str);
// 	free(exit_str);
// 	return (i + 1);
// }

// static int	handle_env_variable(t_expand_params *params, int i)
// {
// 	int		var_start;
// 	char	*tmp;
// 	char	*env_find;

// 	var_start = i;
// 	while (params->src[i] && (ft_isalnum(params->src[i])
// 			|| params->src[i] == '_'))
// 		i++;
// 	tmp = ft_substr(params->src, var_start, i - var_start);
// 	env_find = find_path(params->env, tmp);
// 	if (env_find)
// 		*(params->result) = safe_strjoin(*(params->result), env_find);
// 	free(tmp);
// 	return (i);
// }

// int	handle_variable_i(t_expand_params *params, int i)
// {
// 	if (params->src[i] == '?')
// 		return (handle_exit_code(params, i));
// 	else
// 		return (handle_env_variable(params, i));
// }

// char	*expandables(char *src, t_env **env, t_data *data)
// {
// 	int				i;
// 	int				start;
// 	char			*result;
// 	t_expand_params	params;

// 	i = 0;
// 	start = 0;
// 	result = ft_strdup("");
// 	if (!result)
// 		return (NULL);
// 	params = (t_expand_params){src, env, &result, data};
// 	while (src[i])
// 	{
// 		if (src[i] == '$')
// 		{
// 			result = append_result(result, src, start, i);
// 			i = handle_variable_i(&params, i + 1);
// 			start = i;
// 		}
// 		else
// 			i++;
// 	}
// 	if (start < i)
// 		result = append_result(result, src, start, i);
// 	return (result);
// }
