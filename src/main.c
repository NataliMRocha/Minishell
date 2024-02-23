/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egeraldo <egeraldo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/16 10:28:13 by egeraldo          #+#    #+#             */
/*   Updated: 2024/02/23 12:44:31 by egeraldo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	print_ast(t_ast *root)
{
	int	i;

	i = 0;
	if (root)
	{
		print_ast(root->left);

		if (root && root->command_list)
			while(root->command_list[i])
				printf("%s ", root->command_list[i++]);
		else
			printf("%d ", root->type);

		print_ast(root->right);
	}
}

void	free_program(t_ast **root, t_token **token_list, char **get_cmd)
{
	free(*get_cmd);
	free_ast(*root);
	free_token_list(*token_list);
	*root = NULL;
	*token_list = NULL;
}

int main(void)
{
	t_token *token_list = NULL;
	t_envs **var_envs = create_envs_table();
	t_ast	*root;
	char *get_cmd;
	//setup_signals();

	while (1)
	{
		get_cmd = ft_readline();
		// heredoc("result_heredoc", "eof", *var_envs);
		if (ft_strncmp(get_cmd, "exit", 4) == 0)
			break;
		if (list_fill(&token_list, get_cmd, *var_envs) != 0)
			continue;
		root = parser(token_list, var_envs);
		printf("\ncomandos: ");
		print_ast(root);
		printf("\n");
		free_program(&root, &token_list, &get_cmd);
	}
	free_program(&root, &token_list, &get_cmd);
	free_env_list(*var_envs);
	return (0);
}
