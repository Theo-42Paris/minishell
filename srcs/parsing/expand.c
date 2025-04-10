/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kjolly <kjolly@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/09 11:56:16 by kjolly            #+#    #+#             */
/*   Updated: 2025/04/10 12:09:12 by kjolly           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

char	*handle_expand(char *src, t_env **env)
{
	char	*final;

	final = expandables(src, env);
	if (!final)
		return (NULL);
	return (final);
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

char	*expandables(char *src, t_env **env)
{
	char	*result;
	char	*tmp;
	char	*env_find;
	int		start;
	int		var_start;
	int		i;

	i = 0;
	start = 0;
	var_start = 0;
	result = ft_strdup("");
	if (!result)
		return (NULL);
	while (src[i])
	{
		if (src[i] == '$')
		{
			tmp = ft_substr(src, start, i - start);
			result = ft_strjoin(result, tmp);
			free(tmp);
			i++;
			if (src[i] == '?')
				printf("mimimi"); //handle_signal();
			else
			{
				var_start = i;
				while (src[i] && src[i] != ' ' && src[i] != '\t' && src[i] != '$')
					i++;
				tmp = ft_substr(src, var_start, i - var_start);
				env_find = find_path(env, tmp);
				if (env_find)
					result = ft_strjoin(result, env_find);
				free(tmp);
			}
			start = i;
		}
		else
			i++;
	}
	if (start < i)
    {
        tmp = ft_substr(src, start, i - start);
        result = ft_strjoin(result, tmp);
        free(tmp);
    }
    return (result);
}

// int last_exit_status(int status)
// {
//     if (WIFEXITED(status))
//         return (WEXITSTATUS(status));
//     return (1);
// }