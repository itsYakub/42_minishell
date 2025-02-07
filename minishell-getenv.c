/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell-getenv.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joleksia <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/07 08:35:04 by joleksia          #+#    #+#             */
/*   Updated: 2025/02/07 08:38:07 by joleksia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*msh_getenv(t_mini *mini, const char *env)
{
	char	**env0;
	char	*res;

	env0 = mini->env;
	while (ft_memcmp(*env0, env, ft_strlen(env)))
		env0++;
	if (!env0)
		return (NULL);
	res = ft_substr(*env0, 0, ft_strchr(*env0, '\n') - *env0);
	return (res);
}
