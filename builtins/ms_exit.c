/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lwillis <lwillis@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/06 10:42:31 by lwillis           #+#    #+#             */
/*   Updated: 2025/02/08 15:13:59 by lwillis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ms_exit(t_cmd *cmd)
{
	// Check these
	free_stringlist(cmd->mini->env);
	free_stringlist(cmd->cmd);
	free(cmd);
	cmd->mini->exit = 11;
}
