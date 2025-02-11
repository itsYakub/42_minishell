/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lwillis <lwillis@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/06 10:42:31 by lwillis           #+#    #+#             */
/*   Updated: 2025/02/11 15:48:09 by joleksia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ms_exit(t_cmd *cmd)
{
	free_stringlist(cmd->mini->env);
	free_stringlist(cmd->args);
	msh_lexer_free(&cmd->mini->lexer);
	free(cmd);
	printf("exit\n");
	exit(0);
}
