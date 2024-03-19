/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egeraldo <egeraldo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/16 11:13:54 by egeraldo          #+#    #+#             */
/*   Updated: 2024/03/19 17:53:27 by egeraldo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef REDIRECT_H
# define REDIRECT_H

# include "structs.h"

int		heredoc(char **delim, char count);
int		redir_out(t_token *tokens, t_token_type type);
void	move_redirect(t_token **tokens);
void	move_redirect_right(t_token **arch, t_token **word);
void	handle_redir(t_ast *root);
int		ft_puterror(char *cmd, char *str);
void	free_list(t_fds **fds);
void	dup_and_close(int *std_fd);
void	save_fds(int *fds, int close_fds);
void	capture_heredoc(t_token **token_list);
t_fds	**fds_list(char **name, int type);
int		is_directory(char *name);

#endif