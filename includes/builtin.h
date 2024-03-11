/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: etovaz <etovaz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/12 15:14:18 by egeraldo          #+#    #+#             */
/*   Updated: 2024/03/11 18:47:22 by etovaz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTIN_H
# define BUILTIN_H

# include "parser.h"

t_envs	*new_envs_node(char *key, char *value);
t_envs	**create_envs_table(int is_created, int is_free);
t_envs	*ft_getenv(char *key);
int		ft_export(char **var);
int		ft_unset(char **keys);
int		print_env_list(t_envs *envs);
char	**envs_to_array(void);
void	ft_exit(char **prompt, t_ast *root);
int		ft_pwd(void);

#endif