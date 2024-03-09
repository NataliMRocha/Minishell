/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: etovaz <etovaz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/02 18:45:05 by egeraldo          #+#    #+#             */
/*   Updated: 2024/03/09 19:05:57 by etovaz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_ast	*parser(t_token *token_list, char *get_cmd)
{
	t_ast	*tree;

	tree = NULL;
	if ((get_cmd && !*get_cmd) || list_fill(&token_list, get_cmd) != 0)
		return (NULL);
	capture_heredoc(&token_list);
	if (check_syntax_and_quotes(&token_list, get_cmd))
		return (NULL);
	tree = ast_constructor(token_list);
	ast_holder(tree, 0, 0);
	if (!ft_strncmp(tree->cmd_list[0], "exit", 4))
		ft_exit(ft_atoi(tree->cmd_list[0]));
	if (token_list && token_list->data && *token_list->data)
		free_token_list(&token_list);
	token_list = NULL;
	return (tree);
}
