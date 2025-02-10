/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lwillis <lwillis@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/06 11:04:28 by lwillis           #+#    #+#             */
/*   Updated: 2025/02/10 14:50:46 by joleksia         ###   ########.fr       */
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

	if (1 != count_array(cmd->args))
		return ;
	i = -1;
	while (cmd->mini->env[++i])
	{
		var = env_value_from_index(i, cmd->mini->env);
		if (!var)
			continue ;
		free(var);
		ft_putstr_fd(cmd->mini->env[i], cmd->rdrfd[1]);
		len = ft_strlen(cmd->mini->env[i]);
		if ('\n' != cmd->mini->env[i][len - 1])
			ft_putstr_fd("\n", cmd->rdrfd[1]);
	}
}
