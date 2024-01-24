/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egeraldo <egeraldo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/12 15:15:13 by egeraldo          #+#    #+#             */
/*   Updated: 2024/01/24 14:56:33 by egeraldo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TOKENS_H
# define TOKENS_H

typedef enum e_token_type
{
	WORD,
	PIPE,
	REDIR_IN,
	REDIR_OUT,
	REDIR_APPEND,
	REDIR_HERE_DOC,
	QUOTE,
	DQUOTE,
	OR,
	AND,
	PAREN_OPEN
}				t_token_type;

typedef struct	s_token
{
	char			*data;
	t_token_type	type;
	struct s_token	*next;
	struct s_token	*prev;
}				t_token;

int		ft_handle_quote_paren(char *str, char quote);
char	*ft_strtok(char *str, int call);
void	list_fill(t_token **list, char *readline);
void	ft_write_types(t_token *list);

#endif