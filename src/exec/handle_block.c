/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_block.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: etovaz <etovaz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/11 20:50:57 by etovaz            #+#    #+#             */
/*   Updated: 2024/03/11 21:15:29 by etovaz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*remove_bracket(char *block)
{
	if (block[0] == '(' && block[ft_strlen(block) - 1] == ')')
		return(ft_strcpy_delim(&block[1], ')'));
	return (NULL);
}

void	handle_block(t_ast *root)
{
	char	*sub_prompt;
	int		pid;

	sub_prompt = remove_bracket(root->cmd_list[0]);
	pid = fork();
	if (pid == 0)
	{
		root = parser(sub_prompt);
		if (!root)
			return ;
		starting_exec(root);
		root = ast_holder(NULL, 1, 0);
		free_program(&root, &sub_prompt, NULL);
	}
	else
		pid_last_exit_status(pid);
}