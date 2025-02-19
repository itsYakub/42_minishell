/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_piper.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lwillis <lwillis@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/17 14:50:05 by lwillis           #+#    #+#             */
/*   Updated: 2025/02/19 10:43:19 by lwillis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static int	is_last_command(t_mini *mini)
{
	return (mini->current_cmd == mini->cmdc - 1);
}

void	connect_pipes(t_mini *mini, t_pipe pipes[2])
{
	if (mini->cmdc > 1)
	{
		if (is_last_command(mini) || mini->current_cmd != 0)
			dup2(pipes[PREVIOUS_CMD][READ_END], STDIN_FILENO);
		if (mini->current_cmd == 0 || !is_last_command(mini))
			dup2(pipes[CURRENT_CMD][WRITE_END], STDOUT_FILENO);
	}
}

void	close_pipes(t_mini *mini, t_pipe pipes[2])
{
	if (mini->cmdc > 1)
	{
		if (is_last_command(mini) || mini->current_cmd != 0)
			close(pipes[PREVIOUS_CMD][READ_END]);
		if (mini->current_cmd == 0 || !is_last_command(mini))
			close(pipes[CURRENT_CMD][WRITE_END]);
	}
}

void	swap_pipes(int **pipes)
{
	int	*pipe_current;

	pipe_current = pipes[CURRENT_CMD];
	pipes[CURRENT_CMD] = pipes[PREVIOUS_CMD];
	pipes[PREVIOUS_CMD] = pipe_current;
}
