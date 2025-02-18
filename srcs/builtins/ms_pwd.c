/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lwillis <lwillis@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/06 10:48:46 by lwillis           #+#    #+#             */
/*   Updated: 2025/02/18 10:30:20 by lwillis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	ms_pwd(t_command *cmd)
{
	char	*pwd;

	pwd = env_value("PWD", cmd->mini, 0);
	if (!pwd)
		return ;
	printf("%s\n", pwd);
	free(pwd);
}
