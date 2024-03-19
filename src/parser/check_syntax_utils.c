/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_syntax_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egeraldo <egeraldo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/18 16:40:33 by etovaz            #+#    #+#             */
/*   Updated: 2024/03/19 12:56:50 by egeraldo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	is_redir_followed_by_pipe(t_token *tmp)
{
	return (tmp && tmp->next && ((tmp->type == REDIR_IN
				&& tmp->next->type == PIPE) || (tmp->type == REDIR_OUT
				&& tmp->next->type == PIPE)));
}

int	check_block_error(t_token *list)
{
	return (list && ((list->type == BLOCK && block_checker(list))));
}

int	is_redir_after_symbol(t_token *list)
{
	return (list && (list->data && is_symbol(list->data) && (list->next
				&& is_symbol(list->next->data))
			&& !is_redirect(list->next->type)));
}
