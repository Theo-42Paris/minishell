/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export_utils_2.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tzara <tzara@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/01 08:41:43 by tzara             #+#    #+#             */
/*   Updated: 2025/05/20 14:33:59 by tzara            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

t_env	*find_env_var(char *arg, t_env *env)
{
	int	name_len;

	name_len = 0;
	while (arg[name_len] && arg[name_len] != '=')
		name_len++;
	while (env)
	{
		if (ft_strncmp(env->env, arg, name_len) == 0
			&& env->env[name_len] == '=')
			return (env);
		env = env->next;
	}
	return (NULL);
}

int	is_valid_identifier(const char *arg)
{
	int	i;

	i = 0;
	if (!arg || (!ft_isalpha(arg[0]) && arg[0] != '_'))
		return (0);
	while (arg[i] && arg[i] != '=')
	{
		if (!ft_isalnum(arg[i]) && arg[i] != '_')
			return (0);
		i++;
	}
	return (1);
}

void	print_export_error(const char *arg)
{
	write(2, "export: '", 9);
	write(2, arg, ft_strlen(arg));
	write(2, "': not a valid var name only letters or '_' at beginning\n", 58);
}

int	env_list_size(t_env *env)
{
	int	size;

	size = 0;
	while (env)
	{
		size++;
		env = env->next;
	}
	return (size);
}
