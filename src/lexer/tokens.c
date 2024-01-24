/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokens.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egeraldo <egeraldo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/18 13:41:05 by egeraldo          #+#    #+#             */
/*   Updated: 2024/01/24 16:06:55 by egeraldo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	stack_len(t_token *list)
{
	t_token	*current;
	int		count;

	count = 0;
	current = list;
	while (current != NULL)
	{
		count++;
		current = current->next;
	}
	return (count);
}

t_token	*find_last_node(t_token *head)
{
	if (head == NULL)
		return (NULL);
	while (head->next)
		head = head->next;
	return (head);
}

void	stack_fill(t_token *list)
{
	list->data = "";
	list->type = 0;
	list->next = NULL;
	list->prev = NULL;
}

void	append_node(t_token **list, char *content)
{
	t_token	*node;
	t_token	*last_node;

	if (list == NULL)
		return ;
	node = malloc(sizeof(t_token));
	stack_fill(node);
	if (node == NULL)
		return ;
	node->next = NULL;
	node->data = content;
	ft_write_types(node);
	if (*list == NULL)
	{
		*list = node;
		node->prev = NULL;
	}
	else
	{
		last_node = find_last_node(*list);
		last_node->next = node;
		node->prev = last_node;
	}
}

void	list_fill(t_token **list, char *readline)
{
	char	*token;
	int		call;


	call = 0;
	token = " ";
	while (token && *token != '\0')
	{
		token = ft_strtok(readline, call++);
		if (token)
			append_node(list, token);
	}
}
