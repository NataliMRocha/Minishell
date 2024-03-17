/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_readline.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: etovaz <etovaz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/15 11:37:28 by egeraldo          #+#    #+#             */
/*   Updated: 2024/03/16 20:35:49 by etovaz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*ft_readline(void)
{
	static char	*buffer;
	char	*prompt;

	prompt = malloc(2);
	prompt[0] = '\0';
	prompt = ft_strjoin(prompt, "\001\x1b[32m\002", 1);
	prompt = ft_strjoin(prompt, getenv("USER"), 1);
	prompt = ft_strjoin(prompt, "@minishell $>", 1);
	prompt = ft_strjoin(prompt, "\001\x1b[m\002", 1);
	is_after_prompt(0);
	buffer = readline(prompt);
	is_after_prompt(1);
	if (buffer && ft_strcmp(buffer, ""))
		add_history(buffer);
	free(prompt);
	return (buffer);
}
