/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egeraldo <egeraldo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/12 15:14:37 by egeraldo          #+#    #+#             */
/*   Updated: 2024/03/08 17:26:44 by egeraldo         ###   ########.fr       */
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
void	close_fds(int *fd, int std_fds);
void    starting_exec(t_ast *root);
char	*verify_path(t_ast *root);
void	free_split(char **path);
int		execute_builtin(t_ast *root);

#endif