/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/12 15:14:48 by egeraldo          #+#    #+#             */
/*   Updated: 2024/02/05 22:15:27 by codespace        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

# include "structs.h"

int					check_syntax_error(t_token **list);
int					check_quotes_error(t_token *list);
t_envs				*new_envs_node(char *key, char *value);
t_envs				**create_envs_table(void);
char				*expand_env_var(char *buf, t_envs *envs);
t_envs				*ft_getenv(t_envs *envs, char *key);
void				splited_free(char **s, int w);
int				    heredoc(char *name, char *delim, t_envs *var_envs);
void				free_env_list(t_envs *list);

#endif