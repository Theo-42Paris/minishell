/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pigeon.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kjolly <kjolly@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 15:10:03 by kjolly            #+#    #+#             */
/*   Updated: 2025/04/14 17:49:56 by kjolly           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void *ft_malloc(int size);

void add_node(t_pigeon **head, int size, void *ptr)
{
    t_pigeon *new_node;
    t_pigeon *current;

    new_node = malloc(sizeof(t_pigeon));
    if (!new_node)
        return;
    new_node->ptr = ptr;
    new_node->size = size;
    new_node->next = NULL;
    if (*head == NULL)
    {
        *head = new_node;
        return;
    }
    current = *head;
    while (current->next)
        current = current->next;
    current->next = new_node;
}

void ft_free(void)
{
    t_pigeon **head;
    t_pigeon *current;
    t_pigeon *next;

    head = ft_malloc(-1);
    if (!head || !*head)
        return;
    current = *head;
    while (current)
    {
        next = current->next;
        free(current->ptr);
        free(current);
        current = next;
    }
    *head = NULL;
}

void *ft_malloc(int size)
{
    static t_pigeon *head = NULL;
    void *ptr;

    if (size == -1)
        return (&head);
    if (size <= 0)
        return (NULL);
    ptr = malloc(size);
    if (!ptr)
        return (NULL);
    add_node(&head, size, ptr);
    return (ptr);
}
