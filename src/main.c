/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: natali <natali@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/16 10:28:13 by egeraldo          #+#    #+#             */
/*   Updated: 2024/03/06 19:21:24 by natali           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	update_status_error(int i)
{
	static int status;

	if (i == -1)
		return (status);
	status = i;
	return (status);
}

void	free_program(t_ast **root, char **get_cmd, t_envs **var_envs)
{
	if (get_cmd && *get_cmd)
		free(*get_cmd);
	if (root && *root)
	{
		free_ast(*root, 0);
		*root = NULL;
	}
	if (var_envs && *var_envs)
		free_env_list(*var_envs);
}

int main(void)
{
	t_token *token_list = NULL;
	t_ast	*root;
	char *get_cmd;
	//setup_signals();

	t_envs **var_envs = create_envs_table(0);
	root = NULL;
	while (1)
	{
		get_cmd = ft_readline();
		if (ft_strncmp(get_cmd, "exit", 4) == 0)
			break;
		if ((get_cmd && !*get_cmd) || list_fill(&token_list, get_cmd) != 0)
			continue;
		// heredoc("result_heredoc", "eof", *var_envs);
		if (check_syntax_and_quotes(&token_list, get_cmd))
			continue;
		root = parser(token_list);
		starting_exec(root);
		free_program(&root, &get_cmd, NULL);
		token_list = NULL;
	}
	free_program(&root, &get_cmd, var_envs);
	close_fds(NULL, 1);
	return (0);
}
