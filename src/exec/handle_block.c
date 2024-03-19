/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_block.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egeraldo <egeraldo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/11 20:50:57 by etovaz            #+#    #+#             */
/*   Updated: 2024/03/19 18:13:11 by egeraldo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*remove_bracket(char *block)
{
	char	*sub_prompt;
	int		str_len;

	str_len = ft_strlen(block) - 1;
	sub_prompt = ft_calloc(str_len, sizeof(char));
	if (block[0] == '(' && block[ft_strlen(block) - 1] == ')')
	{
		ft_strlcpy(sub_prompt, &block[1], str_len);
		return (sub_prompt);
	}
	return (NULL);
}

void	handle_block(t_ast *root)
{
	char	*sub_prompt;
	int		pid;

	pid = fork();
	if (pid == 0)
	{
		is_fork(1);
		sub_prompt = remove_bracket(root->cmd_list[0]);
		root = ast_holder(root, 1, 1);
		root = parser(sub_prompt);
		if (!root)
			return ;
		free(sub_prompt);
		starting_exec(root);
		root = ast_holder(root, 1, 1);
		close_fds(NULL, 1);
		free_program(&root, NULL, create_envs_table(1, 1));
		exit(update_status_error(-1));
	}
	else
		pid_last_exit_status(pid);
}
