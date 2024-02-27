/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egeraldo <egeraldo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/29 18:01:00 by egeraldo          #+#    #+#             */
/*   Updated: 2024/02/27 16:32:43 by egeraldo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	close_fds(int *fd, int i)
{
	int	j;

	j = 0;
	while (j < i)
		close(fd[j++]);
}

int	handle_fd_error(int *fd, int i, t_token *token_list)
{
	if (fd[i] < 0)
	{
		close_fds(fd, i);
		printf("minishell: %s: Permission denied\n", token_list->next->data);
		update_status_error(1);
		return (1);
	}
	return (0);
}

void	remove_tokens_after_handle(t_token **token_list, int token_to_remove,
		t_token_type type_to_remove)
{
	t_token	*delete;

	while (token_list && *token_list && token_to_remove > 0)
	{
		if (*token_list && (*token_list)->type == type_to_remove && (*token_list)->prev
			&& (*token_list)->next && (*token_list)->next->next)
		{
			delete = *token_list;
			(*token_list)->prev->next = (*token_list)->next->next;
			(*token_list)->next->next->prev = (*token_list)->prev;
			delete->next = NULL;
			delete->prev = NULL;
			while (token_list && (*token_list)->prev)
				*token_list = (*token_list)->prev;
			free_token_list(delete);
			token_to_remove--;
		}
		*token_list = (*token_list)->next;
	}
}

int	redir_out(t_token *tokens, t_token_type type)
{
	t_token	*temp;
	int		fd[1024];
	int		i;

	i = 0;
	ft_memset(fd, -1, 1024);
	temp = tokens;
	while (temp && temp->next && (type == REDIR_OUT || type == REDIR_APPEND))
	{
		if (temp->type == type)
		{
			fd[i] = open(temp->next->data, O_WRONLY | O_APPEND | O_CREAT, 0644);
			if (handle_fd_error(fd, i, temp))
				break ;
			i++;
		}
		temp = temp->next;
	}
	close_fds(fd, i - 1);
	remove_tokens_after_handle(&tokens, --i, type);
	return (fd[--i]);
}
