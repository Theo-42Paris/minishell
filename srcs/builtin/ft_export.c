/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kjolly <kjolly@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/22 14:19:18 by tzara             #+#    #+#             */
/*   Updated: 2025/05/26 11:58:43 by kjolly           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

t_env	*create_or_update_node(char *arg, t_env *found)
{
	t_env	*new_node;
	char	*dup;

	if (found)
	{
		free(found->env);
		dup = ft_strdup(arg);
		if (!dup)
			return (NULL);
		found->env = dup;
		return (found);
	}
	new_node = malloc(sizeof(t_env));
	if (!new_node)
		return (NULL);
	dup = ft_strdup(arg);
	if (!dup)
	{
		free(new_node);
		return (NULL);
	}
	new_node->env = dup;
	new_node->next = NULL;
	return (new_node);
}

int	add_or_update_env(char *arg, t_env **env_ptr)
{
	t_env	*found;
	t_env	*node;
	t_env	*tmp;

	found = find_env_var(arg, *env_ptr);
	node = create_or_update_node(arg, found);
	if (!node)
		return (1);
	if (!found)
	{
		if (!*env_ptr)
			*env_ptr = node;
		else
		{
			tmp = *env_ptr;
			while (tmp->next)
				tmp = tmp->next;
			tmp->next = node;
		}
	}
	return (0);
}

int	process_export_arg(char *arg, t_env **env_ptr)
{
	int		len;
	int		ret;
	char	*tmp;

	if (!is_valid_identifier(arg))
	{
		print_export_error(arg);
		return (1);
	}
	if (!ft_strchr(arg, '='))
	{
		len = ft_strlen(arg);
		tmp = malloc(sizeof(char) * (len + 1));
		if (!tmp)
			return (1);
		ft_strcpy(tmp, arg);
		tmp[len] = '\0';
		ret = add_or_update_env(tmp, env_ptr);
		free(tmp);
		return (ret);
	}
	return (add_or_update_env(arg, env_ptr));
}

int	print_env_list(t_env *env)
{
	int		size;
	char	**env_array;

	size = env_list_size(env);
	env_array = create_env_array(env, size);
	if (!env_array)
		return (1);
	sort_env_array(env_array, size);
	print_env_array(env_array, size);
	free(env_array);
	return (0);
}

int	ft_export(char **args, t_env **env_ptr)
{
	int	i;
	int	exit_code;

	if (args[1] == NULL)
		return (print_env_list(*env_ptr));
	i = 1;
	exit_code = 0;
	while (args[i])
	{
		if (process_export_arg(args[i], env_ptr) != 0)
			exit_code = 1;
		i++;
	}
	return (exit_code);
}
