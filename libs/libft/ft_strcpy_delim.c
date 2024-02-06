/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcpy_delim.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egeraldo <egeraldo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/31 11:03:24 by egeraldo          #+#    #+#             */
/*   Updated: 2024/02/02 11:58:08 by egeraldo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strcpy_delim(const char *src, char delim)
{
	int		i;
	char	*tmp;

	i = -1;
	tmp = malloc(sizeof(char) * (ft_strlen(src) + 1));
	while (src && src[++i] != delim)
		tmp[i] = src[i];
	tmp[i] = '\0';
	return (tmp);
}
