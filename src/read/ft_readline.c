/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_readline.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egeraldo <egeraldo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/15 11:37:28 by egeraldo          #+#    #+#             */
/*   Updated: 2024/01/30 11:55:32 by egeraldo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*ft_readline(void)
{
	char *buffer;
	char *prompt;
	char *test;

	printf("\001\x1b[32m\002%s@minishell\001\x1b[m\002", getenv("USER"));
	prompt = "\001\x1b[38;2;252;127;0m\002 $> \001\x1b[25;0m\002";
	buffer = readline(prompt);
	test = expand_env_var(buffer);
	printf("\nVARIAVEIS DE AMBIENTE: %s\n\n", test);
	free(test);
	add_history(buffer);
	return (buffer);
}
