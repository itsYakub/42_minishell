/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lwillis <lwillis@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/06 10:48:46 by lwillis           #+#    #+#             */
/*   Updated: 2025/02/10 14:51:37 by joleksia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ms_pwd(t_cmd *cmd)
{
	char	*pwd;
	char	*sub;

	if (1 != count_array(cmd->args))
	{
		write(2, "pwd: too many arguments\n", 24);
		return ;
	}
	pwd = env_var("PWD", cmd->mini->env);
	if (!pwd)
		return ;
	sub = ft_substr(pwd, 4, ft_strlen(pwd));
	ft_putstr_fd(sub, cmd->rdrfd[1]);
	ft_putstr_fd("\n", cmd->rdrfd[1]);
	free(sub);
}
