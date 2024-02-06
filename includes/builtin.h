/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egeraldo <egeraldo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/12 15:14:18 by egeraldo          #+#    #+#             */
/*   Updated: 2024/02/02 18:38:32 by egeraldo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTIN_H
# define BUILTIN_H

# include "parser.h"

void	ft_export(char *variable, t_envs **var_envs);
void	ft_unset(char *key, t_envs **var_envs);
void	print_env_list(t_envs *envs);

#endif