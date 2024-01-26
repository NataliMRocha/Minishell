/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: natali <natali@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/12 15:15:13 by egeraldo          #+#    #+#             */
/*   Updated: 2024/01/26 17:29:25 by natali           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TOKENS_H
# define TOKENS_H

typedef enum e_token_type
{
	WORD,
	REDIR_HERE_DOC,
	REDIR_IN,
	PAREN_OPEN,
	PAREN_CLOSE,
	QUOTE,
	DQUOTE,
	PIPE,
	REDIR_OUT,
	REDIR_APPEND,
	OR,
	AND
}				t_token_type;

typedef struct	s_token
{
	char			*data;
	t_token_type	type;
	struct s_token	*next;
	struct s_token	*prev;
}				t_token;

int		ft_handle_quote(char *str, char quote);
char	*ft_strtok(char *str, int call);
int		stack_len(t_token *list);
t_token	*find_last_node(t_token *head);
void	stack_fill(t_token *list);
void	append_node(t_token **list, char *content);
void	list_fill(t_token **list, char *readline);
void	ft_write_types(t_token *list);
void	free_list(t_token *list);

#endif