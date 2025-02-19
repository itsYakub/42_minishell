/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lwillis <lwillis@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/06 10:48:46 by lwillis           #+#    #+#             */
/*   Updated: 2025/02/19 10:59:47 by lwillis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/*
	Replicates the pwd command.
	Can't use getcwd() as we're dealing with our own env list
*/
void	ms_pwd(t_command *cmd)
{
	char	*pwd;

	pwd = env_value("PWD", cmd->mini, 0);
	if (!pwd)
		return ;
	printf("%s\n", pwd);
	free(pwd);
}
