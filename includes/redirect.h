/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egeraldo <egeraldo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/16 11:13:54 by egeraldo          #+#    #+#             */
/*   Updated: 2024/03/06 11:48:09 by egeraldo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef REDIRECTS_H
# define REDIRECTS_H

# include "structs.h"

int		heredoc(char *name, char *delim);
int		redir_out(t_token *tokens, t_token_type type);
void	move_redirect(t_token **tokens);
void	move_redirect_right(t_token **arch, t_token **word);
int		check_redirect(t_ast *root);
void	handle_redir(t_ast *root);
int		ft_puterror(char *cmd, char *str, t_ast *root);
int		check_redirect(t_ast *root);
void	free_list(t_fds **fds);
void	dup_and_close(int *std_fd);
#endif