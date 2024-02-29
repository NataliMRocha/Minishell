/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egeraldo <egeraldo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/12 15:14:48 by egeraldo          #+#    #+#             */
/*   Updated: 2024/02/28 12:38:01 by egeraldo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

# include "structs.h"

int		check_syntax_error(t_token **list);
int		check_quotes_error(t_token *list);
t_envs	*new_envs_node(char *key, char *value);
t_envs **create_envs_table(int is_created);
char	*expand_var(char *buf);
t_envs	*ft_getenv(char *key);
void	splited_free(char **s, int w);
void	free_env_list(t_envs *list);
int		check_builtin(t_token **token_list);
t_ast	*parser(t_token *token_list);
int		is_redirect(t_token *token);

#endif