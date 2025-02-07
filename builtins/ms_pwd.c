/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lwillis <lwillis@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/06 10:48:46 by lwillis           #+#    #+#             */
/*   Updated: 2025/02/07 11:26:18 by lwillis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ms_pwd(char *env_vars[])
{
	char	*pwd;
	char	*sub;
	
	pwd = env_var("PWD=", env_vars);
	if (!pwd)
		return ;
	sub = ft_substr(pwd, 4, ft_strlen(pwd));
	printf("%s\n", sub);
	free(sub);
}
