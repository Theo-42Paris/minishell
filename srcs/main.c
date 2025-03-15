/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tzara <tzara@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/10 12:32:39 by tzara             #+#    #+#             */
<<<<<<< HEAD
/*   Updated: 2025/03/15 12:18:40 by tzara            ###   ########.fr       */
=======
/*   Updated: 2025/03/15 12:31:36 by tzara            ###   ########.fr       */
>>>>>>> main
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

<<<<<<< HEAD
char	*ft_strndup(char *src, int a)
{
	char	*dst;
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	dst = (char *)malloc(sizeof(char) * (a + 1));
	if (!dst)
		return (NULL);
	while(i < a)
	{
		dst[j++] = src[i++];
	}
	dst[j] = '\0';
	return (dst);
}


void	tokenizer(/*t_tokens *token*/ char *str)
{
	int		i;
	char	*dup;
	char	quote;
	int 	start;

	i = 0;
	while(str[i] == ' ' || str[i] == '\t')
		i++;
	while(str[i])
	{
		start = i;
		if (str[i] == '\'' || str[i] == '"')
		{
			quote = str[i++];
			start = i;
			while(str[i] && quote != str[i])
				i++;
			dup = ft_strndup(str + start, i - start);
			i++;
		}
		else
		{ 
			while(str[i] && str[i] != ' ' && str[i] != '\'' && str[i] != '"' )
				i++;
			dup = ft_strndup(str + start, i - start);
		}
		printf("%s\n", dup);
		printf("----------------\n");
		free(dup);
		i++;
	}
}

int	ft_parsing(t_data *data)
{
	ft_tokenizer(tokens, data->line);
	return (1);
}

int	main(int argc, char **argv, char **envp)
{
	t_data *data;

	if (!data || argc != 1)
		return (-1);
	while (1)
	{
=======
int	main(int argc, char **argv, char **envp)
{
	t_data	*data;

	if (!data || argc != 1)
		return (-1);
	while (1)
	{
>>>>>>> main
		data->line = readline("minishell> ");
		if (!data->line)
			break ;
		if (data->line[0] != '\0')
			add_history(data->line);
		if (ft_token(data) == 1 && ft_parsing(data) == 1)
			execute();
		// waitpid();
<<<<<<< HEAD
		ft_reset_cmd(); //remettre tt data a 0 pour la pro cmd    cat | "grep error" 
=======
		ft_reset_cmd();
			// remettre tt data a 0 pour la pro cmd    cat | "grep error"
>>>>>>> main
	}
	if (isatty(STDIN_FILENO))
	{
		ft_printf("exit\n");
		rl_clear_history();
		free_all_data();
	}
	return (0);
}
