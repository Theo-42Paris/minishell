/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tzara <tzara@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/09 13:06:03 by tzara             #+#    #+#             */
/*   Updated: 2025/04/10 15:36:25 by tzara            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

typedef struct s_env_var
{
	char				*name;
	char				*value;
	struct s_env_var	*next;
}						t_env_var;

/**
 * Updates or adds an environment variable to your custom environment
 */
void	update_env_var(t_env_var **env_list, const char *name,
		const char *value)
{
	t_env_var	*current;
	t_env_var	*new_var;

	current = *env_list;
	// Search if variable already exists
	while (current)
	{
		if (strcmp(current->name, name) == 0)
		{
			// Update existing variable
			free(current->value);
			current->value = strdup(value);
			return ;
		}
		current = current->next;
	}
	// Create new variable if not found
	new_var = (t_env_var *)malloc(sizeof(t_env_var));
	if (!new_var)
		return ;
	new_var->name = strdup(name);
	new_var->value = strdup(value);
	new_var->next = *env_list;
	*env_list = new_var;
}

/**
 * Example usage in your minishell command parser:
 */
void	ft_cd(char *args, t_env_var **env_list)
{
	// Execute cd and update your custom environment
	if (execute_cd(args) == 0)
	{
		char *pwd = getcwd(NULL, 0);
		if (pwd)
		{
			update_env_var(env_list, "PWD", pwd);
			free(pwd);
		}
	}
}