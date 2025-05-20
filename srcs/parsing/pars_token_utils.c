/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pars_token_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tzara <tzara@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/20 15:50:44 by tzara             #+#    #+#             */
/*   Updated: 2025/05/20 15:53:21 by tzara            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

char	*append_char(char *current_word, char c)
{
	int		len;
	char	*new_word;

	if (current_word != NULL)
		len = ft_strlen(current_word);
	else
		len = 0;
	new_word = malloc(len + 2);
	if (!new_word)
		return (NULL);
	if (current_word)
	{
		ft_strcpy(new_word, current_word);
		free(current_word);
	}
	else
		new_word[0] = '\0';
	new_word[len] = c;
	new_word[len + 1] = '\0';
	return (new_word);
}

char	*get_exp(char *name, t_env *env)
{
	t_env	*tmp;

	tmp = env;
	while (tmp)
	{
		if (ft_strncmp(tmp->env, name, ft_strlen(name)) == 0
			&& tmp->env[ft_strlen(name)] == '=')
		{
			return (ft_strdup(tmp->env + ft_strlen(name) + 1));
		}
		tmp = tmp->next;
	}
	return (NULL);
}

int	is_operator(char *s)
{
	if (!s)
		return (0);
	return (!ft_strncmp(s, "<<", 2) || !ft_strncmp(s, ">>", 2) || !ft_strncmp(s,
			"<", 1) || !ft_strncmp(s, ">", 1) || !ft_strncmp(s, "|", 1));
}

void	space_token(t_data *data, char **tmp, int *i)
{
	token_next(data, *tmp);
	*tmp = NULL;
	(*i)++;
}

void	normal_token(char **tmp, char *cmd, int *i, int *in_here_doc)
{
	*tmp = append_char(*tmp, cmd[*i]);
	(*i)++;
	if (*in_here_doc && (cmd[*i] == ' ' || cmd[*i] == '\t' || !cmd[*i]))
		*in_here_doc = 0;
}
