/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_readline.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egeraldo <egeraldo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/15 11:37:28 by egeraldo          #+#    #+#             */
/*   Updated: 2024/02/07 15:44:37 by egeraldo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*ft_readline(void)
{
	char *buffer;
	char *prompt;

	prompt = malloc(2);
	prompt[0] = '\0';
	prompt = ft_strjoin(prompt, "\001\x1b[32m\002");
	prompt = ft_strjoin(prompt, getenv("USER"));
	prompt = ft_strjoin(prompt, "@minishell $>");
	prompt = ft_strjoin(prompt, "\001\x1b[m\002");
	buffer = readline(prompt);
	add_history(buffer);
	free(prompt);
	return (buffer);
}
