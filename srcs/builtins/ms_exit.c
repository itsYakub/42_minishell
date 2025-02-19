/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lwillis <lwillis@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/06 10:42:31 by lwillis           #+#    #+#             */
/*   Updated: 2025/02/19 11:05:23 by joleksia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	ms_exit(t_command *cmd)
{
	t_mini	*mini;

	mini = cmd->mini;
	if (mini->cmdc > 1)
		return ;
	if (1 == mini->cmdc)
		ft_putstr_fd("exit\n", 2);
	free_stringlist(mini->commands->args);
	free_stringlist(mini->env);
	free(mini->commands->orig);
	free(mini->commands->infilename);
	free(mini->commands->outfilename);
	free(mini->commands->other_outfilenames);
	free(mini->commands);
	exit(0);
}
