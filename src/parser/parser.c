/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egeraldo <egeraldo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/02 18:45:05 by egeraldo          #+#    #+#             */
/*   Updated: 2024/03/11 14:05:08 by egeraldo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_ast	*parser(char *get_cmd)
{
	t_ast	*tree;
	t_token	*token_list;

	tree = NULL;
	token_list = NULL;
	if ((get_cmd && !*get_cmd) || list_fill(&token_list, get_cmd) != 0)
		return (NULL);
	capture_heredoc(&token_list);
	if (check_syntax_and_quotes(&token_list, get_cmd))
		return (NULL);
	tree = ast_constructor(token_list);
	ast_holder(tree, 0, 0);
	if (token_list && token_list->data && *token_list->data)
		free_token_list(&token_list);
	token_list = NULL;
	return (tree);
}
