/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lwillis <lwillis@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/07 09:52:49 by lwillis           #+#    #+#             */
/*   Updated: 2025/02/20 10:02:28 by joleksia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/*
	Removes one var from the env list and shortens the list
*/
static void	remove_var(char *var_name, t_command *cmd)
{
	int		pos;
	int		i;
	int		passed_pos;
	int		count;
	char	**copy;

	pos = env_var_index(var_name, cmd->mini->env);
	count = count_array(cmd->mini->env);
	if (-1 == count || -1 == pos)
		return ;
	copy = malloc(sizeof(char *) * count);
	if (!copy)
		return ;
	passed_pos = 0;
	i = -1;
	while (cmd->mini->env[++i])
	{
		if (i == pos)
			passed_pos = 1;
		if (i + passed_pos < count)
			copy[i] = ft_strdup(cmd->mini->env[i + passed_pos]);
	}
	copy[count - 1] = NULL;
	ft_free2d((void **) cmd->mini->env);
	cmd->mini->env = copy;
}

/*
	Replicates the unset command
*/
void	ms_unset(t_command *cmd)
{
	int	count;
	int	i;

	count = count_array(cmd->args);
	if (1 == count)
		return ;
	i = 0;
	while (cmd->args[++i])
		remove_var(cmd->args[i], cmd);
}
