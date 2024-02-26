/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/12 15:14:37 by egeraldo          #+#    #+#             */
/*   Updated: 2024/02/26 21:28:04 by codespace        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXEC_H
# define EXEC_H

# include "structs.h"

void	setup_signals(void);
void exec(t_ast *root);
void handle_and_or(t_ast *root);
void starting_exec(t_ast *root);
char	*verify_path(t_ast *root);
#endif