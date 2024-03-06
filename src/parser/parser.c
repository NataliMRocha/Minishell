/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egeraldo <egeraldo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/02 18:45:05 by egeraldo          #+#    #+#             */
/*   Updated: 2024/03/06 16:19:46 by egeraldo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_ast	*parser(t_token *token_list)
{
	t_ast	*tree;

	tree = NULL;
	tree = ast_constructor(token_list);
	ast_holder(tree, 0);
	free_token_list(*get_tokens(0));
	token_list = NULL;
	return (tree);
}

int	check_builtin(t_token **token_list)
{
	t_token	*tmp;
	t_envs	**envs;

	envs = create_envs_table(1);
	tmp = *token_list;
	while(tmp)
	{
		if (tmp->next && ft_strncmp("export", tmp->data, ft_strlen(tmp->data)) == 0)
			ft_export(tmp->next->data, envs);
		else if (tmp->next && ft_strncmp("unset", tmp->data, ft_strlen(tmp->data)) == 0)
			ft_unset(tmp->next->data, envs);
		else if (ft_strncmp("env", tmp->data, ft_strlen(tmp->data)) == 0)
			print_env_list(*envs);
		else if (ft_strncmp("exit", tmp->data, ft_strlen(tmp->data)) == 0)
			return (3);
		tmp = tmp->next;
	}
	return (0);

}
