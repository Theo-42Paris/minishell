/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pars_token_4.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tzara <tzara@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/23 21:58:45 by tzara             #+#    #+#             */
/*   Updated: 2025/05/23 22:00:07 by tzara            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	free_if_exists(char **tmp)
{
	if (*tmp)
		free(*tmp);
}

void	handle_exit_code(int *i, t_data *data, char **tmp)
{
	char	*value;
	char	*joined;

	value = ft_itoa(data->exit_code);
	(*i)++;
	if (*tmp)
		joined = ft_strjoin(*tmp, value);
	else
		joined = ft_strdup(value);
	free(value);
	free(*tmp);
	*tmp = joined;
}

void	merge_value(char *value, char **tmp)
{
	char	*joined;

	if (!value)
		return ;
	if (*tmp)
		joined = ft_strjoin(*tmp, value);
	else
		joined = ft_strdup(value);
	if (!joined)
	{
		free(value);
		return ;
	}
	free(value);
	free(*tmp);
	*tmp = joined;
}

void	expand_variable(char *var_name, t_data *data, char **tmp)
{
	char	*value;

	value = get_exp(var_name, data->env);
	free(var_name);
	merge_value(value, tmp);
}

void	handle_variable(char *cmd, int *i, t_data *data, char **tmp)
{
	int		start;
	int		end;
	char	*var_name;

	start = *i;
	end = start;
	while (cmd[end] && (ft_isalnum(cmd[end]) || cmd[end] == '_'))
		end++;
	if (start == end)
		return ((void)(*tmp = append_char(*tmp, '$')));
	var_name = ft_substr(cmd, start, end - start);
	*i = end;
	if (!var_name)
		return (free_if_exists(tmp));
	expand_variable(var_name, data, tmp);
}
