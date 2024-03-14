/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: natali <natali@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/24 16:18:49 by egeraldo          #+#    #+#             */
/*   Updated: 2024/03/13 16:36:23 by natali           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*free_static(char *res, int i, int j)
{
	char	*temp;

	if (res && res[0] == '\0')
		return (NULL);
	temp = ft_strdup(&res[i + j]);
	if ((temp && temp[0] == '\0') || ft_strncmp(res, temp, 125) == 0)
	{
		free(temp);
		temp = NULL;
	}
	free(res);
	res = NULL;
	return (temp);
}

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
	while (head && head->next)
		head = head->next;
	return (head);
}

void	free_token_list(t_token **list)
{
	t_token	*tmp;

	while (list && *list)
	{
		if (list && (*list)->next && (*list)->next->data)
			tmp = (*list)->next;
		else
			tmp = NULL;
		if (list && *list && (*list)->data && *(*list)->data)
		{
			free((*list)->data);
			(*list)->data = NULL;
		}
		free(*list);
		*list = NULL;
		*list = tmp;
	}
	list = NULL;
}

void	print_error(int error)
{
	if (error == PIPE)
		ft_putstr_fd("syntax error near unexpected token `|'\n", 2);
	else if (error == AND)
		ft_putstr_fd("syntax error near unexpected token `&&'\n", 2);
	else if (error == OR)
		ft_putstr_fd("syntax error near unexpected token `||'\n", 2);
	else if (error == 1)
		ft_putstr_fd("Minishell can't deal with open quotes\n", 2);
	else if (error == 13)
		ft_putstr_fd("syntax error near unexpected token new line\n", 2);
	else if (error == 126)
		ft_putstr_fd("Is a directory\n", 2);
}
