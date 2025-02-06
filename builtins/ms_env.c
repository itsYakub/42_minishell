/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lwillis <lwillis@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/06 11:04:28 by lwillis           #+#    #+#             */
/*   Updated: 2025/02/06 14:42:04 by lwillis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ms_env(t_env *env_vars)
{
	t_env	*node;
	
	node = env_vars;
	while (node)
	{
		//putstr_fd?
		printf("%s\n", node->var);
		node = node->next;
	}
}
