/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lwillis <lwillis@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/06 11:04:28 by lwillis           #+#    #+#             */
/*   Updated: 2025/02/07 15:29:14 by lwillis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ms_env(t_mini *mini)
{
	int	i;
	int	len;

	i = -1;
	while (mini->env[++i])
	{
		ft_putstr_fd(mini->env[i], mini->cmd->fd1);
		len = ft_strlen(mini->env[i]);
		if ('\n' != mini->env[i][len - 1])
			ft_putstr_fd("\n", mini->cmd->fd1);
	}
}
