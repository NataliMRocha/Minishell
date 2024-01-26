/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egeraldo <egeraldo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/26 16:22:00 by natali            #+#    #+#             */
/*   Updated: 2024/01/26 17:48:56 by egeraldo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* >Parsing
# Erros de sintaxe
+ Terminar com | & < ou >
+ Começar com | ou &
+ Se houver < | ou > | juntos
+ Se houver | | ou & & ou < < (espaço entre os 2 operadores)
 */

#include "../../includes/minishell.h"

int	check_syntaxe(t_token **list)
{
	t_token	*tmp;

	if (list == NULL || *list == NULL)
		return (0);
	tmp = *list;
	if (tmp->type == PIPE || tmp->type == AND || tmp->type == OR)
		return (1);
	while (tmp->next)
	{
		if ((tmp->type == REDIR_IN && tmp->next->type == PIPE)
			|| (tmp->next->type == REDIR_OUT && tmp->type == PIPE))
			return (1);
		if ((tmp->data[0] == '|' && tmp->next->data[0] == '|')
			|| (tmp->type == AND && tmp->next->type == AND)
			|| (tmp->data[0] == '<' && tmp->next->data[0] == '<')
			|| (tmp->data[0] == '>' && tmp->next->data[0] == '>'))
			return (1);
    tmp = tmp->next;
	}
  if ((tmp->type == PIPE || tmp->type == REDIR_HERE_DOC
				|| tmp->type == REDIR_IN || tmp->type == PAREN_OPEN
				|| tmp->type == AND || tmp->type == OR || tmp->type == REDIR_OUT
				|| tmp->type == REDIR_APPEND) && tmp->next == NULL)
			return (1);
	return (0);
}
