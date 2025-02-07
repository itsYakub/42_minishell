/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lwillis <lwillis@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/07 09:51:55 by lwillis           #+#    #+#             */
/*   Updated: 2025/02/07 11:37:08 by lwillis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ms_export(t_cmd cmd, char *env_vars[])
{
	int	cmd_count;

	cmd_count = count_array(cmd.cmd);
	if (1 == cmd_count)
	{
		ms_env(env_vars);
		return ;
	}
}
