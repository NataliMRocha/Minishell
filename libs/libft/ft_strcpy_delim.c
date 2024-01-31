/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcpy_delim.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egeraldo <egeraldo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/31 11:03:24 by egeraldo          #+#    #+#             */
/*   Updated: 2024/01/31 11:07:55 by egeraldo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strcpy_delim(const char *src, char delim)
{
	int		i;
	char	*tmp;

	i = 0;
	tmp = (char *)src;
	while (src && src[i] != delim)
		i++;
	tmp[i] = '\0';
	return (ft_strdup(tmp));
}
