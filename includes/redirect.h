/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: etovaz <etovaz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/16 11:13:54 by egeraldo          #+#    #+#             */
/*   Updated: 2024/03/07 23:55:29 by etovaz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef REDIRECTS_H
# define REDIRECTS_H

# include "structs.h"

int		heredoc(char **delim, char count);
int		redir_out(t_token *tokens, t_token_type type);
void	move_redirect(t_token **tokens);
void	move_redirect_right(t_token **arch, t_token **word);
void	handle_redir(t_ast *root);
int		ft_puterror(char *cmd, char *str);
void	free_list(t_fds **fds);
void	dup_and_close(int *std_fd);
void	save_fds(int *fds, int flag);
#endif