/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: etovaz <etovaz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/10 10:40:11 by etovaz            #+#    #+#             */
/*   Updated: 2024/03/11 18:49:10 by etovaz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	ft_pwd(void)
{
	char	*path;

	path = ft_calloc(1024, sizeof(char));
	getcwd(path, 1024);
	ft_putendl_fd(path, STDOUT_FILENO);
	free(path);
	return (0);
}
