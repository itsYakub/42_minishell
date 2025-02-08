/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lwillis <lwillis@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/06 11:04:28 by lwillis           #+#    #+#             */
/*   Updated: 2025/02/08 11:31:28 by lwillis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

/*
	Emulates the env command.
	Should not show empty exported vars
*/
void	ms_env(t_cmd *cmd)
{
	int		i;
	int		len;
	char	*var;

	if (1 != count_array(cmd->cmd))
		return ;
	i = -1;
	while (cmd->mini->env[++i])
	{
		var = env_value_from_index(i, cmd->mini->env);
		if (!var)
			continue ;
		free(var);
		ft_putstr_fd(cmd->mini->env[i], cmd->fd1);
		len = ft_strlen(cmd->mini->env[i]);
		if ('\n' != cmd->mini->env[i][len - 1])
			ft_putstr_fd("\n", cmd->fd1);
	}
}
