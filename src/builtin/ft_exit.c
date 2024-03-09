/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: etovaz <etovaz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/09 18:27:31 by etovaz            #+#    #+#             */
/*   Updated: 2024/03/09 18:54:59 by etovaz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	ft_exit(int exit_code)
{
	// TODO: precisa atualizar o status code
	ast_holder(NULL, 1, 1);
	free_env_list(*create_envs_table(1, 1));
	exit(update_status_error(exit_code));
}
