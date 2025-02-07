/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lwillis <lwillis@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/07 09:52:49 by lwillis           #+#    #+#             */
/*   Updated: 2025/02/07 16:40:46 by lwillis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

/*
	Removes one var from the env list and shortens the list
*/
static void	remove_var(char *var_name, t_mini *mini)
{
	int		pos;
	int		i;
	int		passed_pos;
	int		count;
	char	**copy;

	count = count_array(mini->env);
	if (-1 == count)
		return ;
	copy = malloc(sizeof(char *) * count);
	if (!copy)
		return ;
	pos = env_var_pos(var_name, mini->env);
	passed_pos = 0;
	i = -1;
	while (mini->env[++i])
	{
		if (i == pos)
			passed_pos = 1;
		if (i + passed_pos < count)
			copy[i] = ft_strdup(mini->env[i + passed_pos]);
	}
	copy[count - 1] = NULL;
	free_stringlist(mini->env);
	mini->env = copy;
}

/*
	Removes vars from the env list
*/
void	ms_unset(t_mini *mini)
{
	int	count;
	int	i;

	count = count_array(mini->cmd->cmd);
	if (1 == count)
		return;
	i = 0;
	while (mini->cmd->cmd[++i])
		remove_var(mini->cmd->cmd[i], mini);	
}
