/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egeraldo <egeraldo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/02 18:45:05 by egeraldo          #+#    #+#             */
/*   Updated: 2024/02/02 19:37:14 by egeraldo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	parser(t_token *token_list, t_envs **envs, char *get_cmd)
{
	list_fill(&token_list, get_cmd);
	//TODO: função para verificar se o comando é um builtin
	//TODO: função para verificar se o comando é um executável
	//TODO: função pra lidar com os redirects e verifica se temos acesso e permissao aos arquivos
	//TODO: função para executar o comando
}