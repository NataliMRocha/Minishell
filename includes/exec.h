/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: etovaz <etovaz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/12 15:14:37 by egeraldo          #+#    #+#             */
/*   Updated: 2024/03/14 18:18:23 by etovaz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXEC_H
# define EXEC_H

# include "structs.h"

void	setup_signals(void);
void	exec(t_ast *root);
void	handle_and_or(t_ast *root);
void	handle_pipe(t_ast *root);
void	pipe_fork(int *fd, t_ast *root, int in_out);
void	close_fds(int *fd, int std_fds);
void	starting_exec(t_ast *root);
char	*verify_path(t_ast *root);
void	free_split(char **path);
int		execute_builtin(t_ast *root);
void	handle_block(t_ast *root);
int		access_path(char *path);
void	term_properties(int restore);
void	signals_initializer(void);
int		is_after_prompt(int is_after);
int		is_fork(int status);
int		on_heredoc(int on_heredoc);
void	sigquit_case(void);
void	exec_error(char *cmd, char **path);
void	handle_fork(int pid, t_ast *root, char *path);
#endif