/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: natali <natali@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/02 18:45:05 by egeraldo          #+#    #+#             */
/*   Updated: 2024/02/06 21:55:52 by natali           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

//TODO: função para verificar se o comando é um executável
//TODO: função pra lidar com os redirects e verifica se temos acesso e permissao aos arquivos
//TODO: função para executar o comando

int	parser(t_token **token_list, t_envs **envs, char *get_cmd)
{
	int	i;

	i = list_fill(token_list, get_cmd, *envs);
//erro de sintaxe
	if (i == 2)
		return(2);
	i = check_builtin(token_list, envs);
//exit
	if (i == 3)
		return(3);
	return (0);
}

int	check_builtin(t_token **token_list, t_envs **envs)
{
	t_token	*tmp;

	tmp = *token_list;
	while(tmp)
	{
		if (tmp->next && ft_strncmp("export", tmp->data, ft_strlen(tmp->data)) == 0)
			ft_export(tmp->next->data, envs);
		else if (tmp->next && ft_strncmp("unset", tmp->data, ft_strlen(tmp->data)) == 0)
			ft_unset(tmp->next->data, envs);
		else if (ft_strncmp("env", tmp->data, ft_strlen(tmp->data)) == 0)
			print_env_list(*envs);
		else if (ft_strncmp("exit", tmp->data, ft_strlen(tmp->data)) == 0)
			return (3);
		tmp = tmp->next;
	}
	return (0);
	
}