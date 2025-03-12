/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kjolly <kjolly@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/10 12:32:39 by tzara             #+#    #+#             */
/*   Updated: 2025/03/12 10:58:31 by kjolly           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int main()
{
	char *str;

	while(1)
	{
		str = readline("minishell> ");
		ft_printf("%s\n", str);
		if (!str)
		{
			ft_printf("exit\n");
			break ;
		}
	}
	return (0);
}