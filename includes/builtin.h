/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: etovaz <etovaz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/12 15:14:18 by egeraldo          #+#    #+#             */
/*   Updated: 2024/03/09 15:21:55 by etovaz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTIN_H
# define BUILTIN_H

# include "parser.h"

t_envs	*new_envs_node(char *key, char *value);
t_envs	**create_envs_table(int is_created);
t_envs	*ft_getenv(char *key);
int		ft_export(char **var);
int		ft_unset(char *key, t_envs **var_envs);
int		print_env_list(t_envs *envs);
char	**envs_to_array(void);

#endif