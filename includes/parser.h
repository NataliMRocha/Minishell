/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: etovaz <etovaz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/12 15:14:48 by egeraldo          #+#    #+#             */
/*   Updated: 2024/03/18 17:13:21 by etovaz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

# include "structs.h"

char	*ft_readline(int get_buffer);
int		check_syntax_error(t_token **list);
int		check_quotes_error(t_token *list);
char	*expand_var(char *buf);
char	**expanded_variable(char **cmd_list);
void	splited_free(char **s, int w);
void	free_env_list(t_envs *list);
int		check_builtin(t_token **token_list);
t_ast	*parser(char *get_cmd);
int		is_redirect(int type);
int		ft_isin(char *str, char *set);
int		is_redir_after_symbol(t_token *list);
int		check_block_error(t_token *list);
int		is_redir_followed_by_pipe(t_token *tmp);

#endif