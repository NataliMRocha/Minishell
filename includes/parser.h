/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egeraldo <egeraldo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/12 15:14:48 by egeraldo          #+#    #+#             */
/*   Updated: 2024/02/01 11:23:06 by egeraldo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

# include "lexer.h"

typedef struct s_envs
{
	char			*key;
	char			*value;
	struct s_envs	*next;
}					t_envs;

int					check_syntax_error(t_token **list);
int					check_quotes_error(t_token *list);
t_envs				**create_envs_table(void);
char				*expand_env_var(char *buf, t_envs *envs);
char				*ft_getenv(t_envs *envs, char *key);
void				splited_free(char **s, int w);
int				    heredoc(char *name, char *delim, t_envs *var_envs);
void				free_env_list(t_envs *list);

#endif