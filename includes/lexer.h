/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egeraldo <egeraldo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/12 15:15:13 by egeraldo          #+#    #+#             */
/*   Updated: 2024/02/06 11:22:17 by egeraldo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TOKENS_H
# define TOKENS_H

# include "structs.h"

int		ft_handle_quote(char *str, char quote);
int		is_symbol(char *res);
char	*ft_strtok(char *str, int call);
int		stack_len(t_token *list);
t_token	*find_last_node(t_token *head);
void	stack_fill(t_token *list);
void	append_node(t_token **list, char *content);
int		list_fill(t_token **list, char *readline, t_envs *envs);
void	ft_write_types(t_token *list);
void	free_token_list(t_token *list);

#endif