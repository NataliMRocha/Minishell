/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egeraldo <egeraldo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/02 18:45:05 by egeraldo          #+#    #+#             */
/*   Updated: 2024/02/28 18:44:19 by egeraldo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

//TODO: função para verificar se o comando é um executável
//TODO: função pra lidar com os redirects e verifica se temos acesso e permissao aos arquivos
//TODO: função para executar o comando

t_ast	*ast_holder(t_ast *root, int its_created)
{
	static t_ast	*ast_address;

	if (root && !its_created)
		ast_address = root;
	return (ast_address);
}

t_ast	*parser(t_token *token_list)
{
	t_ast	*tree;

	tree = NULL;
	tree = ast_constructor(token_list);
	ast_holder(tree, 0);
	free_token_list(token_list);
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
