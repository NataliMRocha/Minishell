/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_readline.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egeraldo <egeraldo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/15 11:37:28 by egeraldo          #+#    #+#             */
/*   Updated: 2024/01/29 17:40:05 by egeraldo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*ft_readline(void)
{
	char *buffer;
	char *prompt;

	printf("\001\x1b[32m\002%s@minishell\001\x1b[m\002", getenv("USER"));
	prompt = "\001\x1b[38;2;252;127;0m\002 $> \001\x1b[25;0m\002";
	buffer = readline(prompt);
	add_history(buffer);
	return (buffer);
}
