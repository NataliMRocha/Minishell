/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structs.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egeraldo <egeraldo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/05 22:14:22 by codespace         #+#    #+#             */
/*   Updated: 2024/02/21 19:24:13 by egeraldo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTS_H
# define STRUCTS_H

typedef enum e_token_type
{
	WORD,
	QUOTE,
	DQUOTE,
	PAREN_CLOSE,
	PAREN_OPEN,
	PIPE,
	HEREDOC,
	REDIR_IN,
	REDIR_OUT,
	REDIR_APPEND,
	OR,
	AND,
	EXEC
}					t_token_type;

typedef struct s_token
{
	char			*data;
	t_token_type	type;
	struct s_token	*next;
	struct s_token	*prev;
}					t_token;

typedef struct s_envs
{
	char			*key;
	char			*value;
	struct s_envs	*next;
}					t_envs;

typedef struct s_ast
{
	t_token			*tokens_to_exec;
	t_token_type	type;
	int				fd;
	struct s_ast	*right;
	struct s_ast	*left;
}					t_ast;

#endif