/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tzara <tzara@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/10 12:32:39 by tzara             #+#    #+#             */
/*   Updated: 2025/03/10 12:40:49 by tzara            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

t_data set_struct(t_data *data, int argc, char **argv)
{
    data->argc = argc;
    data->argv = argv;
}

int main(int argc, char **argv)
{
    t_data data;

    data = set_struct(&data, argc, argv);
    readline("MINISHELL");
}