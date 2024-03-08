/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: natali <natali@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/12 15:14:18 by egeraldo          #+#    #+#             */
/*   Updated: 2024/03/08 11:32:05 by natali           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTIN_H
# define BUILTIN_H

# include "parser.h"

t_envs	*new_envs_node(char *key, char *value);
t_envs	**create_envs_table(int is_created);
t_envs	*ft_getenv(char *key);
void	ft_export(char *variable, t_envs **var_envs);
void	ft_unset(char *key, t_envs **var_envs);
void	print_env_list(t_envs *envs);
char	**envs_to_array(void);
void    creat_error_env(t_envs **envs);

#endif