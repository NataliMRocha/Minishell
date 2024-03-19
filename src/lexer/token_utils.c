/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: etovaz <etovaz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/24 16:18:49 by egeraldo          #+#    #+#             */
/*   Updated: 2024/03/18 18:36:27 by etovaz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*free_static(char *res, int i, int j)
{
	char	*temp;

	if (res && res[0] == '\0')
		return (NULL);
	temp = ft_strdup(&res[i + j]);
	if ((temp && temp[0] == '\0') || ft_strncmp(res, temp, ft_strlen(res)) == 0)
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
		ft_putstr_fd("Minishell: syntax error near unexpected token `|'\n", 2);
	else if (error == AND)
		ft_putstr_fd("Minishell: syntax error near unexpected token `&&'\n", 2);
	else if (error == OR)
		ft_putstr_fd("Minishell: syntax error near unexpected token `||'\n", 2);
	else if (error == 1)
		ft_putstr_fd("Minishell: can't deal with open quotes\n", 2);
	else if (error == 2)
		ft_putstr_fd("Minishell: syntax error near unexpected token `)'\n", 2);
	else if (error == 13 || error == 7 || error == 6)
		ft_putstr_fd("Minishell: syntax error near unexpected token `newline'\n",
			2);
	else if (error == 126)
		ft_putstr_fd("Minishell: Is a directory\n", 2);
}
