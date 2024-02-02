/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_signals.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egeraldo <egeraldo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/01 11:26:08 by egeraldo          #+#    #+#             */
/*   Updated: 2024/02/02 11:09:08 by egeraldo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/*
	Preciso lidar com os sinais de interrupção do terminal
	Ctrl + C, Ctrl + D, Ctrl + \
	Ctrl + C: SIGINT - printa ^C e não finaliza o programa
	Ctrl + D: EOF - printa exit e finaliza o programa
	Ctrl + \: SIGQUIT - é ignorado, não faz nada
*/

void sigint_handler(int sig)
{
    printf("\n");
    rl_on_new_line();
    rl_replace_line("", 0);
    rl_redisplay();
    (void)sig;
}

void setup_signals(void)
{
    signal(SIGINT, sigint_handler);
}
