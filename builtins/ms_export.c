/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lwillis <lwillis@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/07 09:51:55 by lwillis           #+#    #+#             */
/*   Updated: 2025/02/07 09:59:28 by lwillis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ms_export(t_cmd cmd, t_env *env_vars)
{
	int	cmd_count;

	cmd_count = -1;
	while (cmd.cmd[++cmd_count])
		;
	if (1 == cmd_count)
	{
		ms_env(env_vars);
		return ;
	}
}
