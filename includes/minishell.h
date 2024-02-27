/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egeraldo <egeraldo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/12 15:07:49 by egeraldo          #+#    #+#             */
/*   Updated: 2024/02/27 16:38:23 by egeraldo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "../libs/libft/libft.h"
# include "ast.h"
# include "builtin.h"
# include "exec.h"
# include "fcntl.h"
# include "lexer.h"
# include "parser.h"
# include "read.h"
# include "redirect.h"
# include <readline/history.h>
# include <readline/readline.h>
# include <signal.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/wait.h>
# include <unistd.h>

void	free_program(t_ast **root, t_token **token_list, char **get_cmd, t_envs **var_envs);
int		update_status_error(int i);

#endif