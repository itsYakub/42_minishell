/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lwillis <lwillis@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/06 10:48:46 by lwillis           #+#    #+#             */
/*   Updated: 2025/02/15 16:05:44 by lwillis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	ms_pwd(t_command *cmd)
{
	char	*pwd;

	if (1 != count_array(cmd->args))
	{
		ft_putstr_fd("pwd: too many arguments\n", 2);
		return ;
	}
	pwd = env_value("PWD", cmd->mini, 0);
	if (!pwd)
		return ;
	printf("%s\n", pwd);
	free(pwd);
}
