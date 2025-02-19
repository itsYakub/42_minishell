/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lwillis <lwillis@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/06 11:04:28 by lwillis           #+#    #+#             */
/*   Updated: 2025/02/19 10:57:02 by lwillis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/*
	Replicates the env command.
	Should not show empty exported vars
*/
void	ms_env(t_command *cmd)
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
		printf("%s", cmd->mini->env[i]);
		len = ft_strlen(cmd->mini->env[i]);
		if ('\n' != cmd->mini->env[i][len - 1])
			printf("\n");
	}
}
