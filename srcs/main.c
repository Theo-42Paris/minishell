/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tzara <tzara@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/10 12:32:39 by tzara             #+#    #+#             */
/*   Updated: 2025/03/15 11:18:22 by tzara            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

t_tokens	*ft_list_tokens(char *line)
{
	// assigner les parties de la cmd a des types;
}

int	ft_tokens(t_data *data)
{
	if (quote_error(data->line) == -1)
	{
		printf("Error : Quotes pas fermé t'abbuse\n");
		return (-1);
	}
	data->tokens = ft_list_tokens(data->line);
	if (data->tokens)
		return (-1);
}

int	ft_parsing(t_data *data)
{
	// verifier que la ligne de commande est valide
	// pour l'execution (error managing)
}

int	main(int argc, char **argv, char **envp)
{
	t_data *data;

	if (!data || argc != 1)
		return (-1);
	while (1)
	{
		data->line = readline("minishell> ");
		if (!data->line)
			break ;
		if (data->line[0] != '\0')
			add_history(data->line);
		if (ft_token(data) == 1 && ft_parsing(data) == 1)
			execute();
		// waitpid();
		ft_reset_cmd(); //remettre tt data a 0 pour la pro cmd    cat | "grep error" 
	}
	if (isatty(STDIN_FILENO))
	{
		ft_printf("exit\n");
		rl_clear_history();
		free_all_data();
	}
	return (0);
}