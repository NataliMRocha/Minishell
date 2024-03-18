/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: etovaz <etovaz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/12 15:15:01 by egeraldo          #+#    #+#             */
/*   Updated: 2024/03/18 16:26:31 by etovaz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SIGNALS_H
# define SIGNALS_H

# include "structs.h"

int		on_heredoc(int on_heredoc);
void	sigquit_case(void);
int		is_after_prompt(int is_after);
int		is_fork(int status);
void	term_properties(int restore);
void	sigint_handler(int signal);
void	signals_initializer(void);

#endif