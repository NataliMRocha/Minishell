/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: natali <natali@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/12 15:14:37 by egeraldo          #+#    #+#             */
/*   Updated: 2024/02/26 20:25:22 by natali           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXEC_H
# define EXEC_H

# include "structs.h"

void	setup_signals(void);
void    exec(t_ast *root);
void    handle_and_or(t_ast *root);
void    handle_pipe(t_ast *root);
void    pipe_fork(int *fd, t_ast *root, int in_out);
void    starting_exec(t_ast *root);
char	*verify_path(t_ast *root);
#endif