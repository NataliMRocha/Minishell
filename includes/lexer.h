/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egeraldo <egeraldo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/12 15:15:13 by egeraldo          #+#    #+#             */
/*   Updated: 2024/01/17 10:52:31 by egeraldo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TOKENS_H
# define TOKENS_H

typedef struct	s_token
{
	char			*data;
	int				type;
	struct s_token	*next;
}				t_token;

int		ft_handle_quote(char *str, char quote);
char	*ft_strtok(char *str);

#endif