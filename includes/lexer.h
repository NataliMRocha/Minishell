/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egeraldo <egeraldo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/12 15:15:13 by egeraldo          #+#    #+#             */
/*   Updated: 2024/03/07 11:36:21 by egeraldo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TOKENS_H
# define TOKENS_H

# include "structs.h"

int		ft_handle_quote(char *str, char quote, int check_close);
int		ft_handle_block(char *str, int check_close);
int		is_symbol(char *res);
char	*ft_strtok(char *str, int call);
char	*free_static(char *res, int i, int j);
int		stack_len(t_token *list);
t_token	*find_last_node(t_token *head);
void	stack_fill(t_token *list);
void	append_node(t_token **list, char *content);
int		list_fill(t_token **list, char *readline);
void	ft_write_types(t_token *list);
void	free_token_list(t_token **list);
t_token	**get_tokens(t_token *tokens);
void    print_error(int error);
int     check_syntax_and_quotes(t_token **list, char *readline);

#endif