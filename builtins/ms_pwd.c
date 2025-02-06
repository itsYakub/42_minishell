/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lwillis <lwillis@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/06 10:48:46 by lwillis           #+#    #+#             */
/*   Updated: 2025/02/06 14:41:16 by lwillis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ms_pwd(t_env *env_vars)
{
	char	*pwd;
	
	pwd = env_var("PWD=", env_vars);
	if (!pwd)
		return ;
	printf("%s\n", pwd);
	free(pwd);
}
