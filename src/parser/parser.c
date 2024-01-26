/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: natali <natali@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/26 16:22:00 by natali            #+#    #+#             */
/*   Updated: 2024/01/26 17:20:30 by natali           ###   ########.fr       */
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


int check_syntaxe(t_token **list)
{
    t_token *tmp;

    tmp = *list;
    if (tmp->type == PIPE || tmp->type == AND || tmp->type == OR)
		return(1);
    while(tmp)
    {
        if ((tmp->type == PIPE || tmp->type == REDIR_HERE_DOC
                || tmp->type == REDIR_IN || tmp->type == PAREN_OPEN
                || tmp->type == AND || tmp->type == OR || tmp->type == REDIR_OUT
                || tmp->type == REDIR_APPEND) && tmp->next == NULL)
						return(1);
        else if ((tmp->type == REDIR_IN && tmp->next->type == PIPE)
					|| (tmp->next->type == REDIR_OUT && tmp->type == PIPE))
						return(1) ;
        else if ((tmp->data[0] == '|' && tmp->next->data[0] == '|')
                    || (tmp->type == AND && tmp->next->type == AND)
                    || (tmp->data[0] == '<' && tmp->next->data[0] == '<')
                    || (tmp->data[0] == '>' && tmp->next->data[0] == '>'))
 						return(1) ;
    }
	return(0);
}
