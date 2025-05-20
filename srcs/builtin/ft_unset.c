/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tzara <tzara@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/22 14:10:05 by tzara             #+#    #+#             */
/*   Updated: 2025/05/20 12:27:44 by tzara            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	unset_var(char *name, t_env **env_ptr)
{
	t_env	*curr;
	t_env	*prev;
	int		name_len;

	curr = *env_ptr;
	prev = NULL;
	name_len = ft_strlen(name);
	while (curr)
	{
		if ((ft_strncmp(curr->env, name, name_len) == 0)
			&& (curr->env[name_len] == '=' || curr->env[name_len] == '\0'))
		{
			if (prev)
				prev->next = curr->next;
			else
				*env_ptr = curr->next;
			free(curr->env);
			free(curr);
			return (0);
		}
		prev = curr;
		curr = curr->next;
	}
	return (0);
}

void	print_unset_error(char *name)
{
	write(2, "unset: '", 8);
	write(2, name, strlen(name));
	write(2, "': not a valid identifier\n", 27);
}

int	ft_unset(char **args, t_env **env_ptr)
{
	int	i;

	i = 1;
	while (args[i])
	{
		if (!is_valid_identifier(args[i]))
			print_unset_error(args[i]);
		else
			unset_var(args[i], env_ptr);
		i++;
	}
	return (0);
}
