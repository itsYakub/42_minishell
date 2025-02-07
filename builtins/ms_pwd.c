/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lwillis <lwillis@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/06 10:48:46 by lwillis           #+#    #+#             */
/*   Updated: 2025/02/07 15:54:08 by lwillis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ms_pwd(t_mini *mini)
{
	char	*pwd;
	char	*sub;
	
	pwd = env_var("PWD", mini->env);
	if (!pwd)
		return ;
	sub = ft_substr(pwd, 4, ft_strlen(pwd));
	ft_putstr_fd(sub, mini->cmd->fd1);
	ft_putstr_fd("\n", mini->cmd->fd1);
	free(sub);
}
