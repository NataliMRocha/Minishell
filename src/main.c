/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egeraldo <egeraldo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/16 10:28:13 by egeraldo          #+#    #+#             */
/*   Updated: 2024/02/22 16:08:48 by egeraldo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	print_ast(t_ast *root)
{
	if (root)
	{
		print_ast(root->left);

		if (root && root->tokens_to_exec)
			printf("%s ", root->tokens_to_exec->data);
		else
			printf("%d ", root->type);

		print_ast(root->right);
	}
}

int main(void)
{
	t_token *token_list = NULL;
	t_envs **var_envs = create_envs_table();
	t_ast	*tree;
	char *get_cmd;
	//setup_signals();

	while (1)
	{
		get_cmd = ft_readline();
		// heredoc("result_heredoc", "eof", *var_envs);
		if (list_fill(&token_list, get_cmd, *var_envs) != 0)
			continue;
		tree = parser(token_list, var_envs);
		printf("\n\ncomandos: ");
		print_ast(tree);
		printf("\n");
		free(get_cmd);
		free_token_list(token_list);
		token_list = NULL;
	}
	free(get_cmd);
	free_token_list(token_list);
	free_env_list(*var_envs);
	return (0);
}
