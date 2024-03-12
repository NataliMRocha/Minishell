/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: etovaz <etovaz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/02 18:45:05 by egeraldo          #+#    #+#             */
/*   Updated: 2024/03/12 19:59:16 by etovaz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	ft_isin(char *str, char *set)
{
	int	i;

	i = 0;
	while (str && str[i] && ft_strchr(set, str[i]))
		i++;
	return (i);
}

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
	if (!ft_isin(get_cmd, "><|&"))
		holder_tokens(NULL, 1);
	return (tree);
}
